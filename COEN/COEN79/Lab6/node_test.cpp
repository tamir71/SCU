#include "node.h"
#include <iostream>

using namespace std;
using namespace coen79_lab6;


int main(int argc, char const *argv[]) {
    // Make a list.
    node *my_list = NULL;
    node* temp;
    list_head_insert(my_list, 4.5);
    list_head_insert(my_list, 4);
    list_head_insert(my_list, 3.5);
    list_head_insert(my_list, 3);
    list_head_insert(my_list, 2.5);
    list_head_insert(my_list, 2);
    list_head_insert(my_list, 1.5);
    list_head_insert(my_list, 1);
    cout << "The list: ";
    list_print(my_list);

    // Testing list_piece functionality.
    {
        cout << " *** list_piece tests *** " << endl;
        node *head, *tail;
        // Empty
        list_piece(NULL,NULL,head,tail);
        cout << "Empty: ";
        list_print(head);
        // Just first item.
        list_piece(my_list,my_list,head,tail);
        cout << "Both at head: ";
        list_print(head);
        // A few, starting with head.
        list_piece(my_list,list_locate(my_list,4),head,tail);
        cout << "Three from head: ";
        list_print(head);
        // A few in middle
        list_piece(list_locate(my_list,3),list_locate(my_list,6),head,tail);
        cout << "Three in middle: ";
        list_print(head);
        // A few on end
        list_piece(list_locate(my_list,6),NULL,head,tail);
        cout << "Three on end: ";
        list_print(head);
        // Just the end
        list_piece(list_locate(my_list,list_length(my_list)),NULL,head,tail);
        cout << "The end: ";
        list_print(head);
        // The whole list
        list_piece(my_list,NULL,head,tail);
        cout << "Full list: ";
        list_print(head);
    }

    // Testing list_copy_segment functionality.
    {
        cout << endl << " *** list_copy_segment tests *** " << endl;
        // Just first item.
        cout << "Both at head: ";
        list_print(list_copy_segment(my_list,1,1));
        // A few, starting with head.
        cout << "Three from head: ";
        list_print(list_copy_segment(my_list,1,3));
        // A few in middle
        cout << "Three in middle: ";
        list_print(list_copy_segment(my_list,3,5));
        // A few on end
        cout << "Three on end: ";
        list_print(list_copy_segment(my_list,6,list_length(my_list)));
        // Just the end
        cout << "The end: ";
        list_print(list_copy_segment(my_list,list_length(my_list),list_length(my_list)));
        // The whole list
        cout << "Full list: ";
        list_print(list_copy_segment(my_list,1,list_length(my_list)));
    }

    // Testing list_insert_at functionality.
    {
        cout << endl << " *** list_insert_at tests *** " << endl;
        // Insert at front
        list_insert_at(my_list, 0.5, 1);
        cout << "Inserting 0.5 at front:\n\t";
        list_print(my_list);
        // Insert at back
        list_insert_at(my_list, 4.75, list_length(my_list)+1);
        cout << "Inserting 4.75 at back:\n\t";
        list_print(my_list);
        // Insert in middle
        list_insert_at(my_list, 2, 5);
        cout << "Inserting 2.25 in middle:\n\t";
        list_print(my_list);
        // Insert into empty list
        temp = NULL;
        list_insert_at(temp, -4.3, 1);
        cout << "Inserting -4.3 into an empty list:\n\t";
        list_print(temp);
        list_clear(temp);
    }

    // Testing list_piece functionality.
    cout << endl << " *** list_occurrences tests *** " << endl;
    list_insert_at(my_list, 2, 5);
    list_insert_at(my_list, 2, 5);
    cout << "The list: ";
    list_print(my_list);
    cout << "Number of 0.5's: " << list_occurrences(my_list, 0.5) << endl;
    cout << "Number of 4.75's: " << list_occurrences(my_list, 4.75) << endl;
    cout << "Number of 3's: " << list_occurrences(my_list, 3) << endl;
    cout << "Number of 2's: " << list_occurrences(my_list, 2) << endl;
    cout << "Number of 0's: " << list_occurrences(my_list, 0) << endl;

    // Testing list_piece functionality.
    cout << endl << " *** list_remove_at tests *** " << endl;
    cout << "The list: ";
    list_print(my_list);
    cout << "Removing first item:\n\t";
    list_remove_at(my_list, 1);
    list_print(my_list);
    cout << "Removing last item:\n\t";
    list_remove_at(my_list, list_length(my_list));
    list_print(my_list);
    cout << "Removing 3.5 from the middle:\n\t";
    list_remove_at(my_list, 9);
    list_print(my_list);

    
    {
        cout << endl << " *** list_remove_dups tests *** " << endl;

        node* head_ptr = NULL;
        list_head_insert(head_ptr, 1);
        list_head_insert(head_ptr, 1);
        list_head_insert(head_ptr, 1);
        list_head_insert(head_ptr, 1);
        
        list_print(head_ptr);
        list_remove_dups(head_ptr);
        list_print(head_ptr);
    }
    
    {
        cout << endl << " *** list_detect_loop tests *** " << endl;

        node* head_ptr2 = NULL;
        list_head_insert(head_ptr2, 10);
        list_head_insert(head_ptr2, 9);
        list_head_insert(head_ptr2, 8);
        list_head_insert(head_ptr2, 7);
        list_head_insert(head_ptr2, 6);
        list_head_insert(head_ptr2, 5);
        list_head_insert(head_ptr2, 4);
        list_head_insert(head_ptr2, 3);
        list_head_insert(head_ptr2, 2);
        list_head_insert(head_ptr2, 1);
        
        node *tmp;
        tmp = list_locate (head_ptr2, 10);
        tmp->set_link(head_ptr2->link()->link()->link()->link());
        
        node *loop_start = NULL;
        loop_start = list_detect_loop(head_ptr2);
        if (loop_start != NULL)
            std::cout << "Loop start location is: " << loop_start->data() << std::endl;
    }
    
    return 0;
}
