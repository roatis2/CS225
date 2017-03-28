/**
 * @file fib.cpp
 * Contains Fibonacci-number generating functions both utilizing and not
 * utilizing memoization.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "fib.h"

#include <map>

using std::map;

/**
 * Calculates the nth Fibonacci number where the zeroth is defined to be
 * 0.
 * @param n Which number to generate.
 * @return The nth Fibonacci number.
 */
unsigned long fib(unsigned long n)
{
    /* Your code goes here! */
    if(n==0){ //given value
      return 0;
    }

    if(n==1){ //given value
      return 1;
    }
    return fib(n-1) + fib(n-2);
}

/**
 * Calculates the nth Fibonacci number where the zeroth is defined to be
 * 0. This version utilizes memoization.
 * @param n Which number to generate.
 * @return The nth Fibonacci number.
 */
unsigned long memoized_fib(unsigned long n)
{
    /* Your code goes here! */
    static map<unsigned long, unsigned long> memo = { {0, 0} , {1,1}}; //create tree named memo where zeroth is defined as 0
    auto lookup = memo.find(n); //set up iterator

    if(lookup == memo.end()){
      memo[n] = memoized_fib(n-1) + memoized_fib(n-2); //if iterator reaches end, key isn't in tree so we insert it
    }

    return memo[n];
}
