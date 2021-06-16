#include <iostream>
#include <stdlib.h>

// NO HEAP LEAKAGE IN THIS IMPLEMENTATION!!!! YAYAYAYAYAYAY
// Raw Pointers are like little wizards that use their wand to manipulate objects

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

    // Adding and removing of nodes is based on values because it would be weird to have access to the node itself
    // only to pass it to a method to change it's validity

    void addNode(int nodeValue){
        link* newNode = new link;
        newNode->value = nodeValue;
        while(travelerNode->next != NULL){
            travelerNode = travelerNode->next;
        }
        travelerNode->next = newNode;
        travelerNode = headNode;
    }
    
    void deleteNode(int nodeValue){
        while(travelerNode->next != NULL && travelerNode->next->value != nodeValue){
            travelerNode = travelerNode->next;
        }
        // Reached end of list without finding the target node value
        if(travelerNode->next == NULL){
            return;
        }
        // Found the node with the target value
        else{
            link* purger = travelerNode->next;
            travelerNode->next = travelerNode->next->next;
            free(purger);
            travelerNode = headNode;
        }
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

            
// Non circular for the ease in the union program void print_list(link*& start){ // You do not need to allocate a link object for the walker. That will only lead to lost data.
void print_list(link*& start){
    link* walker = NULL;
    walker = start->next;
    while(walker != NULL){
        std::cout << walker->value  << " ";
        walker = walker->next;
    }
    std::cout << "\n";
}

// Remove duplicates by using no extra data structures
// O(n^2) runtime
void removeDupes(link*& start){
    link* walker = start->next;
    link* brother_walker = NULL;
    while(walker != NULL){
        brother_walker = walker;
        while(brother_walker != NULL){
            if(brother_walker->next != NULL && brother_walker->next->value == walker->value){
                link* purger = brother_walker->next;
                brother_walker->next = brother_walker->next->next;
                free(purger);
            }
            else{
                brother_walker = brother_walker->next;
            }
        }
        walker = walker->next;
    }
}


                
    
int main() {
    int linkValues[] = {1, 2, 3, 3, 3, 4, 2, 2, 1, 5, 4, 5, 4, 5, 3, 1, 3, 4, 5};
    linkedList* myList = new linkedList;
    // Adding all the links to the linked list 
    for(int i = 0; i < sizeof(linkValues)/sizeof(linkValues[0]); ++i){
        myList->addNode(linkValues[i]);
    }
    print_list(myList->headNode);
    removeDupes(myList->headNode);
    std::cout << "\n";
    print_list(myList->headNode);
    delete(myList);
    return 0;
}
