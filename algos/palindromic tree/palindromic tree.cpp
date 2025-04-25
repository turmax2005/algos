int n;cin >> n;string s;cin >> s;
const int alpha = 26;
const char a = 'a';
vector <int> suf{0, 0}, len{-1,0};
vector <array <int, alpha> > to{{}, {}};
vector <int> p(n + 1);
int sz = 2;
for (int i = 0; i < n; ++i) {
  auto check = [&] (int l) {
    return i > l && s[i] == s[i - 1 - l];
  };
  int par = p[i];
  while (!check(len[par])) {
    par = suf[par];
  }
  if (to[par][s[i]-a] == 0) {
    p[i+1]=to[par][s[i]-a]=sz++;
    to.emplace_back();
    len.emplace_back(len[par]+2);
    if (par == 0) {
      suf.emplace_back(1);
    }
    else {
      do {
        par = suf[par];
      } while (!check(len[par]));
      suf.emplace_back(to[par][s[i]-a]);
    }
  }
  else {
    p[i+1]=to[par][s[i]-a];
  }
}
vector <int> d(sz), up(sz, 1); //d[1] = 0 sic
for (int i = 2; i < sz; ++i) {
  d[i] = len[i] - len[suf[i]];
  if (d[i] == d[suf[i]]) {
    up[i] = up[suf[i]];
  }
  else {
    up[i] = suf[i];
  }
}
vector <int> dp(n + 1, n), last(sz);
dp[0] = 0;
for (int i = 1; i <= n; ++i) {
  int u = p[i];
  while (u != 1) {
    if (suf[u] == up[u]) {
      last[u] = dp[i - len[u]];
    }
    else {
      last[u] = min(last[suf[u]], dp[i - len[up[u]] - d[u]]);
    }
    dp[i] = min(dp[i], last[u] + 1);
    u = up[u];
  }
}
cout << dp.back() << '\n';
