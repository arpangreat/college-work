#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class KMP {
private:
  vector<char> sigma;
  vector<vector<int>> d;
  string text;
  string pattern;

public:
  KMP() {
    cout << "Enter text: ";
    cin >> text;
    cout << "Enter pattern: ";
    cin >> pattern;
    sigma_construction();
    computeTransition();
  }

  void sigma_construction() {
    unordered_set<char> uniqueChars(pattern.begin(), pattern.end());
    sigma.assign(uniqueChars.begin(), uniqueChars.end());
    sort(sigma.begin(), sigma.end()); // Optional: Sort for consistent output

    cout << "Input Symbol: ";
    for (char c : sigma) {
      cout << c;
    }
    cout << endl;
  }

  void computeTransition() {
    int m = pattern.size();
    int sigmaSize = sigma.size();

    // Allocate memory for d
    d.resize(m + 1, vector<int>(sigmaSize));

    // Initialize transition table
    for (int q = 0; q <= m; ++q) {
      for (int x = 0; x < sigmaSize; ++x) {
        int k = min(m + 1, q + 2);
        string Pqx = pattern.substr(0, q) + sigma[x];
        do {
          k = k - 1;
        } while (k > 0 && !isSuffix(pattern, k, Pqx));
        d[q][x] = k;
      }
    }

    // Print transition table
    cout << "Transition Table:\n";
    cout << "Q ";
    for (char c : sigma) {
      cout << c << " ";
    }
    cout << endl;
    cout << "------------\n";
    for (int i = 0; i <= m; i++) {
      cout << i << " ";
      for (int j = 0; j < sigmaSize; j++) {
        cout << d[i][j] << " ";
      }
      cout << "\n";
    }
  }

  bool isSuffix(const string &P, int k, const string &Pqx) {
    if (k > Pqx.size()) {
      return false;
    }
    return P.substr(0, k) == Pqx.substr(Pqx.size() - k, k);
  }

  void KMPMatcher() {
    int n = text.size();
    int m = pattern.size();
    int q = 0;
    vector<int> match_indices;

    for (int i = 0; i < n; ++i) {
      int x = findIndex(text[i]);
      if (x == -1)
        continue;
      q = d[q][x];
      if (q == m) {
        match_indices.push_back(i - m + 1);
      }
    }

    if (!match_indices.empty()) {
      cout << "Matching indices: ";
      for (int idx : match_indices) {
        cout << idx << " ";
      }
      cout << endl;
    } else {
      cout << "No matches found." << endl;
    }
  }

  int findIndex(char c) {
    for (int i = 0; i < sigma.size(); ++i) {
      if (sigma[i] == c) {
        return i;
      }
    }
    return -1;
  }
};

int main() {
  KMP obj;
  obj.KMPMatcher();
  return 0;
}
