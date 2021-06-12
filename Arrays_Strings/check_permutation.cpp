// Naive O(n^2) Method: For every letter in the first string, check if there is the same letter in the second string and keep track if there is more than one in a hash table
// O(nlog(n)) Method: Sort both, then walk through each making sure each letter is the same
// O(n) Method: Walk through the first string with a hash table and for each letter found along with it's duplicates add 1 to the value. <--- best runtime 
// (the char itself is the key) Then iterate through the next string subtracting from each value instead. If the value found is 0 (there is an extra letter in the second string) or the key does not exist (there is a unique character in the second string) then they are not permutations of each other.
#include <string>
#include <iostream>
#include <map>

void check_permutation(std::string& word1, std::string& word2){
    // Check length
    if(word1.length() != word2.length()){
        std::cout << "Not permutations\n";
        return;
    }

    // Check letter count
    std::map<char, int> char_map;
    for(int i = 0; i < word1.length(); ++i){

        // character found 
        if(char_map[word1[i]]){
            ++char_map[word1[i]];
            continue;
        }

        // character not found
        char_map[word1[i]] = 1;
    }

    for(int i = 0; i < word2.length(); ++i){

        // If there is a mismatch of letter countj
        if(char_map[word2[i]] == 0){
            std::cout << "Not permutations\n";
            return;
        }

        --char_map[word2[i]];
    }
    std::cout << "Indeed permutations\n";

}

int main(){
    std::string word1, word2;
    std::cin >> word1 >> word2;
    check_permutation(word1, word2);
    return 0;
}
