#include <vector>
#include <iostream>
#include <unistd.h> // For debugging with print
#include <stdlib.h> // For rand()
#include <algorithm> // For remove

struct treeNode{
    int value;
    treeNode* parent = NULL;
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
        // This cannot use the object walker because of the recursive contradictions
        treeNode* walker = someRoot;
        if(walker != NULL){
            inOrderSearch(walker->left_child);
            std::cout << walker->value;
            inOrderSearch(walker->right_child);
        }
    }

    // This frees/destroys node1 and replaces it with node2
    void transplant(treeNode*& root, treeNode*& node1, treeNode*& node2){
        if(node1->parent == NULL){
            root = node2;
        }
        else if(node1 == node1->parent->left_child){
            node1->parent->left_child = node2;
        }
        else{node1->parent->right_child == node2;}
        if(node2 != NULL){
            node2->parent = node1->parent;
        }
    }

    treeNode* randomNode(){
        int randomNodeValue = num_list[std::rand() % num_list.size()];
        return BinarySearch(this->root, randomNodeValue);
    }
        
    // Gets the left most child
    treeNode* smallestNode(treeNode*& root){
        this->walker = root;
        while(walker->left_child != NULL){
            walker = walker->left_child;
        }
        return walker;
    }
    
    void treeDelete(int targetValue){
        treeNode* target_node = BinarySearch(this->root, targetValue);
        if(target_node == NULL){
            std::cout << "Node to delete does not exist\n";
            return;
        }

        // Case in which one or both children are NULL from the target node to delete
        if(target_node->left_child == NULL){
            transplant(root, target_node, target_node->right_child);
        }
        else if(target_node->right_child == NULL){
            transplant(root, target_node, target_node->left_child);
        }
        // Both children are present
        // Case in which this can occur
        //              |
        //              |
        //
        //              * <-- To be deleted
        //             / \
        //            /   \
        //           *     *
        //                / \
        //               *   *
        //               ^
        //               ^ Node that needs to go in the empty spot due to ordering
        //
        //
        else{
            treeNode* smallest_left = smallestNode(target_node->right_child);
            if(smallest_left->parent != target_node){
                // Frees node that is the replacement(smallest_left)
                transplant(root, smallest_left, smallest_left->right_child);
                smallest_left->right_child = target_node->right_child;
                smallest_left->right_child->parent = smallest_left;
            }
            // Frees target node and loses it forever
            transplant(root, target_node, smallest_left);
            smallest_left->left_child = target_node->left_child;
            smallest_left->left_child->parent = smallest_left;
        }
        // We must assume there will be no duplicates in this case
        std::remove(this->num_list.begin(), this->num_list.end(), targetValue);
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
                treeNode* returnValue = walker;
                return returnValue;
            }
        }
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
    if(left_child != NULL){
        left_child->parent = child;
    }
    treeNode* right_child = createTree(num_list, mid, end);
    child->right_child = right_child;
    if(right_child != NULL){
        right_child->parent = child;
    }

    return child;
}

int main(){
    std::vector<int> myList = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    treeNode* myRoot = createTree(myList, myList.front()-1, myList.size());
    Tree* myTree = new Tree(myRoot, myList);
    myTree->inOrderSearch(myTree->root);
    std::cout << "\n";

    // Testing add
    std::cout << "Adding the value 10\n";
    myTree->insert(10);
    myTree->inOrderSearch(myTree->root);
    std::cout << "\n";

    // Testing delete
    std::cout << "Deleting the value 4\n";
    myTree->treeDelete(4);
    myTree->inOrderSearch(myTree->root);
    std::cout << "\n";

    // Testing Random Node
    treeNode* randomNode = myTree->randomNode();
    std::cout << "Here is the value of the random node: " << randomNode->value << "\n";
    return 0;
}
