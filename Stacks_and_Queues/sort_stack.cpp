#include <iostream>
#include <assert.h>
// Apprently the solution is to have a second stack that takes all the nodes popped when getting the last element from the primary stack. Then the secondary stack loads all the nodes back onto the
// primary stack without the last element from the original primary stack.

///// LINK DATA STRUCTURE RULES //////
// 1. Always use "new" when creating pointers that aren't immediately
// assigned to another pointer's object.

struct stackNode{
    int value;
    stackNode* next = NULL;
};

struct Stack{
    // In a stack the top node is always the newest node or null
    stackNode* top = NULL;

    void ordered_push(int nodeValue){
        stackNode* newNode = new stackNode;
        newNode->value = nodeValue;
        // First check to see if the top value doesn't exist yet
        if(top == NULL){
            top = newNode;
            return;
        }

        // First check if the top value is less than the node value, then we will have a new top value (the new node)
        if(top->value < nodeValue){
            newNode->next = top;
            top = newNode;
            return;
        }

        // Time to walk through the list
        stackNode* walker = top;

        // Walking through list until at the very end or until we find a smaller value 
        while(walker->next != NULL){
            // Looping through the value until we reach the end of the stack or if we find a smaller value 
            if(walker->next->value > nodeValue){
                walker = walker->next;
                continue;
            }
            // If the value found in the stack is smaller
            newNode->next = walker->next;
            walker->next = newNode;
            break;
        }
        // It either got to the end and is the smallest or found a spot the put the value
        // Got to the end of the list
        if(walker->next == NULL){
            walker->next = newNode;
        }
    }

    // Make this so that it returns the node that is to be deleted
    stackNode* pop(){
        if(top->next != NULL){
            stackNode* popped_node = new stackNode;
            popped_node->value = top->value;
            top = top->next;
            return popped_node;
        }
        return NULL;
    }

    // Just gets the value of the top node
    stackNode* peek(){
        if(top != NULL){
            return top->value;
        }
        return NULL;
    }

    bool isEmpty(){
        return top == NULL;
    }
    
    // Destructor
    ~Stack(){
        stackNode* purger = NULL;
        stackNode* walker = NULL;
        if(top->next != NULL){
            stackNode* walker = top->next;
        }
        free(top);
        while(walker != NULL){
            purger = walker;
            walker = walker->next;
            free(purger);
        }
    }
};


void print_stack(Stack*& myStack){
    stackNode* walker = myStack->top;
    // This conditional is meant for NOT printing the value 0 from the bottom stacknode 
    std::cout << "Here is the ordered stack: ";
    while(walker != NULL){
        std::cout << walker->value << " ";
        walker = walker->next;
    }
    std::cout << "\n";
}

// The only time we want to unload stack1 onto stack 2 is when stack 2 is empty
int main(){
    int a;
    std::cout << "Enter the numbers you want to push onto the stack\n";
    Stack* stack1 = new Stack;

    // Loading the stack with user's number
    while(std::cin >> a){
        stack1->ordered_push(a);
    }
    print_stack(stack1);
    return 0;
}
