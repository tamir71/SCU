// FILE: deque_iterator.h
// PROVIDES: A class for deque iterator (non-const)
//
// Dorian Clay and Tamir Enkhjargal
//
// COEN 79
// Copyright © 2016 Behnam Dezfouli. All rights reserved.
// COEN, SCU
//
// FORWARD ITERATOR to step through the items of a deque
// A deque_iterator can change the underlying deque list through the
// * operator.
// WARNING:
// This classes use std::iterator as its base class;
// Older compilers that do not support the std::iterator class can
// delete everything after the word iterator


#ifndef deque_iterator_h
#define deque_iterator_h

#include "deque.h"

namespace coen79_lab8
{
    template <class Item>
    class deque_iterator : public std::iterator<std::forward_iterator_tag, Item>
    {
        
    public:
        typedef std::size_t size_type;
        typedef Item value_type;
        
        // CONSTRUCTOR
        deque_iterator(value_type** initial_block_pointers = NULL, value_type**  initial_block_pointers_end = NULL,
                       value_type**  initial_first_bp = NULL, value_type**  initial_last_bp = NULL,
                       value_type* initial_front_ptr = NULL, value_type* initial_back_ptr = NULL,
                       size_type initial_bp_array_size = 0, size_type initial_block_size = 0,
                       value_type* initial_cursor = NULL, value_type* initial_current_boundary = NULL, value_type** initial_current_block_pointer = NULL)
        {
            block_pointers = initial_block_pointers;
            block_pointers_end = initial_block_pointers_end;
            
            first_bp = initial_first_bp;
            last_bp = initial_last_bp;
            
            front_ptr = initial_front_ptr;
            back_ptr = initial_back_ptr;
            
            bp_array_size = initial_bp_array_size;
            block_size = initial_block_size;
            
            
            cursor = initial_cursor;
            current_block_pointer = initial_current_block_pointer;
            current_boundary = initial_current_boundary;
        }
        
        // CONST MEMBER FUNCTIONS
        value_type& operator *( ) const
        { return *cursor; }
        
        
        bool operator !=(const deque_iterator other) const
        { return (block_pointers != other.block_pointers || block_pointers_end != other.block_pointers_end
                  || first_bp != other.first_bp  || last_bp != other.last_bp
                  || front_ptr != other.front_ptr  || back_ptr != other.back_ptr
                  || bp_array_size != other.bp_array_size  || block_size != other.block_size
                  || cursor != other.cursor  || current_boundary != other.current_boundary  || current_block_pointer != other.current_block_pointer ); }
        
        
        
        bool operator ==(const deque_iterator other) const
        {
            return (block_pointers == other.block_pointers && block_pointers_end == other.block_pointers_end
                    && first_bp == other.first_bp  && last_bp == other.last_bp
                    && front_ptr == other.front_ptr  && back_ptr == other.back_ptr
                    && bp_array_size == other.bp_array_size  && block_size == other.block_size
                    && cursor == other.cursor  && current_boundary == other.current_boundary  && current_block_pointer == other.current_block_pointer );
        }
        
        
        // MODIFICATION MEMBER FUNCTIONS
        deque_iterator& operator ++( ) // Prefix ++
        {
            // The cursor cannot move forward, simply return the iterator
            if (cursor == NULL)
                return *this;
            
            // There is no item after the current item.
            // Set the variables. Return the itertor.
            if (cursor == back_ptr)
            {
                cursor = NULL;
                current_boundary = NULL;
                current_block_pointer = NULL;
                return *this;
            }
            
            // Move to the next data block
            if (cursor == current_boundary)
            {
                current_block_pointer++;
                cursor = *current_block_pointer;
                current_boundary = *current_block_pointer + (block_size - 1);
            }
            // Move forward
            else
            {
                ++cursor;

            }
            return *this;
        }
        
        
        deque_iterator operator ++(int) // Postfix ++
        {
            deque_iterator original;
            original = *this;
            
            // The cursor cannot move forward, simply return the iterator
            if (cursor == NULL)
                return original;
            
            // There is no item after the current item. Set the variables. Return the itertor.
            if (cursor == back_ptr)
            {
                cursor = NULL;
                current_boundary = NULL;
                current_block_pointer = NULL;
                return original;
            }
            
            // Move to the next data block
            if (cursor == current_boundary)
            {
                current_block_pointer++;
                cursor = *current_block_pointer;
                current_boundary = *current_block_pointer + (block_size - 1);
            }
            // Move forward
            else
            {
                ++cursor;
            }
            
            return original;
        }
        
        
    private:
        // A pointer to the dynamic array of block pointers
        value_type** block_pointers;
        
        // A pointer to the final entry in the array of block pointers
        value_type**  block_pointers_end;
        
        
        // A pointer to the first block pointer that’s now being used
        value_type**  first_bp;
        
        // A pointer to the last block pointer that’s now being used
        value_type**  last_bp;
        
        value_type* front_ptr; // A pointer to the front element of the whole deque
        
        value_type* back_ptr;  // A pointer to the back element of the whole deque
        
        size_type bp_array_size; // Number of entries in the array of block pointers
        size_type block_size; // Number of entries in each block of items
        
        
        // NOTE: Up to this point, the set of pointer variables
        //       is similar to the deque class, the following pointers
        //       enable the itertor to move forward and point to the next item.
        
        value_type* cursor; // A pointer to the "current" item
        value_type** current_block_pointer; // A pointer to the data block which includes the item the "cursor" is pointing to
        value_type* current_boundary; // A pointer to the end of the data block the "cursor" is pointing to
    };
}

#endif /* deque_iterator_h */
