// FILE: node.h
// PROVIDES: A class for a node in a linked list, and list manipulation
// functions, all within the namespace coen79_lab6
//
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
// TYPEDEF for the node class:
//     Each node of the list contains a piece of data and a pointer to the
//     next node. The type of the data is defined as node::value_type in a
//     typedef statement. The value_type may be any
//     of the built-in C++ classes (int, char, ...) or a class with a copy
//     constructor, an assignment operator, and a test for equality (x == y).
//
// CONSTRUCTOR for the node class:
//   node(
//     const value_type& init_data = value_type(),
//     node* init_link = NULL )
//     Postcondition: The node contains the specified data and link.
//     NOTE: The default value for the init_data is obtained from the default
//     constructor of the value_type. In the ANSI/ISO standard, this notation
//     is also allowed for the built-in types, providing a default value of
//     zero. The init_link has a default value of NULL.
//
//
// NOTE:
//   Some of the functions have a return value which is a pointer to a node.
//   Each of these  functions comes in two versions: a non-const version (where
//   the return value is node*) and a const version (where the return value
//   is const node*).
//
// EXAMPLES:
//    const node *c;
//    c->link( ) activates the const version of link
//    list_search(c,... calls the const version of list_search
//
//    node *p;
//    p->link( ) activates the non-const version of link
//    list_search(p,... calls the non-const version of list_search
//
//
//
//
// MEMBER FUNCTIONS for the node class:
//   void set_data(const value_type& new_data)
//     Postcondition: The node now contains the specified new data.
//
//   void set_link(node* new_link)
//     Postcondition: The node now contains the specified new link.
//
//   value_type data( ) const
//     Postcondition: The return value is the data from this node.
//
//   const node* link( ) const <----- const version
//   node* link( ) <----------------- non-const version
//   See the note (above) about the const version and non-const versions:
//     Postcondition: The return value is the link from this node.
//
//
//
// FUNCTIONS in the linked list toolkit:
//
//   size_t list_length(const node* head_ptr)
//     Precondition: head_ptr is the head pointer of a linked list.
//     Postcondition: The value returned is the number of nodes in the linked
//     list.
//
//   void list_head_insert(node*& head_ptr, const node::value_type& entry)
//     Precondition: head_ptr is the head pointer of a linked list.
//     Postcondition: A new node containing the given entry has been added at
//     the head of the linked list; head_ptr now points to the head of the new,
//     longer linked list.
//
//   void list_insert(node* previous_ptr, const node::value_type& entry)
//     Precondition: previous_ptr points to a node in a linked list.
//     Postcondition: A new node containing the given entry has been added
//     after the node that previous_ptr points to.
//
//   const node* list_search(const node* head_ptr, const node::value_type& target)
//   node* list_search(node* head_ptr, const node::value_type& target)
//   See the note (above) about the const version and non-const versions:
//     Precondition: head_ptr is the head pointer of a linked list.
//     Postcondition: The pointer returned points to the first node containing
//     the specified target in its data member. If there is no such node, the
//     null pointer is returned.
//
//   const node* list_locate(const node* head_ptr, size_t position)
//   node* list_locate(node* head_ptr, size_t position)
//   See the note (above) about the const version and non-const versions:
//     Precondition: head_ptr is the head pointer of a linked list, and
//     position > 0.
//     Postcondition: The pointer returned points to the node at the specified
//     position in the list. (The head node is position 1, the next node is
//     position 2, and so on). If there is no such position, then the null
//     pointer is returned.
//
//   void list_head_remove(node*& head_ptr)
//     Precondition: head_ptr is the head pointer of a linked list, with at
//     least one node.
//     Postcondition: The head node has been removed and returned to the heap;
//     head_ptr is now the head pointer of the new, shorter linked list.
//
//   void list_remove(node* previous_ptr)
//     Precondition: previous_ptr points to a node in a linked list, and this
//     is not the tail node of the list.
//     Postcondition: The node after previous_ptr has been removed from the
//     linked list.
//
//   void list_clear(node*& head_ptr)
//     Precondition: head_ptr is the head pointer of a linked list.
//     Postcondition: All nodes of the list have been returned to the heap,
//     and the head_ptr is now NULL.
//
//   void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
//     Precondition: source_ptr is the head pointer of a linked list.
//     Postcondition: head_ptr and tail_ptr are the head and tail pointers for
//     a new list that contains the same items as the list pointed to by
//     source_ptr. The original list is unaltered.
//
//   void list_piece(
//     const node* start_ptr, const node* end_ptr,
//     node*& head_ptr, node*& tail_ptr
//   )
//    Precondition: start_ptr and end_ptr are pointers to nodes on the same
//    linked list, with the start_ptr node at or before the end_ptr node
//    Postcondition: head_ptr and tail_ptr are the head and tail pointers for a
//    new list that contains the items from start_ptr up to but not including
//    end_ptr.  The end_ptr may also be NULL, in which case the new list
//    contains elements from start_ptr to the end of the list.
//
//   size_t list_occurrences(node* head_ptr, const node::value_type& target)
//     Precondition: head_ptr is the head pointer of a linked list.
//     Postcondition: The return value is the count of the number of times
//     target appears as the data portion of a node on the linked list.
//     The linked list itself is unchanged.
//
//   void list_insert_at(Node*& head_ptr, const node::value_type& entry, size_t position)
//     Precondition: head_ptr is the head pointer of a linked list, and
//     position > 0 and position <= list_length(head_ptr)+1.
//     Postcondition: A new node has been added to the linked list with entry
//     as the data. The new node occurs at the specified position in the list.
//     (The head node is position 1, the next node is position 2, and so on.)
//     Any nodes that used to be after this specified position have been
//     shifted to make room for the one new node.
//
//   node::value_type list_remove_at(node*& head_ptr, size_t position)
//     Precondition: head_ptr is the head pointer of a linked list, and
//     position > 0 and position <= list_length(head_ptr).
//     Postcondition: The node at the specified position has been removed from
//     the linked list and the function has returned a copy of the data from
//     the removed node.
//     (The head node is position 1, the next node is position 2, and so on.)
//
//   node* list_copy_segment(node* head_ptr, size_t start, size_t finish)
//     Precondition: head_ptr is the head pointer of a linked list, and
//     (1 <= start) and (start <= finish) and (finish <= list_length(head_ptr)).
//     Postcondition: The value returned is the head pointer for
//     a new list that contains copies of the items from the start position to
//     the finish position in the list that head_ptr points to.
//     (The head node is position 1, the next node is position 2, and so on.)
//     The list pointed to by head_ptr is unchanged.
//
//   void list_remove_dups(node* head_ptr)
//     Precondition: head_ptr is the head pointer of a linked list
//     Postcondition: All the duplicates are removed from the linked list
//     Example: If the list contains 1,1,1,2, after running this function the list
//     contains 1,2
//
//   void list_print (const node* head_ptr);
//     Precondition: head_ptr is the head pointer of a linked list, and
//     the operator << has been defined for the value_type
//     Postcondition: The value_type of all the nodes in the linked list are printed
//
//   node* list_detect_loop (node* head_ptr);
//     Precondition: head_ptr is the head pointer of a linked list
//     Postcondition: If there is a loop in the linked list, the returned value
//     is a pointer to the start of the loop. The returned value is NULL if
//     there is no loop in the list
//
//
// DYNAMIC MEMORY usage by the toolkit:
//   If there is insufficient dynamic memory, then the following functions throw
//   bad_alloc: the constructor, list_head_insert, list_insert, list_copy,
//   list_piece.



