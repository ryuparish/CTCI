// O(n) time in the worst case (will stop early)
#include <iostream>
#include <string>

int possible_single_edit(std::string word1, std::string word2, int& i){
    // Insert or remove
    if(word1.length() < word2.length()){
        // Inserting potentially "completing letter" into word1
        std::string temp_word1 = word1;
        temp_word1.insert(i, word2[i], 1);
        if(temp_word1.compare(word2) == 0){
            return 0;
        }
        std::string temp_word2 = word2.erase(i, 1);
        if(temp_word2.compare(word1) == 0){
            return 0;
        }
    }
    
    else if(word2.length() < word1.length()){
        // Inserting potentially "completing letter" into word2
        std::string temp_word2 = word2;
        temp_word2.insert(i, word1[i], 1);
        if(temp_word2.compare(word1) == 0){
            return 0;
        }
        std::string temp_word1 = word1.erase(i, 1);
        if(temp_word1.compare(word2) == 0){
            return 0;
        }
    }

    // Same length, so try Replace
    std::string temp_word1 = word1;
    temp_word1[i] = word2[i];
    if(temp_word1.compare(word2) == 0){
        return 0;
    }
    std::string temp_word2 = word2;
    temp_word2[i] = word1[i];
    if(temp_word2.compare(word1) == 0){
        return 0;
    }
    // None of the three edits worked, fail
    return 1;
}

int main(){
    std::string word1, word2, shortest_word;
    std::cin >> word1 >> word2;

    // Edge case of the same words
    if(word1.compare(word2) == 0){
        std::cout << "No edits\n";
        return 0;
    }
    // Dealing with the last letter appendage edge case:
    // We want to check if all the letters up until the end of the shortest
    // word, then possibly appending just one letter if the rest match.
    if(word1.length() < word2.length()){
        shortest_word = word1;
    }
    else{
        shortest_word = word2;
    }

    // Checking if all the characters up until the last letter of the 
    // shortest word
    for(int i = 0; i < shortest_word.length(); ++i){
        if(word1[i] != word2[i]){
            int success = possible_single_edit(word1, word2, i);
            if(!success){
                std::cout << "Only one edit\n";
                return 0;
            }
            std::cout << "Takes more than one edit\n";
            return 1;
        }
    }
    // Covering the possible edge case that the we only needed one
    // append at the very end.
    std::string temp_word = shortest_word;
    if(word1.length() > shortest_word.length()){
        temp_word += word1.back();
        if(temp_word.compare(word1) == 0){
            std::cout << "Only one edit\n";
            return 0;
        }
        std::cout << "Takes more than one edit\n";
        return 1;
    }
    temp_word += word2.back();
    if(temp_word.compare(word2) == 0){
        std::cout << "Only one edit\n";
        return 0;
    }
    std::cout << "Takes more than one edit\n";
    return 1;
}

        
