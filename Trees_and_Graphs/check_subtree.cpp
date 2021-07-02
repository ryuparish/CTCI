#include <vector>
#include <iostream>
#include <unistd.h> // For debugging with print
#include <string.h>

struct treeNode{
    int value;
    treeNode* left_child = NULL;
    treeNode* right_child = NULL;
};

treeNode* createTree(std::vector<int>& num_list, int start, int end){
    // Base Case if there are no spaces in between the end and the start to search
    if(end - start <= 1){
        return NULL;
    }
    
    int mid = (end - start)/2 + start;

    treeNode* child = new treeNode;
    child->value = num_list[mid];

    treeNode* left_child = createTree(num_list, start, mid);
    child->left_child = left_child;
    treeNode* right_child = createTree(num_list, mid, end);
    child->right_child = right_child;

    return child;
}

// Now doing a pre-order traversal to print out the corresponding string
std::string createString(treeNode*& root, std::string& treeCode){
    if(root != NULL){
        treeCode.append(std::to_string(root->value));
        createString(root->left_child, treeCode);
        createString(root->right_child, treeCode);
    }
    return " ";
}

// Search through the tree for the target node (I am going to assume this is a binary search tree)
std::string findNode(treeNode*& targetNode, treeNode*& root){
    while(root != NULL){
        if(root == targetNode){
            std::string treeCode;
            return createString(root, treeCode);
        }
        else if(root->value >= targetNode->value){
            root = root->left_child;
        }
        else{
            root = root->right_child;
        }
    }
    return " ";
}
    
int main(){
    // Creating the two tress
    std::vector<int> myList1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    std::vector<int> myList2 = {11, 12, 13, 14};
    treeNode* myRoot1 = createTree(myList1, -1, myList1.size());
    treeNode* myRoot2 = createTree(myList2, -1, myList2.size());

    // Making string codes for each of the possibly matching trees/subtree
    std::string treeCode; 
    std::string code1 = createString(myRoot2, treeCode);
    std::string code2 = findNode(myRoot2, myRoot1);

    // Comparing strings to see if there is a match
    if(code1.compare(code2) == 0){
        std::cout << "Tree 2 is a subtree of tree 1\n";
    }
    else{
        std::cout << "Tree 2  is not a subtree of tree 1\n";
    }
    return 0;
}
