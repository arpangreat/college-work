#include <iostream>
#include <string>
#include <vector>

class KMPMatcher {
public:
  std::vector<std::vector<int>> computeTransitionTable(const std::string &P) {
    int m = P.length();
    std::vector<std::vector<int>> d(
        m,
        std::vector<int>(256, 0)); // Initialize the transition table with zeros

    for (int q = 0; q < m; q++) {
      for (int x = 0; x < 256;
           x++) { // Iterate through all possible characters (ASCII range)
        int k = std::min(m, q + 1);
        while (k > 0 && P[k - 1] != static_cast<char>(x)) {
          k = d[k - 1][static_cast<int>(P[k - 1])];
        }
        d[q][x] = k;
      }
    }

    std::cout << "Transition table:" << std::endl;
    for (int q = 0; q < m; q++) {
      std::cout << "q = " << q << ": ";
      for (int x = 0; x < m; x++) {
        std::cout << d[q][x] << " ";
      }
      std::cout << std::endl;
    }

    return d;
  }

  int findPattern(const std::string &T, const std::string &P) {
    int n = T.length();
    int m = P.length();
    std::vector<std::vector<int>> d = computeTransitionTable(P);

    int q = 0;
    for (int i = 0; i < n; i++) {
      q = d[q][static_cast<int>(T[i])];
      if (q == m) {
        return i - m + 1; // Pattern found at index i - m + 1
      }
    }

    return -1; // Pattern not found
  }
};

int main() {
  KMPMatcher matcher;
  std::string T = "ABABACABAABCABAB";
  std::string P = "ABABACA";

  int index = matcher.findPattern(T, P);

  if (index == -1) {
    std::cout << "Pattern not found in the text." << std::endl;
  } else {
    std::cout << "Pattern found at index: " << index << std::endl;
  }

  return 0;
}
