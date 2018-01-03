#include "deque.h"

template <class Object>
Deque<Object>::Deque( ) {                          // the constructor
  front = back = NULL;
}

template <class Object>
Deque<Object>::Deque( const Deque &rhs ) {         // the copy constructor
  front = back = NULL;
  *this = rhs;
}

template <class Object>
Deque<Object>::~Deque( ) {                         // the destructor
  clear( );
}

template <class Object>
bool Deque<Object>::isEmpty( ) const {             // check if a deque is empty
  return front == NULL;
}

template <class Object>
int Deque<Object>::size( ) const {                 // retrieves # deque nodes
  int i = 0;
  for ( DequeNode *ptr = front; ptr != nullptr; ptr = ptr->next ) // traverse que
    ++i;

  return i;
}

template <class Object>
const Object &Deque<Object>::getFront( ) const {   // retrieve the front node
  if ( isEmpty( ) )
    throw "empty queue";
  return front->item;
}

template <class Object>
const Object &Deque<Object>::getBack( ) const {    // retrieve the tail node
  if ( isEmpty( ) )
    throw "empty queue";
  return back->item;
}

template <class Object>
void Deque<Object>::clear( ) {          // clean up all entries.
  while ( !isEmpty( ) )                 // dequeue till the queue gets empty.
    removeFront( );
}

template <class Object>
void Deque<Object>::addFront( const Object &obj ) {// add a new node to  front
  // Implement the function body.
    DequeNode *newNode = new DequeNode();
    newNode->item = obj;

    if(size() == 0) {
        front = newNode;
        back = newNode;
    }
    else {
        newNode->next = front;
        front->prev = newNode;
        front = newNode;
    }

}

template <class Object>
void Deque<Object>::addBack( const Object &obj ) { // add a new node to tail
  // Implement the function body.
    DequeNode *newNode = new DequeNode;
    newNode->item = obj;
    if(size() == 0) {
        front = newNode;
        back = newNode;
    }
    else {
        back->next = newNode;
        newNode->prev = back;
        back = newNode;
    }
}

template <class Object>
Object Deque<Object>::removeFront( ) {  // remove the front node
  // Implement the function body.
    bool ableToRemove = (size() > 0);

    Object data = NULL;

    if(ableToRemove) {
        data = front->item;
        if (size() == 1) {
            delete front;
            front = nullptr;
            back = nullptr;
        } else {
            front = front ->next;
            front ->prev ->next = nullptr;
            delete front ->prev;
            front ->prev = nullptr;

        }
    }
    return data;

}

template <class Object>
Object Deque<Object>::removeBack( ) {   // remove the tail node
    bool ableToRemove = (size() > 0);
    Object data = NULL;

    if(ableToRemove) {
        data = back->item;
        if (size() == 1) {
            front = nullptr;
            back = nullptr;
        }
        else {
            back = back->prev;
            back -> next -> prev = nullptr;
            delete back->next;
            back->next = nullptr;
            }

        }
    return data;
}

template <class Object>
const Deque<Object> &Deque<Object>::operator=( const Deque &rhs ) { // assign
  if ( this != &rhs ) { // avoid self assignment
    clear( );
    for ( DequeNode *rptr = rhs.front; rptr != NULL; rptr = rptr->next )
      addBack( rptr->item );
  }
  return *this;
}


