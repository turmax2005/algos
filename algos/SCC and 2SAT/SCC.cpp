vector<int> find_scc(vector<vector<int>> g) {
  vector<vector<int>> r(g.size());
  for (int i = 0; i < g.size(); ++i) {
    for (int j : g[i]) r[j].push_back(i);
  }
  vector<int> used(g.size()), tout(g.size());
  int time = 0;
  auto dfs = [&](auto dfs, int cur) -> void {
    if (used[cur]) return;
    used[cur] = 1;
    for (int nxt : g[cur]) {
      dfs(dfs, nxt);
    }
    tout[cur] = time++;
  };
  for (int i = 0; i < g.size(); ++i) if (!used[i]) dfs(dfs, i);
  vector<int> ind(g.size());
  iota(ind.begin(), ind.end(), 0);
  sort(all(ind), [&](int i, int j){return tout[i] > tout[j];});
  vector<int> scc(g.size(), -1);
  auto go = [&](auto go, int cur, int color) -> void {
    if (scc[cur] != -1) return;
    scc[cur] = color;
    for (int nxt : r[cur]) {
      go(go, nxt, color);
    }
  };
  int color = 0;
  for (int i : ind) {
    if (scc[i] == -1) go(go, i, color++);
  }
  return scc;
}