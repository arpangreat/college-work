#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int matrixChainMultiplication(vector<int> &p, int n) {
  vector<vector<int>> m(n, vector<int>(n, 0));

  for (int length = 2; length < n; ++length) {
    for (int i = 1; i < n - length + 1; ++i) {
      int j = i + length - 1;
      m[i][j] = numeric_limits<int>::max();
      for (int k = i; k <= j - 1; ++k) {
        int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
        if (q < m[i][j]) {
          m[i][j] = q;
        }
      }
    }
  }

  return m[1][n - 1];
}

int main() {
  int numMatrices;
  cout << "Enter the number of matrices: ";
  cin >> numMatrices;

  vector<int> dimensions(numMatrices + 1);
  cout << "Enter the dimensions of the matrices:\n";
  for (int i = 0; i <= numMatrices; ++i) {
    cout << "Dimension " << i << ": ";
    cin >> dimensions[i];
  }

  int result = matrixChainMultiplication(dimensions, dimensions.size());
  cout << "Minimum number of multiplications is " << result << endl;

  return 0;
}
