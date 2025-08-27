vector<int> euler(vector<vector<pair<int, int>>> g, int m, int src) {  // g[cur][i] = pair{nxt, idx}
  int n = g.size();
  vector<int> used(m), it(n), cycle;
  auto dfs = [&](auto dfs, int cur) -> void {
    while (true) {
      while (it[cur] < g[cur].size() && used[g[cur][it[cur]].second]) it[cur]++;
      if (it[cur] == g[cur].size()) return;
      auto [nxt, idx] = g[cur][it[cur]];
      used[idx] = true;
      dfs(dfs, nxt);
      cycle.push_back(idx); // or {cur, nxt}
    }
  };
  dfs(dfs, src);
  reverse(cycle.begin(), cycle.end());
  if (cycle.size() != m) return {}; // check that all edges are present in the cycle, fail otherwise
  return cycle;
}

//f6b9d4
