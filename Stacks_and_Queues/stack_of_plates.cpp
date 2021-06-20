#include <iostream>
#include <vector>

struct stackNode{
    int min_value, value, index;
    stackNode* next = NULL;
};

struct setOfStacks{
    std::vector<Stack*> stacks;
    Stack* headStack = NULL;
    void addStack(Stack*& newStack){
        // If it is the first stack in the vector
        if(headStack == NULL){
            headStack = newStack;
        }
        newStack->next = headStack;
        headStack = newStack;
    }
    Stack* operator[int index]{
        return stacks[index];
    }
};

struct Stack{
    stackNode* top = new stackNode;
    Stack* next = NULL;
    int threshold = 10;
    // Constructor
    Stack(){
        top->value = 0;
        top->min_value = 0;
        top->index = 0;
        next = NULL;
    }
    
    void addNode(int nodeValue){
        stackNode* newNode = new stackNode;
        newNode->value = nodeValue;
        newNode->index = top->index + 1;
        // If this is the first value to be added to the stack
        if(top->next == NULL){
            newNode->min_value = nodeValue;
            newNode->next = top;
            top = newNode;
        }
        else{
            // If the node has the smallest value in the substack
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

    ~Stack(){
        stackNode* purger;
        stackNode* walker = top->next;
        while(walker != NULL){
            purger = walker;
            walker = walker->next;
            free(purger);
        }
    }

};

void print_stacks(setOfStacks*& stackSet){
    for(int i = 0; i < stackSet->stacks.size(); ++i){
        std::cout << "Stack number " << i+1 << ":\n";
        Stack* curr_stack = stackSet[i];
        stackNode* curr_node = curr_stack->top->next;
        while(curr_node != NULL){
            std::cout << curr_node->value << " ";
        }
        std::cout << "\n";
    }
}
    
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
    Stack* stackCell = NULL;
    setOfStacks* stackSet = new setOfStacks;
    stackSet->addStack(myStack);
    int value_cell, flip = 1;
    char a;
    while(flip){
        print_stacks(myStack);
        std::cout << "Enter a to add a stack node\nEnter d to pop from the stack\nEnter m to see the minimum value\nEnter q to quit\n";
        std::cin >> a;
        while(a != 'q'){
            if(a == 'a'){
                std::cout << "What value would you like to add? ";
                std::cin >> value_cell;
                if(myStack->top->index == myStack->threshold){
                    Stack* newStack = new Stack;
                    newStack->addNode(value_cell);
                    newStack->next = myStack;
                    myStack = newStack;
                }
                else{myStack->addNode(value_cell);}
            }

            // Need to fix this to index into a specific stack and pop from it
            else if (a == 'd'){
                std::cout << "Which stack?";
                std::cin >> value_cell;
                stackCell = stackSet[value_cell];
                stackCell->deleteNode();
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


