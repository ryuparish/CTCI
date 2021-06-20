#include <iostream>

struct stackNode{
    int min_value, value;
    stackNode* next = NULL;
};

struct Stack{
    stackNode* top = new stackNode;
    // Constructor
    Stack(){
        top->value = 0;
        top->min_value = 0;
    }
    
    void addNode(int nodeValue){
        stackNode* newNode = new stackNode;
        newNode->value = nodeValue;
        // If this is the first value to be added to the stack
        if(top->next == NULL){
            newNode->min_value = nodeValue;
            newNode->next = top;
            top = newNode;
        }
        else{
            if(nodeValue < top->min_value){
                newNode->min_value = nodeValue;
            }
            else{newNode->min_value = top->min_value;}
            newNode->next = top;
            top = newNode;
        }
    }

    void deleteNode(){
        if(top->next != NULL){
            stackNode* purger = top;
            top = top->next;
            free(purger);
        }
    }
    
    int minval(){
        return top->min_value;
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

int main(){
    Stack* myStack = new Stack;
    int value_cell, flip = 1;
    char a;
    while(flip){
        print_stack(myStack);
        std::cout << "Enter a to add a stack node\nEnter d to pop from the stack\nEnter m to see the minimum value\nEnter q to quit\n";
        std::cin >> a;
        while(a != 'q'){
            if(a == 'a'){
                std::cout << "What value would you like to add? ";
                std::cin >> value_cell;
                myStack->addNode(value_cell);
            }

            else if (a == 'd'){
                myStack->deleteNode();
            }

            else if(a == 'm'){
                std::cout << myStack->minval() << "\n";    
            }
            
            else{std::cout << "Please enter a valid character (a,d,q)\n";}

            flip = !flip;
            a = 'q';
        }
        flip = !flip;
    }
    return 0;
}


