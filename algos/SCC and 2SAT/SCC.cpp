vector<int> find_scc(vector<vector<int>> g) {
  int n = g.size();
  vector<vector<int>> r(n);
  for (int i = 0; i < n; ++i) {
    for (int j : g[i]) r[j].push_back(i);
  }
  vector<int> used(n), tout(n);
  int time = 0;
  auto dfs = [&](auto dfs, int cur) -> void {
    used[cur] = 1;
    for (int nxt : g[cur]) {
      if (!used[nxt]) dfs(dfs, nxt);
    }
    tout[cur] = time++;
  };
  for (int i = 0; i < n; ++i) if (!used[i]) dfs(dfs, i);
  vector<int> ind(n);
  iota(all(ind), 0);
  sort(all(ind), [&](int i, int j){return tout[i] > tout[j];});
  vector<int> scc(n, -1);
  auto go = [&](auto go, int cur, int color) -> void {
    scc[cur] = color;
    for (int nxt : r[cur]) {
      if (scc[nxt] == -1) go(go, nxt, color);
    }
  };
  int color = 0;
  for (int i : ind) {
    if (scc[i] == -1) go(go, i, color++);
  }
  return scc;
}
