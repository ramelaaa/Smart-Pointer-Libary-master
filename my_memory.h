/** @file: my_memory.h */

#ifndef MY_MEMORY_H
#define MY_MEMORY_H

/** my_unique_pointer class declaration */
template <class T>
class my_unique_ptr
{
private:
    
    /** A pointer of Type T */
    T *pointer;
    
public:
    
    /** Default Constructor -
     * Initializes the object to nullptr.
     */
    my_unique_ptr();
    
    /** Parametrized Constructor -
     * Takes a pointer Type* as a paramenter
     * Sets the object to point there.
     */
    my_unique_ptr (T * new_pointer);
    
    /** Move Constructor -
     * Takes my_unique_ptr object and constructs a new object from it.
     * Assumes control of the parameter's pointers and the parameter's
     * own pointers are set to nullptr.
     */
    my_unique_ptr ( my_unique_ptr && rhs );
    
    /** Copy Constructor -
     * Copy Constructor is explicitly deleted.
     */
    my_unique_ptr (const T &rhs) = delete;

    /** Destructor -
     * Releases the block of memory pointed by the object
     */
    ~my_unique_ptr();
    
    /** Dereference * Operator -
     * Returns a reference to the item pointed by the object
     */
    T& operator* ();

    /** -> Operator -
     * Returns the pointer to the object.
     * Allows to use the my_unique_ptr for class member access.
     */
    T* operator-> () const;
    
    /** Move Assignment Operator -
     * Hands over the pointers from the parameter to a different
     * my_unique_ptr object. The parameters pointers are set to null.
     * Note: If the pointer is already pointing somewhere,the pointer is set to null
     * before assignment. If the counter is 0 after this, the pointers are
     * deleted.
     */
    my_unique_ptr & operator = ( my_unique_ptr && rhs );
    
    /** Copy Assignment Operator -
     * Copy Assignment Opeator is explicitly deleted.
     */
    my_unique_ptr & operator = ( const my_unique_ptr & rhs ) = delete;
    
    
}; /** end my_unique_pointer */

/** my_shared_pointer class declaration */
template <class S>
class my_shared_ptr {
private:
    
    // A pointer of type S.
    S * pointer;
    
    /** A pointer of type int that points a counter that
     * indicates how many pointers are pointing at a
     * particular memory address.
     */
    int * pointer_counter;
    
public:
    
    /** Default Constructor
     *  Creates an instance of my_shared_ptr and
     * sets all inner pointers to nullptr.
     */
    my_shared_ptr();
    
    /** Paremetrized Constructor
     * Takes Type* as a parameter, creates a new
     * instance and sets the object to point there.
     * Counter is intialized and set to 1
     */
    my_shared_ptr( S * newpointer );
    
    /** Copy Constructor -
     * Takes a constant reference of an already constructed
     * my_shared_pointer object and uses copies the pointers to
     * construct a new my_shared_pointer object.
     * As a result, the counter is incremented by 1.
     * Note: If my_shared_object pointers are set to  null, the
     * counter is not incremented.
     */
    my_shared_ptr (const my_shared_ptr &rhs);
    
    /** Move Constructor -
     * Takes rvalue reference of an already constructed my_shared_ptr
     * reference and constructs a new object from it. This constructor
     * will take ownership of the parameter's pointer and set the parameter's
     * pointers to null pointers. This operation will not
     * increment the pointer counter.
     */
    my_shared_ptr ( my_shared_ptr && rhs);
    
    /** Dereference * Operator -
     * Returns a reference to the item pointed by the object
     */
    S& operator* ();
    
    /** -> Operator -
     * Returns the pointer to the object.
     * Allows to use the my_unique_ptr for class member access.
     */
    S* operator-> () const;
    
    /** Copy Assignment Operator -
     * Creates a duplicate of the parameter where the the pointer
     * assumes the parameter's pointers. This operation increments
     * the counter by 1.
     * Note: If the pointer is already pointing somewhere, that block's
     * pointer is decremented by one and both pointers are set to null
     * before assignment. If the counter is 0 after this, the pointers are
     * deleted.
     */
    my_shared_ptr & operator = ( const my_shared_ptr & rhs );
    
    /** Move Assignment Operator -
     * Hands over the pointers from the parameter to a different
     * my_shared_ptr object. The parameters pointers are set to null and
     * the program counter remains the same.
     * Note: If the pointer is already pointing somewhere, that block's
     * pointer is decremented by one and both pointers are set to null
     * before assignment. If the counter is 0 after this, the pointers are
     * deleted.
     */
    my_shared_ptr & operator = (my_shared_ptr && rhs);
    
    /** Destructor -
     * If there are multiple pointers pointing to a single memory block,
     * the each individual program counter pointers are decremented and
     * set to null. One the counter equals zero, the pointers are deleted.s
     */
    ~my_shared_ptr();
    
}; /** end my_shared_pointer */


#include "my_memory.cpp"

#endif /** MY_MEMORY_H */
