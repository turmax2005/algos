vector<int> sz(n), lvl(n, -1);
auto dfs = [&](auto dfs, int cur, int prev) -> int {
  if (lvl[cur] != -1) return 0;
  sz[cur] = 1;
  for (auto [nxt, w] : g[cur]) {
    if (nxt != prev) sz[cur] += dfs(dfs, nxt, cur);
  }
  return sz[cur];
};
auto find = [&](auto find, int cur, int prev, int tot) -> int {
  int bch = -1, bsz = 0;
  for (auto [nxt, w] : g[cur]) {
    if (nxt == prev || lvl[nxt] != -1) continue;
    if (sz[nxt] > bsz) {
      bch = nxt;
      bsz = sz[nxt];
    }
  }
  if (bsz + bsz <= tot) return cur;
  return find(find, bch, cur, tot);
};
dfs(dfs, 0, 0);
auto c = find(find, 0, 0, sz[0]);
vector<pair<int, int>> stack{{c, 0}};
while (!stack.empty()) {
  auto [centroid, l] = stack.back();
  stack.pop_back();
  lvl[centroid] = l;
  for (auto [nxt, w] : g[centroid]) {
    if (lvl[nxt] != -1) continue;
    dfs(dfs, nxt, centroid);
    int new_centroid = find(find, nxt, centroid, sz[nxt]);
    stack.push_back({new_centroid, lvl[centroid] + 1});
  }
}
//0e1e52
