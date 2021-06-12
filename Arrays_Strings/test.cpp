#include <iostream>
#include <map>

int main(){
    std::map<char, int> char_map;
    if(char_map['b'] == NULL){
        std::cout << "It returns null\n";
        return 0;
    }
    return 0;
}
