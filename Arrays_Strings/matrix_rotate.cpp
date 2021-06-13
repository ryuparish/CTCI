#include <vector>
#include <iostream>
#include <algorithm>

// We may want to consider replacing the exact number for m and n for n-1 and m-1 for indexing purposes
void rotate_90_left(int matrix[][5]){
    // Iterating down the respective columns
    // Following the conventional notation of a matrix being (mxn) [m rows][n columns]
    //
    // DEBUG (May need to change this to a vector)
    //int m = sizeof(matrix)/sizeof(matrix[0]);
    //int n = sizeof(matrix[0])/sizeof(matrix[0][0]);
    int m = 5;
    int n = 5;

    // i travels diagonally toward the center of the matrix starting at the upper left corner
    for(int i = 0; i < m/2; ++i){
        // j travels down the columns of the matrix until the n - (i + 1)th spot
        for(int j = i; j < n - (i + 1); ++j){
            // DEBUG
            // std::cout << "Value of i: " << i << " Value of j: " << j << "\n";
            
            std::swap(matrix[i][j], matrix[j][n - (i + 1)]);
            std::swap(matrix[j][n - (i + 1)], matrix[n - (i + 1)][m - (j + 1)]);
            std::swap(matrix[n - (i + 1)][m - (j + 1)], matrix[m - (j + 1)][i]);

        }
    }
}

void print_matrix(int matrix[][5]){
    // DEBUG (May need to change this to a vector)
    //int m = sizeof(matrix)/sizeof(matrix[0]);
    //int n = sizeof(matrix[0])/sizeof(matrix[0][0]);
    int m = 5;
    int n = 5;
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
    int matrix[5][5] = {
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
