#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Function to check if the suffix of P of length k is equal to the end of Pqx
bool isSuffix(const string &P, int k, const string &Pqx) {
  if (k > Pqx.size())
    return false;
  return P.substr(0, k) == Pqx.substr(Pqx.size() - k, k);
}

// Function to construct the transition table
void constructTransitionTable(const string &P, const string &sigma, int **d) {
  int m = P.size();

  for (int q = 0; q <= m; ++q) {
    for (int x = 0; x < sigma.size(); ++x) {
      int k = min(
          m + 1, q + 2); // +1 for x, +2 for subsequent repeat loop to decrement

      string Pqx = P.substr(0, q) + sigma[x];
      do {
        k = k - 1; // work backwards from q+1
      } while (k > 0 && !isSuffix(P, k, Pqx));

      d[q][x] = k; // assign transition table
    }
  }
}

// Function to search the pattern P in text T using the transition table
vector<int> searchPattern(const string &T, const string &P, int **d,
                          const string &sigma) {
  int n = T.size();
  int m = P.size();
  int q = 0;
  vector<int> match_indices;

  for (int i = 0; i < n; ++i) {
    int x = sigma.find(T[i]);
    if (x == string::npos)
      continue; // ignore characters not in sigma

    q = d[q][x];
    if (q == m) {
      match_indices.push_back(i - m + 1);
    }
  }

  return match_indices;
}

int main() {
  string T = "ababcabcabc";
  string P = "abc";
  string sigma = "abc";

  int m = P.size();
  int sigma_size = sigma.size();

  // Create the transition table
  int **d = new int *[m + 1];
  for (int i = 0; i <= m; ++i) {
    d[i] = new int[sigma_size];
  }

  // Construct the transition table
  constructTransitionTable(P, sigma, d);

  // Debugging: Print the transition table
  cout << "Transition table:" << endl;
  for (int q = 0; q <= m; ++q) {
    for (int x = 0; x < sigma_size; ++x) {
      cout << d[q][x] << " ";
    }
    cout << endl;
  }

  // Search for the pattern
  vector<int> results = searchPattern(T, P, d, sigma);

  if (!results.empty()) {
    cout << "Pattern found at indices: ";
    for (int idx : results) {
      cout << idx << " ";
    }
    cout << endl;
  } else {
    cout << "Pattern not found" << endl;
  }

  // Free the allocated memory
  for (int i = 0; i <= m; ++i) {
    delete[] d[i];
  }
  delete[] d;

  return 0;
}
