/**
 * @file common_words.cpp
 * Implementation of the CommonWords class.
 *
 * @author Zach Widder
 * @date Fall 2014
 */

#include "common_words.h"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::endl;
using std::feof;

string remove_punct(const string& str)
{
    string ret;
    std::remove_copy_if(str.begin(), str.end(), std::back_inserter(ret),
                        std::ptr_fun<int, int>(&std::ispunct));
    return ret;
}

CommonWords::CommonWords(const vector<string>& filenames)
{
    // initialize all member variables
    init_file_word_maps(filenames);
    init_common();
}

void CommonWords::init_file_word_maps(const vector<string>& filenames)
{
    // make the length of file_word_maps the same as the length of filenames
    file_word_maps.resize(filenames.size());

    // go through all files
    for (size_t i = 0; i < filenames.size(); i++) {
        // get the corresponding vector of words that represents the current
        // file
        vector<string> words = file_to_vector(filenames[i]);
        /* Your code goes here! */
        for(auto & times_per_file : words)    //set up iterator in the words vector called "times_per_file" that counts the number of times that word occurs per file
            file_word_maps[i][times_per_file]++;    //for each word, find how many times it appears in the file
    }
}

void CommonWords::init_common()
{
    /* Your code goes here! */
    for(auto & file_word_map : file_word_maps) //goes through the list of file_word_maps
      {
      for(auto & maps :file_word_map)   //goes through the maps in each file_word_map
        common[maps.first]++;  //start with first word and iterate through
      }
}

/**
 * @param n The number of times to word has to appear.
 * @return A vector of strings. The vector contains all words that appear
 * in each file >= n times.
 */
vector<string> CommonWords::get_common_words(unsigned int n) const
{
    vector<string> out;
    /* Your code goes here! */
    for(auto & common_word : common) //iterate through list of common words
      {
      if(common_word.second == file_word_maps.size()) //if the number of files it occurs in is equal to the number of files, the word is in all of them
        {
          size_t files_good = 0;   //how many files the word reaches n in

          for(auto & file_word_map : file_word_maps) //iterate through the list of fild word maps
            {
            //for(auto & map : file_word_map) //iterate through maps in the file_word_map
            auto map = file_word_map.find(common_word.first); //only look at words that are common words

            size_t found_in_file = map->second; //look at the number of time is occurs in this file
            if(found_in_file >= n)      //compare to n
              files_good ++;    //count this file and move onto next one
            }

          if(files_good == file_word_maps.size()) //if the word meets the minimum in all files_good
            out.push_back(common_word.first);  //add common word to out vector
        }
      }
    return out;
}

/**
 * Takes a filename and transforms it to a vector of all words in that file.
 * @param filename The name of the file that will fill the vector
 */
vector<string> CommonWords::file_to_vector(const string& filename) const
{
    ifstream words(filename);
    vector<string> out;

    if (words.is_open()) {
        std::istream_iterator<string> word_iter(words);
        while (!words.eof()) {
            out.push_back(remove_punct(*word_iter));
            ++word_iter;
        }
    }
    return out;
}
