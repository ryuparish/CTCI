#include <iostream>
#include <vector>
#include <map>

struct Node{
    int value;
    std::vector<Node*> children;
};

void print_nodes(std::map<int, Node*>& myGraph){
    Node* walker = NULL;
    for(auto i : myGraph){
        walker = i.second;
        if(walker == NULL){continue;}
        std::cout << walker->value << ": ";
        // Walking through all of the children of the current 
        for(int j = 0; j < walker->children.size(); ++j){
            std::cout << walker->children[j]->value << " ";
        }
        std::cout << "\n";
    }
}
            
int main(){
    // User making the graph
    int nodeValue;
    bool flip = true;
    char a;
    
    // Defining the Graph
    std::map<int, Node*> myGraph;

    while(flip){
        print_nodes(myGraph);
        std::cout << "Enter 'a' to add a node to the graph\nEnter 'e' to add nodes to an existing node\nEnter 'q' to quit\nEnter 'f' to find a path between two nodes\n";

        std::cin >> a;
        while(a != 'q'){
            if(a == 'a'){
                // Creating a new value and adding all the edges
                std::cout << "What value would you like to add?\n";
                std::cin >> nodeValue;
                Node* newNode = new Node;
                newNode->value = nodeValue;
                
                // Adding the value to the graph
                myGraph.insert({nodeValue, newNode});

                // Looping to add all the children of the new node
                while(nodeValue != -1){
                    std::cout << "Please enter all of the child values\nEnter -1 to stop\n";
                    std::cin >> nodeValue;
                    if(nodeValue != -1){
                        Node* child = new Node;
                        child->value = nodeValue;
                        newNode->children.push_back(child);
                    }
                }
                flip = !flip;
                a = 'q';
            }
            // Finding a connection between two points
            else if(a == 'f'){
                int points[2];
                std::cout << "Please enter the two values you would like to find a connection between: ";
                std::cin >> points[0] >> points[1];

                // Searching from point 1 to point 2 and from point 2 to point 1
                for(int i = 0; i < sizeof(points)/sizeof(points[0]); ++i){
                    if(myGraph[points[i]]){

                        Node* curr_child = myGraph[points[i]];

                        // In case a number was not in the graph
                        if(curr_child == NULL){
                            continue;
                        }

                        for(int j = 0; j < curr_child->children.size(); ++j){

                            // If the current child value is equal to the other point
                            if(curr_child->children[j]->value == points[(i+1) % 2]){
                                std::cout << "\nConnection found\n";
                                break;
                            }

                            // If it is the last value and connection was not found
                            else if(j+1 == curr_child->children.size()){
                                std::cout << "\nConnection not found\n";
                            }

                        }
                    }
                }
                flip = !flip;
                a = 'q';
            }
        }
        flip = !flip;
    }
    return 0;
}
