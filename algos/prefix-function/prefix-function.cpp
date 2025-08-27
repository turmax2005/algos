vector<int> prefix_function(string s) {
  int n = s.size();
  vector<int> p(n);
  for (int i = 1; i < n; ++i) {
    p[i] = p[i - 1];
    while (p[i] && s[p[i]] != s[i]) p[i] = p[p[i] - 1];
    p[i] += s[i] == s[p[i]];
  }
  return p;
}

//91103c
