#include <iostream>
#include <stdlib.h>
#include <vector>
#include <map>

// Implementing a queue using only a linked list
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
    void addNode(link*& newNode){
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
        std::cout << walker->value  << " ";
        walker = walker->next;
    }
    std::cout << "\n";
}
    
void intersect_checker(link*& start1, link*& start2){
    std::map<link*, int> link_table;
    link* traveler1 = start1->next;
    link* traveler2 = start2->next;
    while(traveler1 != NULL){
        link_table[traveler1] = 1;
        traveler1 = traveler1->next;
    }
    while(traveler2 != NULL){
        if(link_table[traveler2]){
            std::cout << "Intersection detected\n";
            break;
        }
        traveler2 = traveler2->next;
    }
}

int main() {
    std::vector<int> linkValues1 = {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int> linkValues2 = {9, 10, 11, 12, 13, 14, 15, 16};
    linkedList* List1 = new linkedList;
    linkedList* List2 = new linkedList;
    // Intersection link
    link* intersect_link = new link;
    intersect_link->value = 600;
    for(int i = 0; i < linkValues1.size(); ++i){
        if(i == 4){
            List1->addNode(intersect_link);
            ++i;
            continue;
        }
        link* newNode = new link;
        newNode->value = linkValues1[i];
        List1->addNode(newNode);
    }
    for(int i = 0; i < linkValues2.size(); ++i){
        if(i == 4){
            List2->addNode(intersect_link);
            ++i;
            continue;
        }
        link* newNode = new link;
        newNode->value = linkValues2[i];
        List2->addNode(newNode);
    }
    print_list(List1->headNode);
    print_list(List2->headNode);
    intersect_checker(List1->headNode, List2->headNode);
    // Leaving these to be commented out for now because there will be a double free error
    //delete(List1);
    //delete(List2);
    return 0;
}
