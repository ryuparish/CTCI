#include <string>
#include <iostream>

// O(n^2) runtime
void rotate_match(std::string& target_string, std::string puzzle_string){
    char char_holder;
    for(int i = 0; i < puzzle_string.length(); ++i){
        char_holder = puzzle_string.front();
        puzzle_string.erase(puzzle_string.begin());
        puzzle_string.append(1, char_holder);
        if(puzzle_string.compare(target_string) == 0){
            std::cout << "String 2 is a rotation of string 1\n";
            return;
        }
    }
    std::cout << "String 2 is NOT a rotation of string 1\n";
}
        

int main(){
    std::string target_string, puzzle_string;
    std::cin >> target_string >> puzzle_string;
    rotate_match(target_string, puzzle_string);
    return 0;
}


