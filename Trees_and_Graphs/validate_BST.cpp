#include <vector>
#include <iostream>
#include <unistd.h> // For debugging with print

struct treeNode{
    int value;
    treeNode* left_child = NULL;
    treeNode* right_child = NULL;
};

treeNode* createTree(int start, int end){
    // Base Case if there are no spaces in between the end and the start to search
    if(end - start <= 1){
        return NULL;
    }
    
    int mid = (end - start)/2 + start;

    treeNode* child = new treeNode;
    child->value = mid;

    treeNode* left_child = createTree(start, mid);
    child->left_child = left_child;
    treeNode* right_child = createTree(mid, end);
    child->right_child = right_child;

    return child;
}

// We can send a threshold along while searching the left and right side of the tree's children
// In order to see if there is an invalid node, we need to pass down a minimum and a maximum. Reset the minimum when you move left and reset the maximum when you move right.
// The condition in which the node must be greater than the current max or less than the current max, etc, changes depending on which initial branch you are going down (left or right)
void inOrderValidate(treeNode*& root, int min, int max){
    if(root != NULL){

        // DEBUG
        std::cout << "Current node: " << root->value << " left: ";
        if(root->left_child != NULL){
            std::cout << root->left_child->value << " ";
        }
        else{
            std::cout << 0 << " ";
        }
        // Now for checking the right child
        std::cout << "right: ";
        if(root->right_child != NULL){
            std::cout << root->right_child->value << " ";
        }
        else{
            std::cout << 0 << " ";
        }
        std::cout << "min: " << min << " max: " << max << "\n";


        // Checking if current value is valid
        if(root->value > max || root->value < min){
            std::cout << "Invalid node: " << root->value << "\n";
        }

        // Setting the new left and right values (they will not be evaluated if they are null)
        int new_min = 0, new_max = 0;
        if(root->left_child != NULL){
            new_min = root->left_child->value;
        }
        if(root->right_child != NULL){
            new_max = root->right_child->value;
        }

        inOrderValidate(root->left_child, new_min, max);
        std::cout << root->value << "\n";
        inOrderValidate(root->right_child, min, new_max);
    }
}

int main(){
    std::vector<int> myList = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    treeNode* myRoot = createTree(myList.front()-1, myList.size());
    // Adding an erroneous node to the 5 node
    treeNode* walker = myRoot;
    walker = walker->right_child;
    walker = walker->left_child;
    treeNode* errorNode = new treeNode;
    errorNode->value = 12;
    walker->right_child = errorNode;
    
    inOrderValidate(myRoot, myRoot->value, myRoot->value);
    std::cout << "\n";
    return 0;
}
    

