#include <vector>
#include <iostream>
struct Stack{
    std::vector<int> stack;
    int head_1, head_2, head_3, last_index;
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
        if(stack_num == 1){
            if(last_index < (head_1 + 3)){
                // Making space for all the stacks
                for(int i = 0; i < 3; ++i){
                    stack.push_back(0);
                }
                stack[head_1] = value;
                head_1 += 3;
            }
            else{
                stack[head_1] = value;
                head_1 += 3;
            }
        }
        else if (stack_num == 2){
            if(last_index < (head_2 + 3)){
                // Making space for all the stacks
                for(int i = 0; i < 3; ++i){
                    stack.push_back(0);
                }
                stack[head_2] = value;
                head_2 += 3;
            }
            else{
                stack[head_2] = value;
                head_2 += 3;
            }
        }
        else{
            if(last_index < (head_3 + 3)){
                // Making space for all the stacks
                for(int i = 0; i < 3; ++i){
                    stack.push_back(0);
                }
                stack[head_3] = value;
                head_3 += 3;
            }
            else{
                stack[head_3] = value;
                head_3 += 3;
            }
        }
    }
    void delete_value(int stack_num){
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
    std::cout << "Stack 1: ";
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
    std::cout << "\n";
    return 0;
}
