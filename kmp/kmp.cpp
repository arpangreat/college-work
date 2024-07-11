#include <iostream>
#include <string>
#include <vector>

class KMPMatcher {
public:
  std::vector<int> computeTransitionTable(const std::string &P) {
    int m = P.length();
    std::vector<int> d(m * 4,
                       0); // Initialize the transition table with zeros

    for (int q = 0; q < m; q++) {
      for (int x = 0; x < 4;
           x++) { // Iterate through all possible characters (ASCII range)
        int k = std::min(m + 1, q + 2);
        do {
          k--;
        } while (k > 0 /* && m > q */ && P[k - 1] != P[q]);
        d[q * 4 + x] = k;
      }
    }

    return d;
  }

  std::vector<int> findPattern(const std::string &T, const std::string &P) {
    int n = T.length();
    int m = P.length();
    std::vector<int> d = computeTransitionTable(P);
    std::vector<int> occurences;

    int q = 0;
    for (int i = 0; i < n; i++) {
      q = d[q * 4 + i];
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
  std::string T = "TESTTEXT";
  std::string P = "TEST";

  std::vector<int> index = matcher.findPattern(T, P);

  if (index.empty()) {
    std::cout << "Pattern not found in the text." << std::endl;
  } else {
    std::cout << "Pattern found at index: ";
    for (int i : index) {
      std::cout << i << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}
