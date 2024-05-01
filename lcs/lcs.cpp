#include <bits/stdc++.h>

int lcs(std::string X, std::string Y, int m, int n) {
  if (m == 0 || n == 0)
    return 0;

  if (X[m - 1] == Y[n - 1])
    return 1 + lcs(X, Y, m - 1, n - 1);
  else
    return std::max(lcs(X, Y, m, n - 1), lcs(X, Y, m - 1, n));
}

int main() {
  std::string s1 = "AGGTAB";
  std::string s2 = "GXTXAYB";
  int m = s1.size();
  int n = s2.size();

  std::cout << "Length of LCS is" << lcs(s1, s2, m, n) << std::endl;
}
