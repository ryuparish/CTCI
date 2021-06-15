#include <iostream>
#include <stdlib.h>

// Implementing a queue using only a linked list
// Used some heap allocation, but there is definitely memory leakage.

// Pointers are like little wizards that use their wand to manipulate objects



struct link{
    int value = NULL;
    link* next = NULL;
};

struct linkedList{
    // Using a traveler node will give up the reduced time complexity for
    // the cost of having easy access to any node in the middle and not having a tail pointer allocated
    link* headNode = new link;
    link* travelerNode = new link;
    travelerNode = headNode;

    // Constructor to set the head of the linked list object
    linkedList(link* node){
        headNode = node;
    }

    addNode(link*& node){
        while(travelerNode->next != NULL){
            travelerNode = travelerNode->next;
        }
        travelerNode->next = node;
        travelerNode = headNode;
    }
    
    deleteNode(link*& node){
        while(travelerNode->next != node && travelerNode->next != NULL){
            travelerNode = travelerNode->next;
        }
        if(travelerNode->next =- node){
            travelerNode->next = traveler->next->next;
            travelerNode = travelerNode->next;
            free(travelerNode);
            travelerNode = headNode;
        }
        // If not found, just return the traveler back to it's place
        travelerNode = headNode;
    }
}
            
// Non circular for the ease in the union program
void print_list(link*& start){
    link* walker = new link;
    walker = start;
    while(walker != NULL){
        std::cout << walker->value  << "\n";
        walker = walker->next;
    }
    free(walker);
}
    
int main() {
    int linkValues[5] = {1, 2, 3, 4, 5};
    linkedList* myList = new linkedList;
    for(int i = 0; i < sizeof(linkValues)/sizeof(linkValues[0]); ++i){
        link* newNode = new link;
        newNode->value = linkValues[i];
        myList->addNode(newNode);
    }
    print_list(myList->headNode);
    return 0;
}
