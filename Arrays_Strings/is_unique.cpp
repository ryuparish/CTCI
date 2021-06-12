// O(n) Method: Use a hash table and use the char as a key and store 1 or NULL.
// O(n^2) Method (no DS): Loop from the beginning of the list until the beginning of the list to check if it has appeared already.
// 2nd O(n) Method (no DS): Sort the list and store the current char in a char variable and check to see if the next one matches. <--- No DS, and best runtime

#include <algorithm>
#include <string>
#include <iostream>

int main(){
    std::string user_string;
    char char_cell;
    std::cin >> user_string;
    std::sort(user_string.begin(), user_string.end());
    char_cell = user_string[0];
    for(int i = 1; i < user_string.length(); ++i){
        if(user_string[i] == char_cell){
            std::cout << "There is a duplicate\n";
            break;
        }
        char_cell = user_string[i];
    }
    return 0;
}
