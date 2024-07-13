#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
// #include <vector>

using namespace std;

class KMP {
private:
  char *sigma;
  int **d;
  string text;
  string pattern;
  int sigmaSize;

public:
  KMP() {
    cout << "Enter text: ";
    cin >> text;
    cout << "Enter pattern: ";
    cin >> pattern;
    sigma_construction();
    computeTransition();
  }

  ~KMP() {
    delete[] sigma;
    for (int i = 0; i <= pattern.size(); ++i) {
      delete[] d[i];
    }
    delete[] d;
  }

  void sigma_construction() {
    unordered_set<char> sigmaSet;

    for (char c : text) {
      sigmaSet.insert(c);
    }
    for (char c : pattern) {
      sigmaSet.insert(c);
    }

    sigmaSize = sigmaSet.size();
    sigma = new char[sigmaSize + 1]; // +1 for null terminator

    int index = 0;
    for (char c : sigmaSet) {
      sigma[index++] = c;
    }
    sigma[sigmaSize] = '\0'; // Null-terminate sigma

    sort(sigma, sigma + sigmaSize);

    cout << "Input Symbol: " << sigma << endl;
  }

  void computeTransition() {
    int m = pattern.size();

    // Allocate memory for d
    d = new int *[m + 1];
    for (int i = 0; i <= m; ++i) {
      d[i] = new int[sigmaSize];
    }

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
    for (int i = 0; i < sigmaSize; ++i) {
      cout << sigma[i] << " ";
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
    // vector<int> match_indices;
    int *match_indices = new int[n]; // Assume worst case, all characters match
    int match_count = 0;

    for (int i = 0; i < n; ++i) {
      int x = findIndex(text[i]);
      if (x == -1)
        continue;
      q = d[q][x];
      if (q == m) {
        // match_indices.push_back(i - m + 1);
        match_indices[match_count++] = i - m + 1;
        cout << (i - m + 1) << " ";
      }
    }

    // if (!match_indices.empty()) {
    //   cout << "Matching indices: ";
    //   for (int idx : match_indices) {
    //     cout << idx << " ";
    //   }
    //   cout << endl;
    // } else {
    //   cout << "No matches found." << endl;
    // }
  }

  int findIndex(char c) {
    for (int i = 0; i < sigmaSize; ++i) {
      if (sigma[i] == c) {
        return i;
      }
    }
    return -1;
  }
};

int main() {
  KMP obj;
  cout << "Matching indices: ";
  obj.KMPMatcher();
  cout << endl;
  return 0;
}
