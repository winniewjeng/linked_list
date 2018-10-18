
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include <cassert>
using namespace std;

template <typename T>
//node is a 2-part struct, consisting of item and node pointer
struct node {
    T _item;
    node<T>* _next;

    //constructor

    node(const T& item = T(), node<T> *next = nullptr) {
        _item = item;
        _next = next;
    }

};

//IMPLEMENTED

template<typename T>
//insert_head takes in the address of head_ptr and item to populate the new head node
//and returns the address of the new head_ptr
node<T>* insert_head(node<T>* &head_ptr, const T& item) {
    //1. create a new node
    //2. next points to the head_ptr
    //3. point head_ptr to where temp is pointing to
    //4. return head_ptr

    node<T>* new_node = new node<T>(item);
    new_node->_next = head_ptr;
    head_ptr = new_node;
    return head_ptr;

}

//IMPLEMENTED

template<typename T>
//insert_after takes in the address of the mark, and create a new node after the 
//mark and populate the new node with item and returns the address of the new node ptr
node<T>* insert_after(node<T>* head_ptr, node<T>* mark, const T& item) {
    //1. create a new node named new_node, populated with item
    //2. new_node's _next points to mark's _next
    //3. mark's _next now points to new_node
    //4. return new_node

    //    node<T>* new_node = new node<T>(item);
    //    new_node->_next = mark->_next;
    //    mark->_next = new_node;

    assert(mark != nullptr);



    return insert_head(mark->_next, item);
}

//IMPLEMENTED

template<typename T>
//insert_before takes in the address of the mark, and create a new node before the 
//mark and populate the new node with item and returns the address of the new node ptr
node<T>* insert_before(node<T>* head_ptr, node<T>* mark, const T& item) {
    //1. create a NEW node named new_node, populated with item
    //2. get a walker to traverse down the linked list to node where the _next points to mark
    //3. the node whose _next pointed to mark now points to new_node
    //5. new_node's _next points to mark
    //6. return insert_ptr
    node<T>* new_node = new node<T>(item);

    node<T>* walker = head_ptr;

    while (walker != nullptr) { //don't fall off!
        if (walker->_next == mark) {
            // walker is pointing to the node before the mark
            walker->_next = new_node;
            //walker -> next = new node<T>(item);
            new_node->_next = mark;
            return new_node;
        }

        walker = walker->_next;
    }
    //if you get here, that mean you never found mark:
    //  mark was not even on this list.
    //FU!
    assert(false);
    return new_node;
}

//Not yet tested

template <typename T>
//find the pointer to the previous node of prevToThis
node<T>* PreviousNode(node<T>* head_ptr, node<T>* prevToThis) {
    node<T>* walker = head_ptr;
    while (walker != nullptr) {
        if (walker->_next == prevToThis) {
            return walker;
        }
        walker = walker->_next;
    }
    return nullptr;
}


//IMPLEMENTED

template<typename T>
//get a walker and traverse down the linked list and print out the items in the list
void print_list(node<T>* head_ptr) {
    //1. get a walker
    //2. keep walking down linked list as long as walker != nullptr
    //3. output
    node<T>* walker = head_ptr;
    while (walker != nullptr) {
        cout << " [" << walker->_item << "] -->";
        //traverse the walker down. New syntax!
        walker = walker->_next;
    }
    cout << "|||" << endl;
}

//NOT YET IMPLEMENTED

template <typename T>
//duplicate the list...
node<T>* copy_list(node<T>* head_ptr) {
    
    if(head_ptr->_next == nullptr) {
        return head_ptr;
    }

    node<T>* new_list_head = new node<T>(head_ptr->_item);
    node<T>* og_list_walker = head_ptr;
    node<T>* new_list_walker = new_list_head;


    while (og_list_walker != nullptr) {
        cout << "hi" << endl;
        insert_head(new_list_head, og_list_walker->_item); //head_ptr, item
        og_list_walker = og_list_walker->_next;
    }
    
    return new_list_head;
}

//NOT YET IMPLEMENTED

//template<typename T>
////recursive?
//void print_list_backward(node<T>* head_ptr) {
//
//}

//IMPLEMENTED

