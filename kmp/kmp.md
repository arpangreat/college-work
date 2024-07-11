vector<vector<size_t>> Preprocess(const string &_pattern) {
  vector<string> pattern_vec;
  for (size_t i = 0; i <= _pattern.size(); ++i) // m
    pattern_vec.push_back(_pattern.substr(0, i));

  vector<vector<int>> is_match_matrix(1 + _pattern.size(),
                                      vector<int>(1 + _pattern.size(), -1));
  for (size_t i = 0; i < is_match_matrix.size(); ++i) // m
  {
    for (size_t j = 0; j <= i; ++j) // m
    {
      if (pattern_vec[i - j] == _pattern.substr(j, i - j)) {
        is_match_matrix[i][j] = i - j;
      }
    }
  }

  // note:
  is_match_matrix[_pattern.size()][0] = -1;

  vector<vector<size_t>> status_matrix(1 + _pattern.size(),
                                       vector<size_t>(26, 0));

  for (size_t i = 0; i < status_matrix.size(); ++i) // m
  {
    char c = 'a';
    while (c <= 'z') // E
    {
      for (size_t j = 0; j <= i; ++j) // m
      {
        if (-1 != is_match_matrix[i][j] &&
            c == _pattern[is_match_matrix[i][j]]) {
          status_matrix[i][c - 'a'] = is_match_matrix[i][j] + 1;
          break;
        }
      }

      c++;
    }
  }

  return status_matrix;
}

m = length(P);
for  q = 0 through m  do
    for each character  x  in Σ
    k = min(m+1, q+2); // +1 for x, +2 for subsequent repeat loop to
    decrement
        repeat  k = k-1 // work backwards from q+1
        until  Pk 'is-suffix-of' Pqx;
        d(q, x) = k;    // assign transition table
end for; end for;

return  d;
End algorithm.

write code for
n = len(T), q=0
for i=0 to n-1 do
  q = d[q,i];
  if q == m
    return i-m
using
m = length(P);
for  q = 0 through m  do
    for each character  x  in Σ
    k = min(m+1, q+2); // +1 for x, +2 for subsequent repeat loop to
    decrement
        repeat  k = k-1 // work backwards from q+1
        until  Pk 'is-suffix-of' Pqx;
        d(q, x) = k;    // assign transition table
end for; end for;
