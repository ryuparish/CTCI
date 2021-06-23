#include <iostream>
#include <assert.h>
// Apprently the solution is to have a second stack that takes all the nodes popped when getting the last element from the primary stack. Then the secondary stack loads all the nodes back onto the
// primary stack without the last element from the original primary stack.

///// LINK DATA STRUCTURE RULES //////
// 1. Always use "new" when creating pointers that aren't immediately
// assigned to another pointer's object.

struct Node{
    int value;
    Node* next = NULL;
    // 1 if dog, 0 if cat
    int pet_value;
};

struct Queue{
    // As in first to go and last to be added
    Node* first = NULL;
    Node* last = NULL;

    void push(int nodeValue, int pet_value){
        Node* newNode = new Node;
        newNode->value = nodeValue;
        newNode->pet_value = pet_value;
        // If the last node exists and should be linked
        if (last != NULL){
            last->next = newNode;
        }
        last = newNode;
        if(first == NULL){
            first = last;
        }
    }

    int pop(){
        if(first == NULL){
            return 0;
        }
        int popped_node = first->value;
        first = first->next;
        // last will also be set to NULL because first should tend toward the last position, and first being NULL means last is also being popped
        if(first == NULL){
            last = NULL;
        }
        return popped_node;
    }

    int pop_pet(int preference){
        // In case there are no animals in the list
        if(first == NULL){
            return 0;
        }

        // In case the preference is not valid
        if(preference < 0 || preference >= 3){
            return pop();
        }

        // Finding the preferred pet if possible 
        Node* walker = first;
        int tagger = 0;
        while(walker->next != NULL){
            // If dog was found in list
            if(walker->next->pet_value == preference){
                tagger = walker->next->value;
                walker->next = walker->next->next;
                return tagger;
            }
            walker = walker->next;
        }
        return pop();
    }

    int peek(){
        if(first != NULL){
            return first->value;
        }
        return 0;
    }

    bool isEmpty(){
        return first == NULL;
    }
};

void print_queue(Queue*& myQueue){
    Node* walker = myQueue->first;
    // This conditional is meant for NOT printing the value 0 from the bottom stacknode 
    std::cout << "Here is the current queue: ";
    while(walker != NULL){
        std::cout << walker->value << " ";
        walker = walker->next;
    }
    std::cout << "\n";
}

// The only time we want to unload stack1 onto stack 2 is when stack 2 is empty
int main(){
    int a, randomizer;
    std::cout << "Enter the numbers you want to push onto the queue\n";
    Queue* myQueue = new Queue;

    // Loading the stack with user's number
    while(std::cin >> a){
        randomizer = a;
        randomizer = randomizer % 3;
        if(randomizer == 0){
            randomizer++;
        }
        myQueue->push(a, randomizer);
    }

    // loading onto stack1_reverse
    print_queue(myQueue);

    // Now popping from the oldest value
    std::cout << "Adding 6 to the queue as a dog\n";
    myQueue->push(6,1);
    print_queue(myQueue);

    // Now popping all from the reverse queue and checking the values of both the stacks
    std::cout << "Popping everything alternatingly from the queue\n";
    int walker = -1;
    int counter = 1;
    while(walker->next != 0){
        walker = myQueue->pop_pet(counter);
        std::cout << "Popped: " << walker << "\n";
        // Getting pets in alternating order
        counter++;
        counter = counter % 3;
        if(counter == 0){
            counter++;
        }
    }
    print_queue(myQueue);
    return 0;
}
