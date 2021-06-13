#include <string>
#include <iostream>

int main(){
    std::string user_string, orig_string;
    char char_holder;
    int counter = 1, index = 1;
    std::cin >> user_string;
    orig_string = user_string;
    char_holder = user_string[0];
    while(index <= user_string.length()){
        if(char_holder != user_string[index]){
            char_holder = user_string[index];
            user_string.insert(index, std::to_string(counter));
            index += 2;
            counter = 1;
            continue;
        }
        user_string.erase(index, 1);
        counter++;
    }
    if(user_string.length() < orig_string.length()){
        std::cout << user_string << "\n";
        return 0;
    }
    std::cout << orig_string << "\n";
    return 1;
}
