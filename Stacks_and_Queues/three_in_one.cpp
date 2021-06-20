#include <vector>
#include <iostream>
struct Stack{
    std::vector<int> stack;
    int head_1, head_2, head_3, last_index;
    int* curr_head = NULL;
    Stack(){

        stack.push_back(0);
        stack.push_back(0);
        stack.push_back(0);
        last_index = 2;
        head_1 = 0;
        head_2 = 1;
        head_3 = 2;
    }
    // Head 3 will be the furthest in front and adding 1 to it's value will
    // represent the total size of the vector.
    void add(int stack_num, int value){
        // If we had more stacks, we could use a hash table
        if(stack_num == 1){curr_head = &head_1;}
        if(stack_num == 2){curr_head = &head_2;}
        if(stack_num == 3){curr_head = &head_3;}

        if(last_index < (*curr_head + 3)){
            // Making space for all the stacks
            for(int i = 0; i < 3; ++i){
                stack.push_back(0);
            }
            stack[*curr_head] = value;
            *curr_head += 3;
        }
        else{
            stack[*curr_head] = value;
            *curr_head += 3;
        }
    }
    
    void delete_value(int stack_num){
        // We could possibly use a for loop and set a variable to true or false and use that variable in a single conditional statement instead of doing this
        if(stack_num == 1){
            if(head_2 < head_1 && head_3 < head_1){
                // Destroyting space for all the stacks
                for(int i = 0; i < 3; ++i){
                    stack.pop_back();
                }
                last_index -= 3;
                head_1 -= 3;
            }
            else{
                last_index-= 3;
                head_1 -= 3;
            }
        }
        else if (stack_num == 2){
            if(head_3 < head_2 && head_1 < head_2){
                // Destroying space for all the stacks
                for(int i = 0; i < 3; ++i){
                    stack.pop_back();
                }
                last_index -= 3;
                head_2 -= 3;
            }
            else{
                head_2 -= 3;
            }
        }
        else{
            if(head_1 < head_3 && head_2 < head_3){
                // Destroying space for all the stacks
                for(int i = 0; i < 3; ++i){
                    stack.pop_back();
                }
                last_index -= 3;
                head_3 += 3;
            }
            else{
                head_3 -= 3;
            }
        }
    }
};

void print_stack(Stack& myStack){
    std::cout << "\nStack 1: ";
    for(int i = 0; i < myStack.head_1; i += 3){
        std::cout << myStack.stack[i] << " ";
    }
    std::cout << "\nStack 2: ";
    for(int i = 1; i < myStack.head_2; i += 3){
        std::cout << myStack.stack[i] << " ";
    }
    std::cout << "\nStack 3: ";
    for(int i = 2; i < myStack.head_3; i += 3){
        std::cout << myStack.stack[i] << " ";
    }
}

int main(){
    Stack myStack;
    myStack.add(1,1);
    myStack.add(1,2);
    myStack.add(1,3);
    myStack.add(2,4);
    myStack.add(2,5);
    myStack.add(2,6);
    myStack.add(3,7);
    myStack.add(3,8);
    myStack.add(3,9);
    print_stack(myStack);
    std::cout << "\nRemoving one from the second stack";
    myStack.delete_value(2);
    print_stack(myStack);
    std::cout << "\nAdding the number 11 to the first stack";
    myStack.add(1, 11);
    print_stack(myStack);
    std::cout << "\n";
    return 0;
}
