/** @file: my_memory.cpp */


#ifndef MY_MEMORY_IMPL
#define MY_MEMORY_IMPL

#include "my_memory.h"
#include <iostream>
using namespace std;

/******** my_unique_pointer class declaration **********/
 
/** Default Constructor -
 * Initializes the object to nullptr.
 */
template <class T>
my_unique_ptr<T>::my_unique_ptr() : pointer(nullptr) { } ;

/** Parametrized Constructor -
 * Takes a pointer Type* as a paramenter
 * Sets the object to point there.
 */
template <class T>
my_unique_ptr<T>::my_unique_ptr (T * new_pointer) : pointer(new_pointer) { };

/** Move Constructor -
 * Takes my_unique_ptr object and constructs a new object from it.
 */
template <class T>
my_unique_ptr<T>::my_unique_ptr( my_unique_ptr<T> && rhs ) : pointer(rhs.pointer)
{
    rhs.pointer = nullptr;
}

/** Destructor -
 * Releases the block of memory pointed by the object
 */
template <class T>
my_unique_ptr<T>::~my_unique_ptr<T>()
{
    delete pointer;
    pointer = nullptr;
}

/** Dereference * Operator -
 * Returns a reference to the item pointed by the object
 */
template <class T>
T& my_unique_ptr<T>::operator* () //const
{
    return *pointer;
}

/** -> Operator -
 * Returns the pointer to the object.
 * Allows to use the my_unique_ptr for class member access.
 */
template <class T>
T* my_unique_ptr<T>::operator-> () const
{
    return pointer;
}

/** Move assignment operator */
template <class T>
my_unique_ptr<T>& my_unique_ptr<T>::operator = ( my_unique_ptr && rhs )
{
    swap(rhs.pointer,pointer);
    
    //delete rhs.pointer;
    rhs.pointer = nullptr;
    return *this;
}
/*********************** end my_unique_pointer *********************/

//////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

/******************** my_shared_pointer *************************/

/**  Default Constructor */
template <class S>
my_shared_ptr<S>::my_shared_ptr() : pointer(nullptr), pointer_counter(nullptr) { };

/** Dereference * Operator */
template <class S>
S& my_shared_ptr<S>::operator* ()
{
    return *pointer;
}

/** Arrow Operator */
template <class S>
S* my_shared_ptr<S>::operator->() const
{
    return pointer;
}

/** Parameterized Constructor */
template <class S>
my_shared_ptr<S>::my_shared_ptr(S * newpointer) : pointer(newpointer)
{
    //initialize pointer
    pointer_counter = new int;
    *pointer_counter = 1;
}

/** Copy Constructor */
template <class S>
my_shared_ptr<S>::my_shared_ptr (const my_shared_ptr & rhs) : pointer(rhs.pointer), pointer_counter(rhs.pointer_counter)
{
    //if pointer is null, it cant be incremented
    if(pointer_counter != nullptr)
    {
        ++(*pointer_counter);
    }
}

/** Move Constructor */
template <class S>
my_shared_ptr<S>::my_shared_ptr( my_shared_ptr<S> && rhs ) : pointer(rhs.pointer), pointer_counter(rhs.pointer_counter)
{
    rhs.pointer = nullptr;
    rhs.pointer_counter = nullptr;
}

/** Copy Assignment Operator */
template <class S>
my_shared_ptr<S> & my_shared_ptr<S>::operator = (const my_shared_ptr & rhs)
{
    // test if pointer being copied to  is pointing somemwhere already
    
    //if pointer is not pointing somewhere else
    if(pointer == nullptr)
    {
        //copy pointers
        pointer = rhs.pointer;
        pointer_counter = rhs.pointer_counter;
        
        //increment counter
        ++(*pointer_counter);
    }
    // if pointer being copied to is pointing somewhere
    else
    {
        //decrement old pointer
        --(*pointer_counter);
        
        //if nothing is being pointed to memory block, it must be freed.
        if(*pointer_counter == 0)
        {
            delete pointer;
            delete pointer_counter;
        }
        
        //copy new pointers
        pointer = rhs.pointer;
        pointer_counter = rhs.pointer_counter;
        ++(*pointer_counter);
    }
    
    return *this;
}


/** Move Assignment Operator */
template <class S>
my_shared_ptr<S>& my_shared_ptr<S>::operator = ( my_shared_ptr && rhs )
{    
    //if pointer is alreay pointing somewhere
    if(pointer != nullptr)
    {
        //decrement old block
        (*pointer_counter)--;
        
        //if counter is equal to zero, block must be freed
        if(*pointer_counter == 0)
        {
            delete pointer;
            delete pointer_counter;
        }
        
        pointer = nullptr;
        pointer_counter = nullptr;
    }
    
    swap(pointer,rhs.pointer);
    swap(pointer_counter,rhs.pointer_counter);
    
    return *this;
}
/** Destructor */
template <class S>
my_shared_ptr<S>::~my_shared_ptr()
{
     //pointer is pointing somewhere
     if(pointer != nullptr)
     {
        //decrement b/c it will be deleted shortly
        (*pointer_counter)--;
        
        // this is the last pointer
         // memory can be freed
        if(*pointer_counter == 0 )
        {
            delete pointer_counter;
            pointer_counter = nullptr;
            
            delete pointer;
            pointer = nullptr;
        }
         // more pointers exists, cannot delete yet.
        else
        {
            pointer_counter = nullptr;
        }
    }
}

#endif /** End my_memory.cpp */
