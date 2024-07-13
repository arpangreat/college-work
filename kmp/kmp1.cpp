#include <iostream>
#include <string>
#include <vector>

class KMPMatcher {
public:
  std::vector<std::vector<int>> computeTransitionTable(const std::string &P) {
    int m = P.length();
    std::vector<std::vector<int>> d(
        m,
        std::vector<int>(m, 0)); // Initialize the transition table with zeros

    for (int q = 0; q < m; q++) {
      for (int x = 0; x < m;
           x++) { // Iterate through all possible characters (ASCII range)
        int k = std::min(m + 1, q + 2);
        do {
          k--;
        } while (k > 0 && P[k - 1] != x);
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

  std::vector<int> findPattern(const std::string &T, const std::string &P) {
    int n = T.length();
    int m = P.length();
    std::vector<std::vector<int>> d = computeTransitionTable(P);
    std::vector<int> occurences;

    int q = 0;
    for (int i = 0; i < n; i++) {
      q = d[q][static_cast<int>(T[i])];
      if (q == m) {
        occurences.push_back(i - m + 1); // Pattern found at index i - m + 1
        q = 0;
      }
    }

    return occurences; // Pattern not found
  }
};

int main() {
  KMPMatcher matcher;
  std::string T = "ABABACABAABCABABABABACA";
  std::string P = "ABABACA";

  std::vector<int> index = matcher.findPattern(T, P);

  if (index.empty()) {
    std::cout << "Pattern not found in the text." << std::endl;
  } else {
    for (int i : index)
      std::cout << "Pattern found at index: " << i << std::endl;
  }

  return 0;
}
