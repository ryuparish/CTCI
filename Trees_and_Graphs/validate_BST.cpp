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
void inOrderValidate(treeNode*& root){
    if(root != NULL){
        // Checking the left value (if larger)
        if(root->left_child != NULL && root->left_child->value > root->value){
            std::cout << "Invalid node at root: " << root->value;
        }
        inOrderValidate(root->left_child);
        std::cout << root->value;
        inOrderValidate(root->right_child);
        // Checking the right value (if smaller)
        if(root->right_child != NULL && root->right_child->value < root->value){
            std::cout << "Invalid node at root: " << root->value;
        }
    }
}

int main(){
    std::vector<int> myList = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    treeNode* myRoot = createTree(myList.front()-1, myList.size() + 1);
    inOrderValidate(myRoot);
    std::cout << "\n";
    return 0;
}
    

