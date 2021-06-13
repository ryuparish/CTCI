#include <vector>
#include <iostream>
#include <algorithm>

// We may want to consider replacing the exact number for m and n for n-1 and m-1 for indexing purposes
void rotate_90_left(std::vector< std::vector<int> >& matrix){
    // Iterating down the respective columns
    // Following the conventional notation of a matrix being (mxn) [m rows][n columns]
    // We also subtract 1 so we can index without using any "off by one" notation
    int m = matrix.size() - 1;
    int n = matrix[0].size() - 1;

    // i travels diagonally toward the center of the matrix starting at the upper left corner
    for(int i = 0; i < m/2; ++i){
        // j travels down the columns of the matrix until the n - (i + 1)th spot
        for(int j = i; j < n - (i); ++j){
            // DEBUG
            // std::cout << "Value of i: " << i << " Value of j: " << j << "\n";
            
            std::swap(matrix[i][j], matrix[j][n - (i)]);
            std::swap(matrix[j][n - (i)], matrix[n - (i)][m - (j)]);
            std::swap(matrix[n - (i)][m - (j)], matrix[m - (j)][i]);

        }
    }
}

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

int main(){
    // Making a an np.arange(25).reshape((5,5))
    std::vector< std::vector<int> > matrix = {
        {0, 1, 2, 3, 4},
        {5, 6, 7, 8, 9},
        {10, 11, 12, 13, 14},
        {15, 16, 17, 18, 19},
        {20, 21, 22, 23, 24}
    };

    print_matrix(matrix);
    rotate_90_left(matrix);
    print_matrix(matrix);
    return 0;
}
