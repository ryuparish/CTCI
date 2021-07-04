#include <vector>
#include <iostream>

// Apparently this way is not efficient enough for LeetCode. Switching to leet code now!
int findNumPaths(std::vector< std::vector<int> >& routes, int& target_steps, int curr_step){
    // Base Case when we have made it to the stairs
    if(curr_step == target_steps){
        return 1;
    }
    // Will have to put base cases for overstepping here so we don't segfault below
    else if(curr_step > target_steps){
        return 0;
    }

    // Getting all possible paths for the current step we are on
    // For taking one step
    int return_value = 0, total_solutions = 0;
    if(routes[curr_step][0]){
        return_value = findNumPaths(routes, target_steps, curr_step+1);
        // Keep the table the same if solution
        if(return_value){
            total_solutions += return_value;
        }
        // Prune off the table spot if this step is not a possible solution
        else{
            routes[curr_step][0] = 0;
        }
    }
    // For taking two steps
    if(routes[curr_step][1]){
        return_value = findNumPaths(routes, target_steps, curr_step+2);
        if(return_value){
            total_solutions += return_value;
        }
        // Prune off the table spot if this step is not a possible solution
        else{
            routes[curr_step][1] = 0;
        }
    }
    // For taking three steps
    if(routes[curr_step][2]){
        return_value = findNumPaths(routes, target_steps, curr_step+3);
        // Keep the table the same if solution
        if(return_value){
            total_solutions += return_value;
        }
        // Prune off the table spot if this step is not a possible solution
        else{
            routes[curr_step][2] = 0;
        }
    }
    return total_solutions;
}
        

// DP in this case won't make our runtime O(n)(I don't think so at least), but it will prune out all of the paths that will not lead to a possible solution
int main(){
    int n = 3, total_solutions = 0;
    // 0 and 1 will mean no path and possible path respectively.
    std::vector< std::vector<int> > routes(n, std::vector<int>(3, 1)); 
    int numPaths = findNumPaths(routes, n, 0);
    std::cout << "There are " << numPaths << " possible paths to the top of the stairs\n";
    return 0;
}
