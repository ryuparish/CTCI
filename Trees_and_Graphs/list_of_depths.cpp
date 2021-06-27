#include <vector>
#include <iostream>
#include <unistd.h> // For debugging with print

struct treeNode{
    int value;
    treeNode* left_child = NULL;
    treeNode* right_child = NULL;
};

struct Link{
    int value;
    Link* next = NULL;
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

void createLinkVector(std::vector<Link*>& linkList, int depth, treeNode* root){
    // Base Case when the root value is NULL
    if(root == NULL){
        return;
    }

    // -1 because of the indexing rather than the actual number of values 
    if(linkList.size() <= depth){
        Link* newHead = NULL;
        linkList.push_back(newHead);
    }
    
    // Walking through the current linked list to add on the current value
    Link* walker = linkList[depth];

    while(walker != NULL && walker->next != NULL){
        walker = walker->next;
    }

    // Adding the current depth value to the respective link head
    Link* newNode = new Link;
    newNode->value = root->value;

    // Setting the pointer to the new node if newHead is the only pointer in the list
    if(walker == NULL){
        linkList[depth] = newNode;
    }
    else{walker->next = newNode;}

    // Calling the function on both children to add to their respective linkHeads
    createLinkVector(linkList, depth+1, root->left_child);
    createLinkVector(linkList, depth+1, root->right_child);
    return;
}

void printLinkedLists(std::vector<Link*>& linkList){
    Link* walker = NULL;
    for(int i = 0; i < linkList.size(); ++i){
        walker = linkList[i];
        std::cout << "current depth: " << i << "\n";
        while(walker != NULL){
            std::cout << walker->value << " ";
            walker = walker->next;
        }
        std::cout << "\n";
    }
}
    
int main(){
    std::vector<int> myList = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    treeNode* myRoot = createTree(myList, -1, myList.size());
    std::vector<Link*> linkList = {};
    createLinkVector(linkList, 0, myRoot);
    printLinkedLists(linkList);
    return 0;
}
