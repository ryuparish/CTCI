#include <vector>
#include <iostream>
#include <unistd.h> // For debugging with print

struct treeNode{
    int value;
    treeNode* left_child = NULL;
    treeNode* right_child = NULL;
    treeNode* parent = NULL;
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

    // Setting the parent value of the child
    if(left_child != NULL){
        left_child->parent = child;
    }

    treeNode* right_child = createTree(num_list, mid, end);
    child->right_child = right_child;

    // Setting the parent value of the child
    if(right_child != NULL){
        right_child->parent = child;
    }

    return child;
}

void inOrderPrint(treeNode*& root){
    if(root != NULL){
        inOrderPrint(root->left_child);
        std::cout << root->value;
        inOrderPrint(root->right_child);
    }
}

treeNode* inOrderSearch(treeNode*& root, int target){
    if(root != NULL){
        // Base Case if the target is found
        if(root->value == target){
            return root;
        }
        treeNode* left_search = inOrderSearch(root->left_child, target);
        treeNode* right_search = inOrderSearch(root->right_child, target);
        if(left_search != NULL && left_search->value == target){
            return left_search;
        }
        else if(right_search != NULL && right_search->value == target){
            return right_search;
        }
        else{return NULL;}
    }
    else{return NULL;}
}

void findCommonAncestor(treeNode*& root, treeNode*& node1, treeNode*& node2){
    treeNode* walker1 = node1->parent;
    while(walker1 != NULL){
        treeNode* walker2 = node2->parent;
        while(walker2 != NULL){
            if(walker2 == walker1){
                std::cout << "Common ancestor found: " << walker1->value << " Between: " << node1->value << " and " << node2->value << "\n";
                return;
            }
            walker2 = walker2->parent;
        }
        walker1 = walker1->parent;
    }
    std::cout << "Common ancestor not found\n";
    return;
}

int main(){
    std::vector<int> myList = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    treeNode* myRoot = createTree(myList, -1, myList.size());
    inOrderPrint(myRoot);
    std::cout << "\n";
    
    treeNode* twoNode = inOrderSearch(myRoot, 5);
    treeNode* fiveNode = inOrderSearch(myRoot, 8);
    
    findCommonAncestor(myRoot, twoNode, fiveNode);
    return 0;
}
    

