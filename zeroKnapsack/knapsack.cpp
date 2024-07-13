#include <iostream>
#include <vector>
using namespace std;

pair<int, vector<int>> knapsack(int W, const vector<int> &weights,
                                const vector<int> &values, int n) {
  vector<vector<int>> K(n + 1, vector<int>(W + 1));

  for (int i = 0; i <= n; ++i) {
    for (int w = 0; w <= W; ++w) {
      if (i == 0 || w == 0)
        K[i][w] = 0;
      else if (weights[i - 1] <= w)
        K[i][w] =
            max(values[i - 1] + K[i - 1][w - weights[i - 1]], K[i - 1][w]);
      else
        K[i][w] = K[i - 1][w];
    }
  }

  int maxValue = K[n][W];

  int w = W;
  vector<int> itemsIncluded;
  for (int i = n; i > 0 && maxValue > 0; i--) {
    if (maxValue != K[i - 1][w]) {
      itemsIncluded.push_back(i - 1);
      maxValue -= values[i - 1];
      w -= weights[i - 1];
    }
  }

  return {K[n][W], itemsIncluded};
}

int main() {
  int n, W;
  cout << "Enter number of items: ";
  cin >> n;

  vector<int> values(n);
  vector<int> weights(n);

  cout << "Enter values and weights of items:\n";
  for (int i = 0; i < n; ++i) {
    cout << "Item " << i + 1 << " value: ";
    cin >> values[i];
    cout << "Item " << i + 1 << " weight: ";
    cin >> weights[i];
  }

  cout << "Enter maximum weight of knapsack: ";
  cin >> W;

  auto result = knapsack(W, weights, values, n);
  int maxValue = result.first;
  vector<int> itemsIncluded = result.second;

  cout << "Maximum value in Knapsack = " << maxValue << endl;

  return 0;
}
