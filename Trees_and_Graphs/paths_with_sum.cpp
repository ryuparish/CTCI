#include <vector>
#include <iostream>
#include <unistd.h> // For debugging with print

struct treeNode{
    int value;
    bool visited = false;
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

void inOrderSearch(treeNode*& root){
    if(root != NULL){
        inOrderSearch(root->left_child);
        std::cout << root->value;
        inOrderSearch(root->right_child);
    }
}

int pathsWithSum(int sum, int target, treeNode*& curr_node, treeNode*& root){

    // Base Case were both children are null and the value itself
    // does not add to the sum to make the target
    if(curr_node->left_child == NULL && curr_node->right_child == NULL){
        if(sum + curr_node->value == target){
            return 1;
        }
        else{return 0;}
    }
    
    int total_matches = 0;

    sum += curr_node->value;
    // If the passed down sum plus the curr value is equivalent
    // to the target.
    if(sum == target){
        total_matches++;
    }

    // First recursing the sum passed down and then
    // recursing the node's value down to see if there is
    // a path starting from the node
    if(curr_node->left_child != NULL){
        total_matches += pathsWithSum(sum, target, curr_node->left_child, root);
        if(curr_node != root && curr_node->visited == false){
            total_matches += pathsWithSum(curr_node->value, target, curr_node->left_child, root);
        }
    }
    if(curr_node->right_child != NULL){
        total_matches += pathsWithSum(sum, target, curr_node->right_child, root);
        if(curr_node != root && curr_node->visited == false){
            total_matches += pathsWithSum(curr_node->value, target, curr_node->right_child, root);
        }
    }

    // Since both the current node has been used as a possible starting point and possibilities for this current node as a beginning has been explored
    curr_node->visited = true;

    return total_matches;
}

int main(){
    std::vector<int> myList = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    treeNode* myRoot = createTree(myList, myList.front()-1, myList.size());
    inOrderSearch(myRoot);
    std::cout << "\n";
    int numPaths = pathsWithSum(0, 15, myRoot, myRoot);
    std::cout << "Here are the total number of paths that add up to " << 15 << " : " << numPaths << "\n";
    return 0;
}
