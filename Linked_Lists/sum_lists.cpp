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

linkedList* sum_lists(link*& num1_head, link*& num2_head){
    linkedList* sum_list = new linkedList;
    // Walkers for both numbers 
    link* walker1 = num1_head->next;
    link* walker2 = num2_head->next;
    // We will need these two integers after this initial for loop
    int carry_over = 0, sum;
    while(walker1 != NULL && walker2 != NULL){
        sum = walker1->value + walker2->value + carry_over;

        // Placing the zeroing of the carry over here to make sure
        // it gets cleared right after addition and saved for the next
        // digit place.
        carry_over = 0;

        if(sum > 9){
            carry_over = (int)(sum / 10);
            sum = sum % 10;
        }
        sum_list->addNode(sum);

        // Placing the zeroing of the sum here for the conditionals after
        // this while loop.
        sum = 0;

        walker1 = walker1->next;
        walker2 = walker2->next;
    }
    while(walker2 != NULL){
        sum = walker2->value + carry_over;
        carry_over = 0;
        if(sum > 9){
            carry_over = (int)(sum  / 10);
            sum = sum % 10;
        }
        sum_list->addNode(sum);
        walker2 = walker2->next;
    }
    while(walker1 != NULL){
        sum = walker1->value + carry_over;
        carry_over = 0;
        if(sum > 9){
            carry_over = (int)(sum  / 10);
            sum = sum % 10;
        }
        sum_list->addNode(sum);
        walker1 = walker1->next;
    }
    // If there is carry over only remaining
    if(carry_over){
        sum_list->addNode(carry_over);
        carry_over = 0;
    }
    return sum_list;
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
    // We can make a function that reads these two numbers in.
    std::vector<int> num1 = {7, 1, 6};
    std::vector<int> num2 = {5, 9, 2};
    std::vector<int> linkValues;

    // List of entered numbers for loading into linked lists
    std::vector< std::vector<int> > num_list = {
        num1,
        num2
    };

    // Linked lists to put the numbers above into 
    std::vector< linkedList* > linkedLists;

    // Making a separate linked list for every vector representation of
    // the two numbers.
    for(int i = 0; i < num_list.size(); ++i){
        linkValues = num_list[i];
        linkedList* current_list = new linkedList;
        for(int j = 0; j < linkValues.size(); ++j){
            current_list->addNode(linkValues[j]);
        }
        linkedLists.push_back(current_list);
    }
    linkedList* linked_sum = sum_lists(linkedLists[0]->headNode, linkedLists[1]->headNode);
    print_list(linked_sum->headNode);

    // For printing out and deleting the linked lists allocated memory
    for (int j = 0; j < linkedLists.size(); ++j){
        delete(linkedLists[j]);
    }
    delete(linked_sum);
    return 0;
}
