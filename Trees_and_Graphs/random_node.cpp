#include <vector>
#include <iostream>
#include <unistd.h> // For debugging with print
struct treeNode{
    int value;
    treeNode* left_child = NULL;
    treeNode* right_child = NULL;
};

struct Tree{

    treeNode* root = NULL;
    treeNode* walker = NULL;
    std::vector<int> num_list;

    // Constructor
    Tree(treeNode*& newRoot, std::vector<int>& newNumList){
        root = newRoot;
        num_list = newNumList;
    }
    
    // In order print 
    void inOrderSearch(treeNode*& someRoot){
        walker = someRoot;
        if(walker != NULL){
            inOrderSearch(walker->left_child);
            std::cout << walker->value;
            inOrderSearch(walker->right_child);
        }
    }

    transplant(node*& root, node*& node1, node*& node2){
        if(node1->parent == NULL){
            root = node2;
        }
        else if(node1 == node1->parent->left){
            node1->parent->left = node2;
        }
        else{node1->parent->right == node2;}
        if(node2 != NULL){
            node2->parent = node1->parent;
        }
    }
    
    void treeDelete(node*& root, int targetValue){
        treeNode* target_node = BinarySearch(root, targetValue);
        if(target_node->left == NULL){
            transplant(root, target_node, target_node->right);
        }
        else if(target_node->right == NULL){
            transplant(root, target_node, target_node->left);
        }
        else{
            node* smallest_left = treeMinimum(target_node->right);
            if(smallest_left->parent != target_node){
                transplant(root, smallest_left, smallest_left->right);
                smallest_left->right = target_node->right;
                smallest_left->right->parent = smallest_left;
            }
            transplant(root, target_node, smallest_left);
            smallest_left->left = target_node->left;
            smallest_left->left->parent = smallest_left;
        }
    }

    treeNode* BinarySearch(treeNode*& someRoot, int targetValue){
        walker = someRoot;
        // Finding a spot to insert the node value into the tree
        while(walker != NULL){
            if(walker->value > targetValue){
                walker = walker->left_child;
            }
            else if(walker->value < targetValue){
                walker = walker->right_child;
            }
            else{
                std::cout << "Value is in the tree\n";
                treeNode* returnValue = walker;
                return returnValue;
            }
        }
        std::cout << "Value is not in the tree\n";
        return NULL;
    }

    void insert(int nodeValue){
        walker = root;
        treeNode* lagger = NULL;

        // Finding a spot to insert the node value into the tree
        while(walker != NULL){
            lagger = walker;
            if(walker->value > nodeValue){
                walker = walker->left_child;
            }
            else if(walker->value < nodeValue){
                walker = walker->right_child;
            }
            else{
                std::cout << "Value is already in the tree\n";
                break;
            }
        }

        // If the value was not found in the tree
        if(walker == NULL){
            treeNode* newNode = new treeNode;
            newNode->value = nodeValue;
            if(lagger->value < nodeValue){
                lagger->right_child = newNode;
            }
            else{
                lagger->left_child = newNode;
            }
        }
    }
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

int main(){
    std::vector<int> myList = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    treeNode* myRoot = createTree(myList, myList.front()-1, myList.size());
    Tree* myTree = new Tree(myRoot, myList);
    myTree->inOrderSearch(myTree->root);
    std::cout << "\n";

    return 0;
}
