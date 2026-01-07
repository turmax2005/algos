/// w(a,c)+w(b,d)<=w(a,d)+w(b,c) for a<=b<=c<=d 
/// https://codeforces.com/blog/entry/93772 by seiko.iwasawa
/// dp(i) = min(j<i : dp(j)+w(j,i)), dp(0) = 0
auto w = [&](int j, int i) { return b[j] * 1LL * a[i]; };
dp[0] = 0;
deque<pair<int, int>> k = {{0, 1}};
for (int i = 1; i < n; ++i) {
  dp[i] = dp[k[0].first] + w(k[0].first, i);
  if (i == n - 1) {
    break;
  }
  ++k[0].second;
  if (SZ(k) >= 2 && k[0].second == k[1].second) {
    k.pop_front();
  }
  while (!k.empty() &&
         dp[k.back().first] + w(k.back().first, k.back().second) >=
             dp[i] + w(i, k.back().second)) {
    k.pop_back();
  }
  if (k.empty()) {
    k.push_back({i, i + 1});
  } else if (dp[k.back().first] + w(k.back().first, n - 1) >=
             dp[i] + w(i, n - 1)) {
    int left = k.back().second, right = n - 1;
    while (right - left > 1) {
      int mid = left + right >> 1;
      (dp[k.back().first] + w(k.back().first, mid) >= dp[i] + w(i, mid)
           ? right
           : left) = mid;
    }
    k.push_back({i, right});
  }
}
cout << dp[n - 1] << '\n';
