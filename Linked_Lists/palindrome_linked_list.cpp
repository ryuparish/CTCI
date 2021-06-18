#include <iostream>
#include <stdlib.h>
#include <vector>

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

    void reverseAddNode(int new_value){
        link* newNode = new link;
        newNode->value = new_value;
        travelerNode = travelerNode->next;
        headNode->next = newNode;
        newNode->next = travelerNode;
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
        std::cout << walker->value  << " ";
        walker = walker->next;
    }
    std::cout << "\n";
}
    
// Make a copy of the linked list as another linked list then compare them 
int main() {
    // Users enters list of numbers
    int a;
    std::vector<int> linkValues;
    std::cout << "Please enter your numbers separated by spaces: ";
    while(std::cin >> a){
        linkValues.push_back(a);
    }
        
    linkedList* myList = new linkedList;
    linkedList* myListCopy = new linkedList;

    // Getting a forward and backward ordered linked list from the list of numbers
    for(int i = 0; i < linkValues.size(); ++i){
        myList->addNode(linkValues[i]);
        myListCopy->reverseAddNode(linkValues[i]);
    }

    std::cout << "Here is the list of numbers: \n";
    print_list(myList->headNode);

    link* traveler1 = myList->headNode;
    link* traveler2 = myListCopy->headNode;
    // Both links are always the same size so this single condition should suffice
    while(traveler1->next != NULL){
        if(traveler1->next->value == traveler2->next->value){
            traveler1 = traveler1->next;
            traveler2 = traveler2->next;
            continue;
        }
        std::cout << "Not a palindrome\n";
        delete(myList);
        delete(myListCopy);
        return 1;
    }
    std::cout << "This is a palidrome\n";
    delete(myList);
    delete(myListCopy);
    return 0;
}
