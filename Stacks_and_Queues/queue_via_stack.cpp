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
    stackNode* top = new stackNode;

    void push(int nodeValue){
        stackNode* newNode = new stackNode;
        newNode->value = nodeValue;
        newNode->next = top;
        top = newNode;
        
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
        return top;
    }

    bool isEmpty(){
        return top->next == NULL;
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

struct myQueue{
    Stack* stack1 = NULL;
    Stack* stack1_reverse = NULL;

    // Constructor
    myQueue(Stack*& orderedStack, Stack*& reversedStack){
        stack1 = orderedStack;
        stack1_reverse = reversedStack;
    }

    // Unloads the stack when the reverse stack is empty
    void unloadStack1(){
        stackNode* nodeHolder;
        int intHolder;
        while(!stack1->isEmpty()){
            nodeHolder = stack1->pop();
            intHolder = nodeHolder->value;
            free(nodeHolder);
            stack1_reverse->push(intHolder);
        }
    }

    void push(int nodeValue){
        stack1->push(nodeValue);
    }

    stackNode* pop(){
        stackNode* poppedNode = stack1_reverse->pop();
        if(stack1_reverse->isEmpty()){
            unloadStack1();
        }
        return poppedNode;
    }
};

void print_stack(Stack*& myStack){
    stackNode* walker = myStack->top;
    // This conditional is meant for NOT printing the value 0 from the bottom stacknode 
    std::cout << "Here is the current stack: ";
    while(walker->value != 0){
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
    Stack* stack2 = new Stack;
    myQueue* theQueue = new myQueue(stack1, stack2);

    // Loading the stack with user's number
    while(std::cin >> a){
        theQueue->push(a);
    }
    // loading onto stack1_reverse
    theQueue->unloadStack1();
    print_stack(theQueue->stack1_reverse);
    print_stack(theQueue->stack1);
    
    // Now popping from the oldest value
    stackNode* popped_node = theQueue->pop();
    std::cout << "Here is the oldest value: " << popped_node->value << "\n";
    print_stack(theQueue->stack1_reverse);
    print_stack(theQueue->stack1);
    std::cout << "Adding 6 to the queue\n";
    theQueue->push(6);
    print_stack(theQueue->stack1_reverse);
    print_stack(theQueue->stack1);

    // Now popping all from the reverse queue and checking the values of both the stacks
    std::cout << "Popping everything from the reverse stack\n";
    stackNode* walker = theQueue->pop();
    while(walker != NULL){
        std::cout << "Popped: " << walker->value << "\n";
        walker = theQueue->pop();
    }
    print_stack(theQueue->stack1_reverse);
    print_stack(theQueue->stack1);

    return 0;
}
