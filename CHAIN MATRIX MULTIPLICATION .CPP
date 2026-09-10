#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Function to find the optimal parenthesis configuration and minimum cost
int matrixChainOrder(const vector<int>& p) {
    int n = p.size() - 1; // Number of matrices
    
    // dp[i][j] stores the minimum number of scalar multiplications 
    // needed to compute the matrix chain Ai...Aj
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    // Base Case: dp[i][i] = 0 (multiplying 1 matrix requires 0 operations)
    // Already handled since vector is initialized to 0.

    // L is the chain length (ranging from 2 matrices up to n matrices)
    for (int L = 2; L <= n; L++) {
        for (int i = 1; i <= n - L + 1; i++) {
            int j = i + L - 1;
            dp[i][j] = INT_MAX;

            // Try every possible split position 'k' between i and j
            for (int k = i; k <= j - 1; k++) {
                // cost = cost of left subchain + cost of right subchain + cost of combining them
                int cost = dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j];
                
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                }
            }
        }
    }

    // The result for the full chain A1...An is stored at dp[1][n]
    return dp[1][n];
}

int main() {
    // Array dimensions representing matrices:
    // A1: 40x20, A2: 20x30, A3: 30x10, A4: 10x30
    vector<int> arr = {40, 20, 30, 10, 30}; 
    
    int minOps = matrixChainOrder(arr);
    
    cout << "Minimum number of multiplications is: " << minOps << endl;
    
    return 0;
}
