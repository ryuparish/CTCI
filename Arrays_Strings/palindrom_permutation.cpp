#include <string>
#include <iostream>
#include <map>

void palindrome_check(std::string& user_string){
    std::map<char, int> char_map;
    // There should be exactly 1 no_match in an odd-length string
    // and exactly 0 no_match in an even-length string
    int no_match = 0, space_debt = 0;

    for(int i = 0; i < user_string.length(); ++i){
        if(user_string[i] == ' '){
            ++space_debt;
            continue;
        }
        else if(char_map[user_string[i]]){
            --no_match;
            continue;
        }
        char_map[user_string[i]] = 1;
        ++no_match;
    }

    // We subtract the number of spaces because they are not included
    // in the calculation and we only want the "real length" of the 
    // string
    if((user_string.length() - space_debt) % 2 == 0 && no_match == 0){
        std::cout << "This is a permutation of a palindrome\n";
        return;
    }
    
    else if((user_string.length() - space_debt) % 2 == 1 && no_match == 1){
        std::cout << "This is a permutation of a palidrome\n";
        return;
    }

    std::cout << "This is not a permutation of a palindrome\n";
}

    

int main(){
    std::string user_string;
    std::getline (std::cin, user_string);
    palindrome_check(user_string);
    return 0;
}

