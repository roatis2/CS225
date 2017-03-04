#include "queue.h"
#include "stack.h"

/**
 * @file stack.cpp
 * Implementation of the Stack class.
 *
 * @author CS 225 Course Staff
 * @date Fall 2009
 *
 * @author Chase Geigle
 * @date Fall 2012
 */

/**
 * Adds the parameter object to the top of the Stack. That is, the element
 * should go at the beginning of the list.
 *
 * @note This function must be O(1)!
 *
 * @param newItem The object to be added to the Stack.
 */
template<class T>
void Stack<T>::push(T const & newItem)
{
    myStack.push_front(newItem); //adds to front
}

/**
 * Removes the object on top of the Stack, and returns it. That is, remove
 * the element at the beginning of the list. You may assume this function
 * is only called when the Stack is not empty.
 *
 * @note This function must be O(1)!
 *
 * @return The element that used to be at the top of the Stack.
 */
template <class T>
T Stack<T>::pop()
{
    T topOfStack = myStack.front(); //set to front
    myStack.pop_front(); //remove front item
    return topOfStack; //return altered stack
}

/**
 * Adds an element to the ordering structure.
 *
 * @see OrderingStructure::add()
 */
template <class T>
void Stack<T>::add(const T& theItem)
{
    push(theItem);
}

/**
 * Removes an element from the ordering structure.
 *
 * @see OrderingStructure::remove()
 */
template <class T>
T Stack<T>::remove()
{
    return this->pop();
}

/**
 * Finds the object on top of the Stack, and returns it to the caller.
 * Unlike pop(), this operation does not alter the Stack itself. It should
 * look at the beginning of the list. You may assume this function is only
 * called when the Stack is not empty.
 *
 * @note This function must be O(1)!
 *
 * @return The element at the top of the Stack.
 */
template <class T>
T Stack<T>::peek()
{
  return myStack.front(); //returns front item, this will not disturb ordering
}

/**
 * Determines if the Stack is empty.
 *
 * @note This function must be O(1)! Note that the std::list's size()
 *	function is O(n), so you should not attempt to use it here.
 *
 * @return Whether or not the stack is empty (bool).
 */
template <class T>
bool Stack<T>::isEmpty() const
{

    return myStack.empty(); //checks if empty
}
