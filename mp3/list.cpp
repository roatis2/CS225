

/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */
#include "list.h"
#include <cassert>
#include <iostream>
/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */

 using namespace std;

template <class T>
List<T>::~List()
{
    clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
    if(head == NULL || tail == NULL || length == 0) {
      assert(head == NULL && tail == NULL && length == 0); /*should all be false but if
      one is true, it terminates the program */
      return;
    }

    else{
      ListNode * current = head;
      while(current != NULL){
        ListNode * next = current->next;
        delete current;
        current = next;
      }
    }
}
/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata)
{
    ListNode * current = new ListNode(ndata); //if you insert, you will have to make a new node
    current->next = head;
    if(head == NULL){               //case where we have an empty list
        head = current;
        tail = current;
        current->prev = NULL;
        current->next = NULL;
    }
    else{       //case were we have nodes in list. add current to front and make it new head
      head->prev = current;
      head = current;
      current->prev = NULL;
   }
   length++;
   current = NULL;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata)
{
    ListNode * current = new ListNode(ndata); //if you insert, you will have to make a new node
    current->prev = tail;
    if(tail == NULL){         //same as above, except in reference to tail
        tail = current;
        head = current;
        current->next = NULL;
        current->prev = NULL;
    }

    else{
      tail->next = current;
      tail = current;
      current->next = NULL;
    }
    length++;
    current = NULL;
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
    reverse(head, tail);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
 template <class T>
 void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint)
 {
     if(startPoint == NULL || endPoint == NULL || startPoint == endPoint){
       return; //case where empty list or one node, do nothing
     }

     ListNode * current  = startPoint->next;
     ListNode * temp = current->next;
     startPoint->next = startPoint->prev;
     startPoint->prev = current;

     while(current!=endPoint){ //instead of moving nodes, we flip what they point to
       current->next = current->prev; //function flips nodes between startpoint and endpoint
       current->prev = temp;
       current = temp;
       temp = temp->next;
     }

     endPoint->next = endPoint->prev; //flip last node
     endPoint->prev = temp;
     endPoint = startPoint; //update start and endpoint
     startPoint = current;
     head = startPoint;
     tail = endPoint;
 }
/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n)
{
    if(head == NULL || tail == NULL || head == tail) //accounts for empty list or list with one node
      return;

    ListNode * start = head; //make two pointers that start at head
    ListNode * end = head;

    while(start->next != NULL && end->next != NULL) //stops when one of them hits the end
    {
      end = start;
      for(int i = 1; i < n; i++) //create group of n nodes to reverse
      {
        if(end->next != NULL)
        end = end->next;
      }

      reverse(start, end);
      start = start->prev;
    }
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{
  if(head == NULL || tail == NULL || head==tail) //accounts for empty list or list with one node
    return;

    ListNode * move = head->next;
    ListNode * stay = move->next;

    while(stay != NULL){ //leapfrog
      (move->prev)->next = stay;
      stay->prev = move->prev;
      move->prev = tail;
      move->next = NULL;
      tail->next = move;
      move = stay->next;
      stay = move->next;
      tail = tail->next;
    }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head) {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    } else {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL) {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to spli••••••••••t a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint)
{
    if(head == NULL || splitPoint == 0) /* in which function does nothing are where
    the list is empty or if the splitPoint is before the list*/
      return head;

    ListNode * newStart = start;
    for(int i=0; i < splitPoint; i++){
      newStart = newStart->next;
    }
    (newStart->prev)->next = NULL;
    newStart->prev = NULL;

    /*cout << "Second portion of list is: " << endl;
    ListNode * print = newStart;
    while(print !=NULL){
      cout << print->data << endl;  //meant to print splitList. Works but list is super long
      print = print->next;
    }*/

    return newStart;
  }

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if (tail != NULL) {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second)
{
  if(first == NULL || second == NULL)//both empty return empty
    return NULL;
  if(first == NULL && second != NULL)//first is empty so return second
    return second;
  if(first != NULL && second == NULL)//second is empty so return first
    return first;
  if(first == second)//same list, return second
    return first;

  ListNode * f1 = first;
  ListNode * s1 = second;
  ListNode * finalHead;
  ListNode * deleteHead;

  if(first->data == second->data || first->data < second->data) //if first will be primary list
   {
     finalHead = first;
     f1 = f1->next;
     deleteHead = s1;
   }

   else //if b will be primary list;
    {
      finalHead = second;
      s1 = s1->next;
      deleteHead = f1;
    }

   ListNode * movingHead = finalHead;

   while(f1 != NULL && s1 != NULL){//ends when one is pointing at NULL
    if(f1->data < s1->data) //if f1 is smaller or second list finished
      {
        movingHead->next = f1; //case where f1 is smaller, we add it next
        f1->prev = movingHead;
        movingHead = f1;
        f1 = f1->next;
      }

    else//if s1 is smaller, add s1 whether f1 is empty or not
      {
          movingHead->next = s1; //case where s1 is smaller, we add it next
          s1->prev = movingHead;
          movingHead = s1;
          s1 = s1->next;

      }
    }

    if(f1 == NULL) //case where first being empty ended while loop, attach rest of second list
    {
      movingHead->next = s1;
      s1->prev = movingHead;
    }

    else //case where second being empty ended while loop, attach rest of first list
    {
      movingHead->next = f1;
      f1->prev = movingHead;
    }

    deleteHead = NULL; //list that should now be empty point to NULL
    return finalHead;
}


/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength)
{
    ListNode * finalHead; //this is what we will return. idk why I couldn't put it right before the else statement

    if(head == NULL || tail == NULL || chainLength == 0)
      return NULL;

    if(chainLength == 1)
      {
        start->prev = NULL; //not sure if necessary
        start->next = NULL;
        return start;
      }
      /*best way to go about this keeping O(n) mind is to create two lists, use mergesort, then merge*/
    else
    {
          ListNode * startOfSecond = start;   //create start of second list to be merged
          int i = 0;
          while(i < chainLength/2)             //increment startOfSecond until it is at halfway
            {
              startOfSecond = startOfSecond->next;
              i++;
            }

          (startOfSecond->prev)->next = NULL;    //separate second list from main list
          startOfSecond->prev = NULL;

          start = mergesort(start, chainLength/2);
          startOfSecond = mergesort(startOfSecond, chainLength - chainLength/2); //cant use chainlength/2 again in case that number is odd

          finalHead = merge(start, startOfSecond); //finally done!
    }

    return finalHead;
}
