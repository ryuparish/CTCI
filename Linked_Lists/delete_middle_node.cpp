#include <iostream>

#include <stdlib.h>

// Implementing a queue using only a linked list
// NO MEMORY LEAKAGE WOO HOO!
// Memory Management rules:
//  1. Remember to create destructor that uses two pointers.
//  2. Pointers do not always need to be allocated (new), especially if they are walkers.
//  3. Always free the head node after setting the walker ahead in the destructor
//  4. Default to using a NULL pointer rather than new. new will almost always be the cause of memory leakage.
//  5. Valgrind is not always accurate and one single missed allocation can be causing an assortment of leaks directly and indirectly at the same time.

// Pointers are like little wizards that use their wand to manipulate objects



struct link{
    int value = 0;
    link* next = NULL;
};

struct linkedList{
    // Using a traveler node will give up the reduced time complexity for
    // the cost of having easy access to any node in the middle and not having a tail pointer allocated
    link* headNode = new link;
    link* travelerNode = NULL;

    // Constructor to set the head of the linked list object
    linkedList(){
        travelerNode = headNode;
    }

    // Adding a node with a value instead of passing a node because it would be more convenient
    void addNode(int new_value){
        link* newNode = new link;
        newNode->value = new_value;
        while(travelerNode->next != NULL){
            travelerNode = travelerNode->next;
        }
        travelerNode->next = newNode;
        travelerNode = headNode;
    }
    
    void deleteNode(int target_value){
        while(travelerNode->next != NULL && travelerNode->next->value != target_value){
            travelerNode = travelerNode->next;
        }
        // target value was not found
        if(travelerNode->next == NULL){
            travelerNode = headNode;
            return;
        }
        // target value was found
        else{
            link* purger = travelerNode->next;
            travelerNode->next = travelerNode->next->next;
            free(purger);
            travelerNode = headNode;
        }
    }

    ~linkedList(){
        link* purger = NULL;
        link* walker = headNode->next;
        free(headNode);
        while(walker != NULL){
            purger = walker;
            walker = walker->next;
            free(purger);
        }
    }

};

// Delete the middle node with only access to the middle node
void deleteMiddleNode(link*& middleNode){
    link* walker = middleNode;
    link* next_copy = middleNode;
    walker = walker->next;
    // Walker is guaranteed to not be NULL because we start in the middle
    next_copy->value = walker->value;
    next_copy->next = walker->next;
    free(walker);
}

link* getMiddleNode(link*& start){
    int counter = 0;
    link* walker = start->next;
    while(walker != NULL){
        counter++;
        walker = walker->next;
    }
    walker = start->next;
    for(int i = 0; i < counter/2; ++i){
        walker = walker->next;
    }
    link* middleNode = walker;
    return middleNode;
}
            
// Non circular for the ease in the union program
void print_list(link*& start){
    link* walker = NULL;
    walker = start->next;
    while(walker != NULL){
        std::cout << walker->value  << " ";
        walker = walker->next;
    }
    std::cout << "\n";
}

int main() {
    int linkValues[] = {1, 2, 3, 4, 5};
    linkedList* myList = new linkedList;
    for(int i = 0; i < sizeof(linkValues)/sizeof(linkValues[0]); ++i){
        myList->addNode(linkValues[i]);
    }
    print_list(myList->headNode);
    link* middleNode = getMiddleNode(myList->headNode);
    deleteMiddleNode(middleNode);
    std::cout << "\n";
    print_list(myList->headNode);
    link* middleNode2 = getMiddleNode(myList->headNode);
    deleteMiddleNode(middleNode2);
    std::cout << "\n";
    print_list(myList->headNode);
    delete(myList);
    return 0;
}
