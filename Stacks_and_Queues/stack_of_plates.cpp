#include <iostream>
#include <vector>

struct stackNode{
    int min_value, value, index;
    stackNode* next = NULL;
};


struct Stack{
    stackNode* top = NULL;
    Stack* next = NULL;
    int threshold = 10;

    // Constructor
    Stack(){
        next = NULL;
    }
    
    void addNode(int nodeValue){
        stackNode* newNode = new stackNode;
        newNode->value = nodeValue;

        // If this is the first value to be added to the stack
        if(top == NULL){
            newNode->index = 1;
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
            newNode->index = top->index + 1;
            newNode->next = top;
            top = newNode;
        }
    }

    int deleteNode(){
        if(top != NULL && top->next != NULL){
            stackNode* purger = top;
            top = top->next;
            free(purger);
            return 0;
        }
        // This will delete the entire stack if you initiate a deleteNode on an empty stack
        else{return 1;}
    }
    
    int minval(){
        return top->min_value;
    }

    ~Stack(){
        stackNode* purger = NULL;
        stackNode* walker = NULL;
        if(top != NULL){
            stackNode* walker = top->next;
            free(top);
        }
        while(walker != NULL){
            purger = walker;
            walker = walker->next;
            free(purger);
        }
    }

};

struct setOfStacks{
    std::vector<Stack*> stacks;
    Stack* headStack = NULL;
    void addStack(Stack*& newStack){
        newStack->next = headStack;
        headStack = newStack;
        stacks.push_back(newStack);
    }
    void deleteStack(){
        if(headStack != NULL){
            stacks.pop_back();
            headStack = headStack->next;
        }
    }
    Stack* operator[](int index){
        return stacks[index];
    }
};

// For printing all the stacks
void print_stacks(setOfStacks*& stackSet){
    std::cout << "Here is the list of stacks\n";
    for(int i = 0; i < stackSet->stacks.size(); ++i){
        std::cout << "Stack number " << i+1 << ":\n";
        Stack* curr_stack = stackSet->stacks[i];
        stackNode* curr_node = curr_stack->top;

        // Looping through the current linked stack
        while(curr_node != NULL){
            std::cout << curr_node->value << " ";
            curr_node = curr_node->next;
        }
        std::cout << "\n";
    }
}
    
// For printing a single stack
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
    int value_cell, flip = 1;
    char a;

    // Adding the first stack to the set of stacks
    stackSet->addStack(myStack);

    while(flip){
        print_stacks(stackSet);
        std::cout << "Enter a to add a stack node\nEnter d to pop from the stack\nEnter m to see the minimum value\nEnter q to quit\n";
        std::cin >> a;
        while(a != 'q'){

            // If adding to a stack or adding another stack
            if(a == 'a'){
                std::cout << "What value would you like to add? ";
                std::cin >> value_cell;

                // Checking if the set of stacks is empty and adding one in the case that it is 
                if(stackSet->stacks.size() == 0){
                    Stack* newStack = new Stack;
                    stackSet->addStack(newStack);
                    myStack = newStack;
                }

                // If there are ten values in the stack
                if(myStack->top != NULL && myStack->top->index == myStack->threshold){
                    Stack* newStack = new Stack;
                    newStack->addNode(value_cell);
                    newStack->next = myStack;
                    myStack = newStack;
                    stackSet->addStack(newStack);
                }

                // If it can fit on the current stack
                else{myStack->addNode(value_cell);}
            }

            // If deleting 
            else if (a == 'd'){
                std::cout << "Which stack?";
                std::cin >> value_cell;
                stackCell = NULL;
                // Checking to make sure we don't get an index error
                if(stackSet->stacks.size() > 0){
                    stackCell = stackSet->stacks[value_cell-1];
                }

                // If there is nothing but the stack structure with no "plates"
                if(stackCell != NULL && stackCell->deleteNode()){
                    
                    // If the current stack is the stack to be deleted then the current stack needs to travel to the next stack
                    if(myStack == stackCell && myStack != NULL){
                        myStack = myStack->next;
                    }

                    // I think this is necessary to delete the dynamic stack pointer without it leaking?
                    free(stackCell);
                    stackSet->deleteStack();
                }
            }

            // If getting minimum value
            else if(a == 'm'){
                std::cout << myStack->minval() << "\n";    
            }
            
            // Error for non-valid characters
            else{std::cout << "Please enter a valid character (a,d,q)\n";}

            flip = !flip;
            a = 'q';
        }
        flip = !flip;
    }
    return 0;
}
