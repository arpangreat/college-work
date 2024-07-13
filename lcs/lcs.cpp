#include <algorithm>
#include <iostream>
#include <vector>

std::string longestCommonSubsequence(std::string text1, std::string text2) {
  int m = text1.length();
  int n = text2.length();

  std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      if (text1[i - 1] == text2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }

  std::string lcs = "";
  int i = m, j = n;
  while (i > 0 && j > 0) {
    if (text1[i - 1] == text2[j - 1]) {
      lcs = text1[i - 1] + lcs;
      i--;
      j--;
    } else if (dp[i - 1][j] > dp[i][j - 1]) {
      i--;
    } else {
      j--;
    }
  }

  return lcs;
}

int main() {

  std::string text1, text2;
  std::cout << "input first string: ";
  std::cin >> text1;
  std::cout << "input second string: ";
  std::cin >> text2;

  std::string lcs = longestCommonSubsequence(text1, text2);
  std::cout << "Longest Common Subsequence: " << lcs << std::endl;

  return 0;
}

// The time complexity will be O(m * n) where m and n is strings size
