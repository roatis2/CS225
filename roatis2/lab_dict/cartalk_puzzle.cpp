/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of "StringTriples" (a typedef'd std::tuple, see top of
 * cartalk_puzzle.h). Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<StringTriple> cartalk_puzzle(PronounceDict d, const string& word_list_fname)
{
  vector< StringTriple> solutions; //what will be returned
  /*vector< string > 5LetterWords; //make a vector with potential 5 letter word candidates

  ifstream words(word_list_fname);
  string word;
  if(words.is_open())
    {

      {
        if(word.length() == 5) //solution will be a 5 letter word
        5LetterWords.push_back(word); //add to candidate words vector
      }
    }
    for(auto & Candidate : 5LetterWords) //assess each word out of the candidates
      {
        string removeFirstLetter = Candidate.substr(1); //save first letter of each candidate
        string removeSecondLetter = append(eachWord.begin(),eachWord.begin()+1);
        removeSecond.append(removeFirst.begin()+1,removeFirst.end());
          if(d.homophones(eachWord, removeFirst)&&d.homophones(eachWord, removeSecond)&&d.homophones(removeFirst, removeSecond))
          {
            StringTriple answer;
            get<0>(answer) = eachWord;
            get<1>(answer) = removeFirst;
            get<2>(answer) = removeSecond;
            out.push_back(answer);
          }
        }*/
  return solutions;
}
