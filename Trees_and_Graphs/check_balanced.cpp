#include <vector>
#include <iostream>
#include <unistd.h> // For debugging with print
#include <cstdlib>

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

int check_balanced(treeNode*& root, int counter){
    // Base Case if the node is NULL
    if(root == NULL){
        return counter;
    }

    // Adding one for every depth
    counter++;
    
    int left_count = check_balanced(root->left_child, counter);
    int right_count = check_balanced(root->right_child, counter);
    
    // If the difference between the two heights of the children nodes are offset by anything more than 1 they are unbalanced
    if(abs(left_count - right_count) > 1){
        std::cout << "Unbalanced trees with root: " << root->value << "\n";
    }
    
    // The height of the current node is the tallest possible height (child1's height, child2's height, or the root nodes original height is the heighest(true) height)
    int highest_child_height = (left_count > right_count) ? left_count : right_count;
    if(highest_child_height > counter){
        counter = highest_child_height;
    }

    return counter;
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
    treeNode* myRoot = createTree(myList.front()-1, myList.size());
    // Purposefully making an extra long branch in the tree
    treeNode* walker = myRoot;
    for(int i = 0; i < 2; ++i){
        walker = walker->left_child;
    }
    // Adding two extra nodes on the 0 node of the tree
    treeNode* extra1 = new treeNode;
    treeNode* extra2 = new treeNode;
    extra1->value = 10;
    extra2->value = 11;
    walker->left_child = extra1;
    walker = walker->left_child;
    walker->left_child = extra2;
    
    
    check_balanced(myRoot, 0);
    return 0;
}
