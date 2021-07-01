#include <vector>
#include <iostream>
#include <algorithm>
#include <unistd.h> // For debugging with print

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

void inOrderSearch(treeNode*& root){
    if(root != NULL){
        inOrderSearch(root->left_child);
        std::cout << root->value;
        inOrderSearch(root->right_child);
    }
}

void createDepthVector(std::vector< std::vector<int> >& nodeAtDepths, int depth, treeNode* root){
    // Base Case when the root value is NULL
    if(root == NULL){
        return;
    }

    // If there is a depth that does not have an indexable vector in place
    if(nodeAtDepths.size() <= depth){
        std::vector<int> newDepthVector;
        nodeAtDepths.push_back(newDepthVector);
    }

    nodeAtDepths[depth].push_back(root->value);
    
    // Calling the function on both children to add to their respective linkHeads
    createDepthVector(nodeAtDepths, depth+1, root->left_child);
    createDepthVector(nodeAtDepths, depth+1, root->right_child);
    return;
}

void printNodes(std::vector< std::vector<int> >& nodeAtDepths){
    std::cout << "Made it here\n";
    for(int i = 0; i < nodeAtDepths.size(); ++i){
        std::cout << "current depth: " << i << "\n";
        for(int j = 0; j < nodeAtDepths[i].size(); ++j){
            std::cout << nodeAtDepths[i][j] << " ";
        }
        std::cout << "\n";
    }
}
    

// Min index and Max index are for the curr_array indexing
void printPossibleSequences(std::vector< std::vector<int> >& nodeAtDepths, std::vector<int> curr_array, int depth, int min_index, int max_index){
    // Base Case that we have reached a permutation
    if(min_index == max_index && depth <= nodeAtDepths.size()){
        // Adding the current permutation to the curr_array
        for(int i = 0; i <= max_index; ++i){
            curr_array.push_back(nodeAtDepths[depth][i]);
        }
        
        // If we are at the last depth
        if(depth == nodeAtDepths.size() - 1){
            for(int i = 0; i < curr_array.size(); ++i){
                std::cout << curr_array[i] << " ";
            }
            std::cout << "\n";
            return;
        }

        // If we still need to permutate another depth
        return printPossibleSequences(nodeAtDepths, curr_array, depth+1, 0, nodeAtDepths[depth+1].size() - 1);
    }

    for(int i = min_index; i < nodeAtDepths[depth].size(); ++i){
        std::swap(nodeAtDepths[depth][min_index], nodeAtDepths[depth][i]);
        printPossibleSequences(nodeAtDepths, curr_array, depth, min_index+1, nodeAtDepths[depth].size() - 1);
        std::swap(nodeAtDepths[depth][min_index], nodeAtDepths[depth][i]);
    }
}

int main(){
    std::vector<int> myList = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    treeNode* myRoot = createTree(myList, -1, myList.size());
    std::vector< std::vector<int> > nodeAtDepths;
    createDepthVector(nodeAtDepths, 0, myRoot);
    printNodes(nodeAtDepths);
    std::vector<int> permutation_array;
    printPossibleSequences(nodeAtDepths, permutation_array, 0, 0, 0);
    return 0;
}
