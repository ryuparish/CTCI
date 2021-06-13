#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>

// O(n) Method: The plan is to store every zeros' row and column in a list of pairs whilst walking through the matrix and then cross them out in a separate function after we walk the matrix itself.


void print_matrix(std::vector< std::vector<int> >& matrix){
    // DEBUG (May need to change this to a vector)
    int m = matrix.size();
    int n = matrix[0].size();
    for(int i = 0; i < m; ++i){
        for(int j = 0; j < n; ++j){
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void walk_matrix(std::vector< std::vector<int> >& matrix, std::vector< std::pair<int, int> >& zero_locs){
    // DEBUG (May need to change this to a vector)
    int m = matrix.size();
    int n = matrix[0].size();
    for(int i = 0; i < m; ++i){
        for(int j = 0; j < n; ++j){
            if(matrix[i][j] == 0){
                std::pair<int, int> zero = std::make_pair (i,j);
                zero_locs.push_back(zero);
            }
        }
    }
}

void cross_zero(std::vector< std::vector<int> >& matrix, std::vector< std::pair<int, int> >& zero_locs){
    // m rows and n columns
    int m = matrix.size();
    int n = matrix[0].size();
    int target_row, target_column;

    for(int i = 0; i < zero_locs.size(); ++i){
        target_row = zero_locs[i].first;
        target_column = zero_locs[i].second;
        for(int j = 0; j < m; ++j){
            matrix[j][target_column] = 0;
        }
        for(int k = 0; k < n; ++k){
            matrix[target_row][k] = 0;
        }
    }
}
        
        
int main(){
    // Making a an np.arange(25).reshape((5,5))
    // Only four numbers should remain
    std::vector< std::vector<int> > matrix = {
        {0, 1, 2, 3, 4},
        {5, 6, 7, 8, 9},
        {10, 11, 0, 13, 14},
        {15, 16, 17, 18, 19},
        {20, 21, 22, 23, 0}
    };
    std::vector< std::pair<int, int> > zero_locs;

    print_matrix(matrix);
    walk_matrix(matrix, zero_locs);
    cross_zero(matrix, zero_locs);
    print_matrix(matrix);
    return 0;
}
