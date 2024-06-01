vector<int> manacher_odd(const string &s) {
  vector<int> man(s.size(), 0);
  int l = 0, r = 0;
  int n = s.size();
  for (int i = 1; i < n; i++) {
    if (i <= r) {
      man[i] = min(r - i, man[l + r - i]);
    }
    while (i + man[i] + 1 < n && i - man[i] - 1 >= 0 && s[i + man[i] + 1] == s[i - man[i] - 1]) {
      man[i]++;
    }
    if (i + man[i] > r) {
      l = i - man[i];
      r = i + man[i];
    }
  }
  return man;
}
// abacaba : (0 1 0 3 0 1 0)
// abbaa : (0 0 0 0 0)

vector <int> manacher_even(const string &s) {
  assert(s.size());
  string t;
  for (int i = 0; i + 1 < s.size(); ++i) {
    t += s[i];
    t += '#';
  }
  t += s.back();
  auto odd = manacher_odd(t);
  vector <int> ans;
  for (int i = 1; i < odd.size(); i += 2) {
    ans.push_back((odd[i]+1)/2);
  }
  return ans;
}
// abacaba : (0 0 0 0 0 0)
// abbaa : (0 2 0 1)
