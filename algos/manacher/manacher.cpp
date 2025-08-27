vector<int> manacher(const string &s, int even) {
  int l = 0, r = 0, n = s.size();
  vector<int> man(n, 0);
  for (int i = 1; i < n; i++) {
    int j = i - even;
    if (j <= r) {
      man[i] = min(r - j, man[l + r - j]);
    }
    while (j + man[i] + 1 < n && i - man[i] > 0 && s[j + man[i] + 1] == s[i - man[i] - 1]) {
      man[i]++;
    }
    if (j + man[i] > r) {
      l = i - man[i];
      r = j + man[i];
    }
  }
  return man;
}

// abacaba : odd : (0 1 0 3 0 1 0); even : (0 0 0 0 0 0 0)
// abbaa : odd : (0 0 0 0 0); even : (0 0 2 0 1)
bool pal(int from, int len) {
    if (len == 0) {
        return true;
    }
    int m = len/2;
    if (len & 1) {
        return odd[from + m] >= m;
    }
    else {
        return even[from + m] >= m;
    }
}

//8a64d6