#ifndef COEN_79_NODE_H
#define COEN_79_NODE_H
#include <cstdlib> // Provides size_t and NULL

namespace coen79_lab6
{
    class node
    {
    public:
    	// TYPEDEF
    	typedef double value_type;

    	// CONSTRUCTOR
    	node(const value_type& init_data = value_type( ), node* init_link = NULL)
    	{
            data_field = init_data;
            link_field = init_link;
        }

    	// Member functions to set the data and link fields:
    	void set_data(const value_type& new_data) { data_field = new_data; }
    	void set_link(node* new_link) { link_field = new_link; }

    	// Constant member function to retrieve the current data:
    	value_type data( ) const { return data_field; }

    	// Two slightly different member functions to retreive
    	// the current link:
    	const node* link( ) const { return link_field; }
        node* link( ) { return link_field; }

    private:
    	value_type data_field;
    	node* link_field;
    };

    // FUNCTIONS for the linked list toolkit
    std::size_t list_length(const node* head_ptr);
    void list_head_insert(node*& head_ptr, const node::value_type& entry);
    void list_insert(node* previous_ptr, const node::value_type& entry);
    node* list_search(node* head_ptr, const node::value_type& target);
    const node* list_search
	(const node* head_ptr, const node::value_type& target);
    node* list_locate(node* head_ptr, std::size_t position);
    const node* list_locate(const node* head_ptr, std::size_t position);
    void list_head_remove(node*& head_ptr);
    void list_remove(node* previous_ptr);
    void list_clear(node*& head_ptr);
    void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr);
    
    // IMPLEMENT THE FOLLOWING FUNCTIONS
    void list_piece(node* start_ptr, node* end_ptr, node*& head_ptr, node*& tail_ptr);
    size_t list_occurrences(node* head_ptr, const node::value_type& target);
    void list_insert_at(node*& head_ptr, const node::value_type& entry, size_t position);
    node::value_type list_remove_at(node*& head_ptr, size_t position);
    node* list_copy_segment(node* head_ptr, size_t start, size_t finish);
    void list_print (const node* head_ptr);
    void list_remove_dups(node* head_ptr);
    node* list_detect_loop (node* head_ptr);

}

#endif

