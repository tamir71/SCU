
#ifndef ITEM_CPP
#define ITEM_CPP

#include "node.h"

namespace coen79_lab7 {
    // Constructor
    node::node(const std::string &itemName, const float &newPrice, node *nextNode) {
        name = itemName;
        price = newPrice;
        link = nextNode;
    }
    // Setter modification methods
    void node::setName(const std::string &newName) {
        name = newName;
    }
    void node::setPrice(const float &newPrice) {
        price = newPrice;
    }
    void node::setLink(node *new_next) {
        link = new_next;
    }
    // Getter methods
    node* node::getLink() {
        return link;
    }
    const node* node::getLink() const {
        return link;
    }
    std::string node::getName() const{
        return name;
    }
    float node::getPrice() const {
        return price;
    }
    // Create a list with a head pointer
    void list_init(node*& head, node*& tail, const std::string& newName, const float& newPrice) {
        head = new node(newName, newPrice, NULL);                               // Create a new list, with the name and price, and set the head to the new node
        tail = head;                                                            // Also update the tail pointer
    }
    // Insert a node to the tail
    void list_tail_insert(node*& tail, const std::string &newName, const float &newPrice) {
        tail->setLink(new node(newName, newPrice, NULL));
        tail = tail->getLink();
    }
    // Delete the list of products
    void list_clear(node*& head) {
        while(head != NULL)
            list_head_remove(head);
    }
    // Copy a list over to the other
    void list_copy(const node *old_head, node* &new_head, node* &new_tail) {
        new_head = NULL;
        new_tail = new_head;    
        const node *cur = old_head;
        while (cur != NULL) {
            if (new_head == NULL) {
                new_head = new node(cur->getName(), cur->getPrice());
                new_tail = new_head;
            }
            else {
                new_tail->setLink(new node(cur->getName(), cur->getPrice()));
                new_tail = new_tail->getLink();
            }
            cur=cur->getLink();
        }
    }
    // Remove the head of the list and adjust head pointer
    void list_head_remove(node*& head) {
        node* delete_ptr = head;
        head = head->getLink();
        delete delete_ptr;
    }
    // Print the list starting from head
    void list_print(node *head) {
        node *cur = head;
        while (cur != NULL) {
            std::cout << "- " << cur->getName() << ", where the price is $" << cur->getPrice() << std::endl;
            cur = cur->getLink();
        }
    }
    // Check if a list contains a product name
    bool list_contains_item(node *head_ptr, const std::string& newName) {
        return (list_search(head_ptr, newName) != NULL);
    }
    // Check if a list contains the target
    node* list_search(node* head_ptr, const std::string& target) {
        node *cursor;
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->getLink( ))
            if (target == cursor->getName( ))
                return cursor;
        return NULL;
    }
    // Constant version
    const node* list_search(const node* head_ptr, const std::string & target) {
        const node *cursor;
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->getLink( ))
            if (target == cursor->getName( ))
                return cursor;
        return NULL;
    }
}

#endif
