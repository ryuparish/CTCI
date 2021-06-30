#include <vector>
#include <iostream>
#include <unistd.h> // For debugging with print
#include <map>
#include <utility>

struct Node{
    char letter;
    Node* next = NULL;
};

// Creating a graph from the dependency map
std::map< char, Node*> createGraph(std::vector< std::pair< char, char >  >&graphMap){
    std::map< char, Node*> graphCorrected;
    for(auto pair : graphMap){

        // Walker is the first Node of the graphInfo provided
        char curr_dependent = pair.second;
        char curr_letter = pair.first;

        // Adding the new link created for the key of the current pair to the graphCorrected map if there is already a Node established in graphCorrected with this current letter
        if(graphCorrected[curr_dependent]){
            Node* innerWalker = graphCorrected[curr_dependent];
            
            // The innerWalker->next != will always deter because the initial conditional was passed
            while(innerWalker->next != NULL){
                innerWalker = innerWalker->next;
            }
            Node* newNode = new Node;
            newNode->letter = curr_letter;
            innerWalker->next = newNode;
        }
        // Adding the current letter dependency as the front link on the current dependent
        else{
            Node* newNode = new Node;
            newNode->letter = curr_letter;
            graphCorrected[curr_dependent] = newNode;
        }
    }
    return graphCorrected;
}

void printGraph(std::map< char, Node* >& myMap){
    for(auto pair : myMap){
        std::cout << "Here is the dependent: " << pair.first << "\n";
        std::cout << "Here are the dependencies: ";
        Node* walker = pair.second;
        while(walker != NULL){
            std::cout << walker->letter << " ";
            walker = walker->next;
        }
        std::cout << "\n";
    }
}

// Returns 0 if the map has been cleared of all nodes and 1 if not
int check_clear(std::map<char, Node*>& myMap){
    int flip = 0;
    for(auto pair : myMap){
        if(pair.second == NULL){
            std::cout << pair.first << " ";
            myMap.erase(pair.first);
            flip = 1;
        }
    }
    return flip;
}
            

void build_order(std::map<char, Node*>& myMap, std::vector<char>& projects){
    bool finished = false;
    while(!finished){
        // Search through every letter on the projects list and see if there are any that can be released.
        // Then search all the other projects to see if they contain that letter and delete the letter 
        // from that list.

        for(int i = 0; i < projects.size(); ++i){
            if(myMap[projects[i]] == NULL){
                finished = true;
                char targetLetter = projects[i];

                // Deleting the target character from every other letter's dependencies
                for(auto pair : myMap){
                    if(pair.first != targetLetter){
                        Node* walker = pair.second;

                        // The first conditional is just in case there is another letter with no dependencies
                        while(walker != NULL){
                            // If the next letter is equivalent to the target letter
                            if(walker->next != NULL && walker->next->letter == targetLetter){

                                // SHOULD FREE MEMORY HERE 
                                walker->next = walker->next->next;
                            }
                            // If the current letter is the target letter
                            else if(walker->letter == targetLetter){
                                // If the current letter is the target, but there is also a letter afterwards
                                if(walker->next != NULL){
                                    // SHOULD FREE MEMORY HERE
                                    myMap[pair.first] = walker->next;
                                }
                                else{
                                    myMap[pair.first] = NULL;
                                }
                            }
                                
                            walker = walker->next;
                        }
                    }
                }
                // Erasing the target letter from both the map and the projects list
                std::cout << targetLetter << " ";
                myMap.erase(targetLetter);
                projects.erase(projects.begin() + i);
            }
        }
        finished = !finished;
    }
}



int main(){
    // Reading in all the dependencies
    std::vector<char> projects = {'a', 'b', 'c', 'd', 'e', 'f'};

    // Making the Node/Char pairs into a single vector myPairs
    std::vector<char> dependencies = {'a', 'f', 'b', 'f', 'd'};
    std::vector<char> dependents = {'d', 'b', 'd', 'a', 'c'};
    std::vector< std::pair<char, char> >myPairs;
    for(int i = 0; i < dependents.size(); ++i){
        std::pair<char, char> newPair;
        newPair.first = dependencies[i];
        newPair.second = dependents[i];
        myPairs.push_back(newPair);
    }

    // Creating the graph
    std::map< char, Node* >myMap = createGraph(myPairs);

    // Getting any leftover projects that have no dependencies an adding them to the myMap map
    for(int i = 0; i < projects.size(); ++i){
        int j = 0;
        for(; j < dependents.size(); ++j){
            if(projects[i] == dependents[j]){
                break;
            }
        }
        if(j == dependents.size()){
            myMap[projects[i]] = NULL;
        }
    }
    printGraph(myMap);
    build_order(myMap, projects);
    std::cout << "\n";
    return 0;
}
