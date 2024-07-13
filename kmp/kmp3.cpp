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

    return d;
  }

  std::vector<int> findPattern(const std::string &T, const std::string &P) {
    int n = T.length();
    int m = P.length();
    std::vector<std::vector<int>> d = computeTransitionTable(P);
    std::vector<int> occurrences;

    int q = 0;
    for (int i = 0; i < n; i++) {
      q = d[q][static_cast<int>(T[i])];
      if (q == m) {
        occurrences.push_back(i - m + 1); // Pattern found at index i - m + 1
        q = 0;                            // Reset the state
      }
    }

    return occurrences;
  }
};

int main() {
  KMPMatcher matcher;
  std::string T = "ABABABCABAABCABAB";
  std::string P = "ABABACA";

  std::vector<int> indices = matcher.findPattern(T, P);

  if (indices.empty()) {
    std::cout << "Pattern not found in the text." << std::endl;
  } else {
    std::cout << "Pattern found at indices: ";
    for (int index : indices) {
      std::cout << index << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}
