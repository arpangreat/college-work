#include <algorithm>
#include <iostream>
#include <string>
using namespace std;
class KMP {
private:
  char *sigma;
  int size;
  int **d;
  string text;
  string pattern;

public:
  KMP() {
    cout << "Enter text: ";
    cin >> text;
    cout << "Enter pattern: ";
    cin >> pattern;
    size = pattern.size();
    sigma = new char[size + 1]; // +1 for null terminator
    sigma_construction();
  }
  ~KMP() {
    delete[] sigma;
    for (int i = 0; i <= pattern.size(); ++i) {
      delete[] d[i];
    }
    delete[] d;
  }
  void sigma_construction() {
    int uniqueIndex = 0;
    bool found;
    // Initialize sigma array
    for (int i = 0; i < size; ++i) {
      found = false;
      for (int j = 0; j < uniqueIndex; ++j) {
        if (sigma[j] == pattern[i]) {
          found = true;
          break;
        }
      }
      if (!found) {
        sigma[uniqueIndex++] = pattern[i];
      }
    }
    sigma[uniqueIndex] = '\0'; // Null-terminate sigma
    cout << "Input Symbol: " << sigma << endl;
  }

  void compute_transition() {
    int m = pattern.size();
    int count = 0;
    int i = 0;
    while (sigma[i] != '\0') {
      count++;
      i++;
    }

    // Allocate memory for d
    d = new int *[m + 1];
    for (int i = 0; i <= m; ++i) {
      d[i] = new int[count];
    }

    // Initialize transition table
    for (int q = 0; q <= m; ++q) {
      for (int x = 0; x < count; ++x) {
        int k = min(m + 1, q + 2);
        string Pqx = pattern.substr(0, q) + sigma[x];
        do {
          k = k - 1;
        } while (k > 0 && !isSuffix(pattern, k, Pqx));
        d[q][x] = k;
      }
    }
    // Fix the last row transitions (q = m)
    for (int x = 0; x < count; ++x) {
      d[m][x] = m; // Complete match transitions to itself
    }
    // Print transition table
    cout << "Transition Table:\n";
    cout << "Q";
    for (int i = 0; sigma[i] != '\0'; i++) {
      cout << "  " << sigma[i];
    }
    cout << endl;
    cout << "------------\n";
    for (int i = 0; i <= m; i++) {
      cout << i << " ";
      for (int j = 0; j < count; j++) {
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
  void KMP_Matcher() {
    int n = text.size();
    int m = pattern.size();
    int q = 0;
    int *match_indices = new int[n]; // Assume worst case, all characters match
    int match_count = 0;
    for (int i = 0; i < n; ++i) {
      int x = findIndex(text[i]);
      if (x == -1)
        continue;
      q = d[q][x];
      if (q == m) {
        match_indices[match_count++] = i - m + 1;
        cout << (i - m + 1) << " ";
      }
    }
    delete[] match_indices; // Free allocated memory
  }
  int findIndex(char c) {
    for (int i = 0; sigma[i] != '\0'; ++i) {
      if (sigma[i] == c) {
        return i;
      }
    }
    return -1;
  }
};

int main() {
  KMP obj;
  obj.compute_transition();
  cout << "Matching indices: ";
  obj.KMP_Matcher();
  cout << endl;
  return 0;
}
