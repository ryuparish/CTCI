#include <iostream>
#include <stdlib.h>

// Memory Management rules:
//  1. Remember to create destructor that uses two pointers.
//  2. Pointers do not always need to be allocated (new), especially if they are walkers.
//  3. Always free the head node after setting the walker ahead in the destructor
//  4. Default to using a NULL pointer rather than new. new will almost always be the cause of memory leakage.
//  5. Valgrind is not always accurate and one single missed allocation can be causing an assortment of leaks directly and indirectly at the same time.

// The fundamental functionlity of quicksort is the at the very beginning of the partition, the part_index and the iterating index will be traveling at the same pace until value iterated on is larger
// than the part_value. This will ensure that any less-than-part_value link will be swapped with a
// value that is always greater than or equal to the part_value.

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
            
void print_list(link*& start){
    link* walker = NULL;
    walker = start->next;
    while(walker != NULL){
        std::cout << walker->value  << " ";
        walker = walker->next;
    }
    std::cout << "\n";
}

void partition(link*& start, int& part_value){
    int value_swapspace;
    link* part_link = start->next;
    link* walker = start->next;
    while(walker != NULL){
        if(walker->value < part_value){
            value_swapspace = part_link->value;
            part_link->value = walker->value;
            walker->value = value_swapspace;
            part_link = part_link->next;
        }
        walker = walker->next;
    }
}
    
int main() {
    int linkValues[] = {3, 5, 8, 5, 10, 2, 1};
    int part_value;
    linkedList* myList = new linkedList;
    for(int i = 0; i < sizeof(linkValues)/sizeof(linkValues[0]); ++i){
        myList->addNode(linkValues[i]);
    }
    print_list(myList->headNode);
    std::cout << "What value do you want to partition around? ";
    std::cin >> part_value;
    partition(myList->headNode, part_value);
    print_list(myList->headNode);
    delete(myList);
    return 0;
}
