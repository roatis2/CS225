/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */
template <typename T>
T sum(stack<T>& s)
{
    T popped; //create a var to hold the value on the top
    T sumStack; //var to hold the sum
    if(s.size() == 0)//check is size is empty
    {
        sumStack = 0; //if it is, return  0 to be added onto the sum
    }
    else
    {
        popped = s.top(); //let popped be the value on the top of the stack
        s.pop(); //actually pop that off so we can continue going through the stack
        sumStack = popped + sum(s); //add that onto the sum and then recursively call the sum functoin on the new smaller stack
        s.push(popped); //pop it back on so that the stack is unchanged in the end
    }

    return sumStack; //return this sum
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was
 *  complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void scramble(queue<T>& q)
{
    stack<T> s;
    int current = 1;
	  int finished = 0;
	  int size = int(q.size());

    while(finished < size) //goes through whole list. will stop at end since finished starts at 0
	  {
	      if(current%2==1)//odd block, just move
	      {
	           int amtLeft = current;
	           if(amtLeft > size-finished) //case where we have an awkward amount of blocks left
	                 amtLeft = size-finished;
             int i = 0;
             while(i < amtLeft)
		         {
                 T x = q.front();
                 q.push(x);
		             q.pop();
                 i++;
		         }
             current++;
             finished += amtLeft;
	      }

        else//even block, reverse
	      {
	         int amtLeft = current;
	         if(amtLeft > size-finished)
	              amtLeft = size-finished;
	         int i = 0;
           while(i < amtLeft)
		       {
                T y = q.front();
                s.push(y);
		            q.pop();
                i++;
		       }
           int j = 0;
           while(j < amtLeft)
		       {
               T z = s.top();
               q.push(z);
		           s.pop();
               j++;
		       }
           current++;
           finished += amtLeft;
	      }
	  }
}

/**
 * @return true if the parameter stack and queue contain only elements of
 *  exactly the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
      bool retval = true; // given statement

      if(s.size() == 0)//base case that will be used in recursive step
    	{
             return true;
      }

      else
      {
          T x = s.top();//stack content storered and carried through each recursion step;
    	    s.pop();
    	    retval = verifySame(s, q);//at base case s will be empty making it identical to front of queue

          if(x == q.front() && retval ==true)
          {
            retval = true;
          }

          else
          {
            retval = false;
          }

          retval = (retval && (x == q.front()));
          s.push(x);//add previous s back onto stack
          q.push(q.front());//shuffle front of queue to back
    	    q.pop();//move first element of queue to the end
      }

      return retval;
}
}
