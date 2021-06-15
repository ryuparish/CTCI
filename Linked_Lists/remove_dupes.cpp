#include <iostream>
#include <stdlib.h>

// NO HEAP LEAKAGE IN THIS IMPLEMENTATION!!!! YAYAYAYAYAYAY

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

    void addNode(link* node){
        while(travelerNode->next != NULL){
            travelerNode = travelerNode->next;
        }
        travelerNode->next = node;
        travelerNode = headNode;
    }
    
    void deleteNode(link*& node){
        while(travelerNode->next != node && travelerNode->next != NULL){
            travelerNode = travelerNode->next;
        }
        if(travelerNode->next = node){
            travelerNode->next = travelerNode->next->next;
            travelerNode = travelerNode->next;
            free(travelerNode);
            travelerNode = headNode;
        }
        // If not found, just return the traveler back to it's place
        travelerNode = headNode;
    }

    ~linkedList(){
        link* purger = NULL;
        travelerNode = travelerNode->next;
        free(headNode);
        while(travelerNode != NULL){
            purger = travelerNode;
            travelerNode = travelerNode->next;
            free(purger);
        }
        free(travelerNode);
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
    
int main() {
    int linkValues[5] = {1, 2, 3, 4, 5};
    linkedList* myList = new linkedList;
    // Adding all the links to the linked list 
    for(int i = 0; i < sizeof(linkValues)/sizeof(linkValues[0]); ++i){
        link* newNode = new link;
        newNode->value = linkValues[i];
        myList->addNode(newNode);
    }
    print_list(myList->headNode);
    delete(myList);
    return 0;
}
