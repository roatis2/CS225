#include "queue.h"
#include "stack.h"

/**
 * @file queue.cpp
 * Implementation of the Queue class.
 *
 * @author CS 225 course staff
 * @date Fall 2009
 */

/**
 * Adds the parameter object to the back of the Queue.
 *
 * @param newItem object to be added to the Queue.
 */
template <class T>
void Queue<T>::enqueue(T const& newItem)
{
    inStack.push(newItem); //add new item to end
}

/**
 * Removes the object at the front of the Queue, and returns it to the
 * caller.
 *
 * @return The item that used to be at the front of the Queue.
 */
template <class T>
T Queue<T>::dequeue()
{
    if(outStack.isEmpty() == true) //check if stack is empty, it should be
    {
      while(inStack.isEmpty() == false) //loop until empty
      {
        outStack.push(inStack.pop()); //move items from inStack to outStack, this will reverse order
      }
    }
    return outStack.pop(); //return object from end of stack which should have been at the beginning of the queue
}

/**
 * Adds an element to the ordering structure.
 *
 * @see OrderingStructure::add()
 */
template <class T>
void Queue<T>::add(const T& theItem)
{
    this->enqueue(theItem);
}

/**
 * Removes an element from the ordering structure.
 *
 * @see OrderingStructure::remove()
 */
template <class T>
T Queue<T>::remove()
{
    return this->dequeue(); //need to return an altered stack
}

/**
 * Finds the object at the front of the Queue, and returns it to the
 * caller. Unlike pop(), this operation does not alter the queue.
 *
 * @return The item at the front of the queue.
 */
template <class T>
T Queue<T>::peek()
{
    if(outStack.isEmpty() == true)//check if outstack is empty
    {
      while(inStack.isEmpty() == false) //loop through until inStack is empty
      {
        outStack.push(inStack.pop()); //move items from instack to outstack
      }
    }
    return outStack.peek(); //returns item from front of queue without changing order
}

/**
 * Determines if the Queue is empty.
 *
 * @return bool which is true if the Queue is empty, false otherwise.
 */
template <class T>
bool Queue<T>::isEmpty() const
{
    return (inStack.isEmpty() && outStack.isEmpty() ); //returns true only is both are empty
}
