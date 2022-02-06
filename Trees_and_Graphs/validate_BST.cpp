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
// In order to see if there is an invalid node, we need to pass down a minimum and a maximum. Reset the minimum when you move right and check that the next node you will travel to will not violate either the minimum or the maximum. Reset the maximum when you move left and check the next node you will travel to for any violations.
// When traveling from the initial node however, you do not want to check for 
void inOrderValidate(treeNode*& root, int min, int max){
    if(root != NULL){

        // DEBUG
//        std::cout << "Current node: " << root->value << " left: ";
//        if(root->left_child != NULL){
//            std::cout << root->left_child->value << " ";
//        }
//        else{
//            std::cout << 0 << " ";
//        }
//        // Now for checking the right child
//        std::cout << "right: ";
//        if(root->right_child != NULL){
//            std::cout << root->right_child->value << " ";
//        }
//        else{
//            std::cout << 0 << " ";
//        }
//        std::cout << "min: " << min << " max: " << max << "\n";

        // Checking left side after root node
        if(min != 0 && root->left_child != NULL){
            if(root->left_child->value > root->value || root->left_child->value < min){
                std::cout << "Invalid node: " << root->left_child->value << "\n";
            }
        }

        // Checking left side from the root node
        else if(root->left_child != NULL){
            if(root->value < root->left_child->value){
                std::cout << "Invalid node: " << root->left_child->value << "\n";
            }
        }

        // Checking right side after root node
        if(max != 0 && root->right_child != NULL){
            if(root->right_child->value < root->value || root->right_child->value > max){
                std::cout << "Invalid node: " << root->right_child->value << "\n";
            }
        }
        // Checking left side from the root node
        else if(root->right_child != NULL){
            if(root->value > root->right_child->value){
                std::cout << "Invalid node: " << root->right_child->value << "\n";
            }
        }

        // Setting the new left and right values (they will not be evaluated if they are null)
        inOrderValidate(root->left_child, min, root->value);
        inOrderValidate(root->right_child, root->value, max);
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
    walker->left_child = errorNode;
    
    inOrderValidate(myRoot, 0, 0);
    return 0;
}
    

