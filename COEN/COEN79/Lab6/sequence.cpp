//  FILE: sequence.cpp
//  CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
//
//  Tamir Enkhjargal
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
//  INVARIANT for the sequence class
//  1. The number of items in the sequence is stored in the member variable "many_nodes"
//
//  2. For an empty sequence, we do not care what is stored in any of data and head_ptr
//      and tail_ptr point to NULL; for a non-empty sequence, the items stored in the
//      sequence can be accessed using head_ptr and tail_ptr and we don't care what is
//      stored in the rest of the data.
//
//  3. If there is a current item, then it lies in *cursor; if there is no
//     current item, then cursor* equals NULL.
//
//  4. If there is a previous item, then it lies in precursor*.  If there is no previous
//       item, then precursor equals NULL.


#include <iostream>
#include <algorithm>        //provides copy function
#include <cassert>          //for assert function
#include "sequence.h"
#include "node.h"           // provides node class

using namespace std; //For copy function

namespace coen79_lab6
{

    // CONSTRUCTOR IMPLEMENTATION for default constructor
    sequence::sequence() {
        init();
    }

    // Copy Constructor
    sequence::sequence(const sequence& source) {
        init();
        *this = source;
    }

    // Destructor
    sequence::~sequence() {
        list_clear(head_ptr);                               // List_clear deletes all nodes in list
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        many_nodes = 0;
    }

    void sequence::start() {
        cursor = head_ptr;                                  // Point to front of list
        precursor = NULL;                                   // Precursor is nothing
    }

    void sequence::end() {
        if(many_nodes == 0)                                 // If empty, return
            return;
        cursor = tail_ptr;                                  // Set cursor at tail
        if(head_ptr == tail_ptr)                            // If only one node in list
            precursor = NULL;                               // Precursor is null
        else
            precursor = list_locate(head_ptr, many_nodes-1);        // If not, precursor points to tail - 1
    }

    void sequence::advance() {
        assert(is_item());
        precursor = cursor;
        cursor = cursor->link();
    }

    void sequence::insert(const value_type& entry) {
        if(!is_item() || precursor == NULL) {               // If empty or no current item
            list_head_insert(head_ptr, entry);              // Insert to front of list
            if(tail_ptr = NULL)                             // If also no tail, set tail to front
                tail_ptr = head_ptr;
            cursor = head_ptr;                              // Set current to head
            precursor = NULL;                               // Precursor is NULL
            many_nodes++;
        }
        else {                                              // If list is not empty and current item exists
            list_insert(precursor, entry);                  // Insert into precursor
            cursor = precursor->link();                     // Then point precursor to cursor
            many_nodes++;
        }
    }

    void sequence::attach(const value_type& entry) {
        cout << "attach start";
        if(head_ptr == NULL) {                              // If empty
            cout << "1";
            list_head_insert(head_ptr, entry);              // Insert into head pointer
            tail_ptr = head_ptr;                            // Tail is also at head now
            cursor = head_ptr;                              // Put cursor at head
            precursor = NULL;                               // precursor is NULL
        }
        else if(cursor == NULL) {                           // If cursor NULL, then precursor is at tail
            cout << "cursor is null if statement";
            list_insert(tail_ptr, entry);                   // Therefore insert into tail
            cursor = tail_ptr->link();
            precursor = tail_ptr;                           // Precursor now at old tail
            tail_ptr = tail_ptr->link();                    // Update tail pointer
        }
        else {                                              // Else, insert into middle somewhere
            cout << "3";
            list_insert(cursor, entry);                     // Insert where cursor is
            precursor = cursor;                             // Set precursor to old cursor
            cursor = cursor->link();                        // Update cursor
            if(cursor->link() == NULL)                      // If cursor is now NULL, then tail is at cursor
                tail_ptr = cursor;
        }
        many_nodes++;
    }

    void sequence::operator=(const sequence& source) {
        if(this == &source)                                 // Check for self-assignment
            return;
        list_copy(source.head_ptr, head_ptr, tail_ptr);     // Copy from source to head-to-tail
        many_nodes = source.many_nodes;                     // Copy many nodes
        start();                                            // Call start(), setting all things to null/0
        node* tmp = source.head_ptr;                        // Temporary node, since we can't edit source
        while(tmp != source.cursor) {                       // Iterate until we find the source's cursor
            advance();                                      // keep pushing this->cursor
            tmp = tmp->link();                              // keep pushing this->link
        }
    }

    void sequence::remove_current() {
        assert(is_item());                                  // Check that cursor points to something first
        if(cursor == head_ptr) {                            // If we're at head
            if(head_ptr == tail_ptr) {                      // If only one object
                list_head_remove(head_ptr);                 // Remove head
                head_ptr = NULL;                            // set all to NULL
                tail_ptr = NULL;
                cursor = NULL;
                precursor = NULL;
            }
            else {                                          // If size > 1 and at front
                list_head_remove(head_ptr);                 // Remove head
                cursor = head_ptr;                          // Point to new head
                precursor = NULL;                           // Precursor is NULL
            }
        }
        else if(cursor == tail_ptr) {                       // Else, cursor at end
            list_remove(precursor);                         // list_remove deletes node after precursor
            tail_ptr = precursor;                           // then shift tail pointer left once
            cursor = NULL;                                  // cursor is now NULL
        }
        else {                                              // Else, cursor in middle
            list_remove(precursor);                         // Remove node after precursor
            cursor = cursor->link();                        // Then cursor points one to right after 'shifting'
        }
        many_nodes--;
    }

    sequence::size_type sequence::size() const {
        return many_nodes;
    }

    bool sequence::is_item() const {
        if(cursor == NULL)                                  // Just checking if cursor points to anything
            return false;
        else
            return true;
    }
    
    sequence::value_type sequence::current() const {
        assert(is_item());
        return cursor->data();
    }

    // Default private member variable initialization function.
    void sequence::init() {
        head_ptr = NULL;            // Initializing pointers to NULL
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        many_nodes = 0;             // Initializiing many_nodes (or our counter) to 0
    }
    
}
