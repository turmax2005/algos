
bool bfs() {
  fill(s+1, s+m+1, -1);fill(sl+1, sl+m+1, 0); // s is filled with -1
  h = 1, t = 0; for (int i = 1; i <= m; ++i) if (st[i] == i && !lk[i]) f[i] = s[i] = 0, ins(i);
  if (h > t) return 0;
  while (1) {
    while (h <= t) {
      int u = q[h++];
      if (s[st[u]] != 1) {
        for (int v = 1; v <= n; ++v) if (e[u][v].w > 0 && st[u] != st[v]) {
          if (d(e[u][v])) upd(u, st[v]); else if (on(e[u][v])) return 1;
        }
      }
    }
    int x = inf;
    for (int i = n+1; i <= m; ++i) if (st[i] == i && s[i] == 1) x = min(x, lab[i]/2);
    for (int i = 1; i <= m; ++i) if (st[i] == i && sl[i] && s[i] != 1) x = min(x, d(e[sl[i]][i])>>s[i]+1);
    for (int i = 1; i <= n; ++i) if (~s[st[i]]) if ((lab[i] += (s[st[i]] * 2 - 1) * x) <=0) return 0;
    for (int i = n + 1; i <= m; ++i) if (st[i] == i && ~s[st[i]]) lab[i] += (2 - 4 * s[st[i]]) * x;
    h = 1, t = 0;
    for (int i = 1; i <= m; ++i) if (st[i] == i && sl[i] && st[sl[i]] != i && !d(e[sl[i]][i]) && on(e[sl[i]][i])) return 1;
    for (int i = n+1; i <= m; ++i) if (st[i] == i && s[i] == 1 && !lab[i]) ex(i);
  }
}

pair<int, vector<array<int, 2>>> run(int N, vector<array<int, 3>> edges) {
  for (auto &[u, v, w] : edges) ++u, ++v;
  fill(ed+1, ed+m+1, 0);
  fill(lk+1, lk+m+1, 0);
  n = m = N;
  id = 0;
  iota(st + 1, st + n + 1, 1);
  int wm = 0, weight = 0;
  for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) e[i][j] = {i,j,0};
  for (auto [u, v, w] : edges) wm = max(wm, e[v][u].w = e[u][v].w = max(e[u][v].w, w));
  for (int i = 1; i <= n; ++i) p[i].clear();
  for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) b[i][j] = i==j?i:0;
  fill_n(lab+1, n, wm); while (bfs());
  vector<array<int, 2>> matching;
  for (int i = 1; i <= n; ++i) if (i < lk[i]) weight += e[i][lk[i]].w, matching.push_back({i - 1, lk[i] - 1});
  return {weight, matching};
}
