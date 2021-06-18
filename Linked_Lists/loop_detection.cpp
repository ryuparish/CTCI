#include <iostream>
#include <map>
#include <vector>
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
    void addNode(link* newNode){
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
        travelerNode = headNode->next;
        free(headNode);
        while(travelerNode != NULL){
            purger = travelerNode;
            travelerNode = travelerNode->next;
            free(purger);
        }
    }

};
            
// Non circular for the ease in the union program
void print_list(link*& start){
    link* walker = NULL;
    walker = start->next;
    while(walker != NULL){
        std::cout << walker->value  << "\n";
        walker = walker->next;
    }
}

// Non circular for the ease in the union program
void check_loop(link*& start){
    std::map<link*, int> link_table;
    link* walker = NULL;
    walker = start->next;
    while(walker != NULL){
        std::cout << "Value of link_table[walker]: " << link_table[walker] << "\n";
        if(link_table[walker]){
            std::cout << "Loop detected\n";
            return;
        }
        link_table[walker] = 1;
        walker = walker->next;
    }
}
    
// In order to detect a loop, we would have to also trigger the detection in the addNode function, because it uses the while(traveler != NULL) functionality 
int main() {
    std::vector<int> linkValues = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    linkedList* myList = new linkedList;
    link* loopNode = NULL;
    for(int i = 0; i < linkValues.size(); ++i){
        std::cout << "Stuck in here\n";
        link* newNode = new link;
        if(i == 4){
            loopNode = newNode;
        }
        if(i == 6){
            myList->addNode(loopNode);
        }
        newNode->value = linkValues[i];
        myList->addNode(newNode);
    }
    std::cout << "Made it out of the main for loop\n";
    check_loop(myList->headNode);
    return 0;
}
