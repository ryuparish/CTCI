#include <vector>
#include <iostream>
#include <unistd.h> // For debugging with print
#include <map>

struct Link{
    char letter;
    Link* next = NULL;
};

std::map< char, Link*> createGraph(std::map< char, Link* >&graphMap){
    std::map< char, Link*> graphCorrected;
    for(auto pair : graphMap){

        // Walker is the first Link of the graphInfo provided
        // It is guaranteed that there will be no chars  without dependencies in the graphMap provided
        // so we get the Value(Link) of every key(char) in the map
        Link* walker = pair.second;
        char curr_letter = pair.first;
        std::cout << "Current letter that is a dependency: " << curr_letter << "\n"; 

        // Adding the new link created for the key of the current pair to the graphCorrected map if there is already a Link at the spot
        if(graphCorrected[walker->letter]){
            Link* innerWalker = graphCorrected[walker->letter];
            // The innetWalker->next != will always deter first because the initial conditional was passed
            while(innerWalker != NULL && innerWalker->next != NULL){
                innerWalker = innerWalker->next;
            }
            innerWalker->next = newNode;
        }
        else{
            Link* newNode = new Link;
            newNode->letter = pair.first;
            graphCorrected[walker->letter] = newNode;
        }

        // Walking through all the letters that depend on the current dependency
        while(walker != NULL){
            // If the letter in the current linked list already has links in it's adjecency list
            Link* newNode = new Link;
            newNode->letter = curr_letter;
            if(graphCorrected[walker->letter]){
                // This might mess up the graphCorrected by pointing the first link inside the graphCorrected to the current dependency instead of making the current dependency the
                // new first link. (It might be a good idea to create a headNode, although that may make the code more complicated)
                newNode->next = graphCorrected[walker->letter];
            }
            graphCorrected[walker->letter] = newNode;
        }
}

void inOrderSearch(treeNode*& root){
    if(root != NULL){
        inOrderSearch(root->left_child);
        std::cout << root->value;
        inOrderSearch(root->right_child);
    }
}

int main(){
    std::vector<int> myList = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    treeNode* myRoot = createTree(myList, myList.front()-1, myList.size());
    inOrderSearch(myRoot);
    std::cout << "\n";
    return 0;
}
    