template<typename T>
//fuck you
T delete_head(node<T>*& head_ptr) {

    //0. assert that the list is not empty
    //1. get a temp node_ptr to point to the head node
    //2. get a T variable to store item in head node
    //3. get head_ptr to skip the head node and point to the node after it
    //4. delete temp, which points to the head node

    assert(head_ptr != nullptr);
    T hold_this = head_ptr->_item;
    node<T>* temp;
    temp = head_ptr;
    head_ptr = head_ptr->_next;
    delete temp;

    return hold_this;
}


//IMPLEMENTED

template<typename T>
//delete the node from linked list and return the item in node
T delete_node(node<T>* head_ptr, node<T>* mark) {
    //1. get a walker to traverse down the linked list & find mark
    //2. when node._next == mark is found:
    //3. store the item in temp T
    //4. node._next = mark._next
    //5. no need of garbage collection?

    T temp_item;
    node<T>* walker = head_ptr;
    while (walker != nullptr) {
        if (walker->_next == mark) {
            node<T>* temp = mark;
            temp_item = mark->_item;
            walker->_next = mark->_next;
            delete temp; ////
            return temp_item;
        }
        walker = walker->_next;
    }

    return 0;
}

//IMPLEMENTED

template<typename T>
//find an item in linked list. Return the address of the node where item is found -- ALSO CALLED searchList
node<T>* search_list(node<T>* head_ptr, const T& item) {
    //1. get a walker to traverse down the linked list
    //2. if ._item == item, return the walker as it's on that node
    node<T>* walker = head_ptr;
    while (walker != nullptr) {
        if (walker->_item == item) {
            return walker;
        }
        walker = walker->_next;
    }
    //return nullptr if item is not found
    return nullptr;
}

//IMPLEMENTED

template<typename T>
//delete all node
void clear_list(node<T>*& head_ptr) {
    node<T>* walker = head_ptr;

    while (walker != nullptr) {
        delete_head(head_ptr);
        walker = walker->_next;
    }
}

//Implemented 

template<typename T>
//_item at this position
T& At(node<T>* head_ptr, int pos) {

    int count = 0;
    node<T>* walker = head_ptr;

    while (count != pos) {
        walker = walker->_next;
        count++;
    }
    return walker->_item;
}


//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//      Sorted List Routines. order: 0: ascending, order: other: descending
//                              Assume a Sorted List
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

//Not clear on implementation

template <typename T>
//insert
node<T>* InsertSorted(node<T>* &head_ptr, T item, bool ascending = true) {

    //insert item at head of linked list
    insert_head(head_ptr, item);

    node<T>* walker1 = head_ptr;
    node<T>* walker2 = head_ptr->_next;

    while (walker1 != nullptr && walker2 != nullptr) {

        while (walker2 != nullptr) {

            if (walker1->_item > walker2->_item) {
                //swap
                T temp = walker1->_item;
                walker1->_item = walker2->_item;
                walker2->_item = temp;
            }
            //move walker2
            walker2 = walker2->_next;
        }
        walker1 = walker1->_next;
        //reset walker2
        walker2 = walker1->_next;
    }
    return head_ptr;

    //    node<T>* place_here = WhereThisGoes(head_ptr, item, ascending = true);
    //    return insert_after(head_ptr, place_here, item);


}

//Not yet implemented 
template <typename T>
//insert or add if a dup
node<T>* InsertSorted_and_add(node<T>* &head_ptr, T item, bool ascending = true);

//Implemented -- not yet tested

template <typename T>
//node after which this item goes //order: 0 ascending
node<T>* WhereThisGoes(node<T>* head_ptr, T item, bool ascending = true) {

    node<T>* walker = head_ptr;
    while (walker != nullptr) {
        if (walker->_item == item) {
            return walker;
        }
        walker = walker->_next;
    }
    return nullptr;
}

//Implemented -- not yet tested

template <typename T>
//Last Node in the list
node<T>* LastNode(node<T>* head_ptr) {
    node<T> walker = head_ptr;
    while (walker != nullptr) {
        walker = walker._next;
    }
    return walker;
}

#endif /* LINKED_LIST_H */

