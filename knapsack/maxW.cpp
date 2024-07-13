#include <iostream>
#include <vector>

int knapsack(int W, std::vector<int> &wt, std::vector<int> &val, int n) {
  std::vector<std::vector<int>> dp(n + 1, std::vector<int>(W + 1, 0));

  for (int i = 1; i <= n; i++) {
    for (int w = 1; w <= W; w++) {
      if (wt[i - 1] <= w) {
        dp[i][w] =
            std::max(val[i - 1] + dp[i - 1][w - wt[i - 1]], dp[i - 1][w]);
      } else {
        dp[i][w] = dp[i - 1][w];
      }
    }
  }

  return dp[n][W];
}

int main() {
  int W = 50;                                // Maximum capacity of the knapsack
  std::vector<int> val = {40, 80, 120, 140}; // Values of items
  std::vector<int> wt = {20, 30, 50, 60};    // Weights of items
  int n = val.size();                        // Number of items

  int maxProfit = knapsack(W, wt, val, n);
  std::cout << "Maximum profit: " << maxProfit << std::endl;

  return 0;
}

/*
This program takes as input the maximum capacity of the knapsack (W), the values
of the items (val), the weights of the items (wt), and the number of items (n).
It then uses dynamic programming to find the maximum profit that can be obtained
by selecting a subset of the items. The result is printed out at the end.

This implementation has a time complexity of O(n×W), where nn is the
number of items and WW is the maximum capacity of the knapsack.
*/
