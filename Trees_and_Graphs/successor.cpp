#include <vector>
#include <iostream>
#include <unistd.h> // For debugging with print

struct treeNode{
    int value;
    treeNode* parent = NULL;
    treeNode* left_child = NULL;
    treeNode* right_child = NULL;
};

treeNode* createTree(std::vector<int>& num_list, int start, int end){
    // Base Case if there are no spaces in between the end and the start to search
    if(end - start <= 1){
        return NULL;
    }

    int mid = (end - start)/2 + start;

    // Setting current node to the middle value
    treeNode* child = new treeNode;
    child->value = num_list[mid];

    // Making a left child node if possible
    treeNode* left_child = createTree(num_list, start, mid);
    if(left_child != NULL){
        left_child->parent = child;
    }
    child->left_child = left_child;

    // Making a right child node if possible 
    treeNode* right_child = createTree(num_list, mid, end);
    if(right_child != NULL){
        right_child->parent = child;
    }
    child->right_child = right_child;

    return child;
}

void inOrderSearch(treeNode*& root){
    if(root != NULL){
        inOrderSearch(root->left_child);
        std::cout << root->value;
        inOrderSearch(root->right_child);
    }
}

int findLeftMostNode(treeNode*& grandChild){
    while(grandChild->left_child != NULL){
        grandChild = grandChild->left_child;
    }
    // return the left most value after the right_child of the target value
    return grandChild->value;
}

int getSuccessor(treeNode*& root, int target_value){
    treeNode* walker = root;
    // This loop will walk through the tree until the target value is found and then will print the sucessor (if it exists)
    while(walker != NULL){
        if(walker->value > target_value){
            walker = walker->left_child;
        }
        else if(walker->value < target_value){
            walker = walker->right_child;
        }
        else{
            // The path in which the right child of the target node is not NULL, then the successor will be the leftmost node starting at the right_child
            if(walker->right_child != NULL){
                if(walker->right_child->left_child != NULL){
                    // Return the leftmost grand child after the right child of the target value
                    return findLeftMostNode(walker->right_child->left_child);
                }
                // return the right_child (it is the left-most value)
                return walker->right_child->value;
            }
            // The parent or grandparent node is the successor if the value of the parent node is equal or greater
            else if(walker->parent != NULL){
                while(walker->parent != NULL){
                    walker = walker->parent;
                    if(walker->value >= target_value){return walker->value;}
                }
            }
            // Target value was found but not successor was found (it is the last value of the in-order traversal
            return -1;
        }
    }
    return -1;
}

int main(){
    // Creating the tree
    std::vector<int> myList = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    treeNode* myRoot = createTree(myList, myList.front()-1, myList.size());
    inOrderSearch(myRoot);
    std::cout << "\n";
    
    // Searching for the successor of given value
    int successor_value = getSuccessor(myRoot, 6);
    if(successor_value != -1){
        std::cout << "Here is the successor of " << 6 << " : " << successor_value << "\n";
    }
    else{std::cout << "The target was not found or the target is the largest value\n";}
    return 0;
}
    

