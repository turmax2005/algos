
void add(int u, int a, int v) {
  int x = n + 1; while (x <= m && st[x]) ++x;
  if (x > m) ++m;
  lab[x] = s[x] = st[x] = 0;
  lk[x] = lk[a];
  p[x].clear();
  p[x].push_back(a);
#define op(q) for (int i = q, j = 0; i != a; i=st[f[j]]) p[x].push_back(i), p[x].push_back(j=st[lk[i]]), ins(j) // also not ==
  op(u); reverse(1+all(p[x]));op(v);
  ch(x, x); for (int i = 1; i <= m; ++i) e[x][i].w = e[i][x].w = 0;
  fill(b[x]+1, b[x]+n+1, 0);
  for (int u : p[x]) {
    for (int v = 1; v <= m; ++v) if (!e[x][v].w || d(e[u][v]) < d(e[x][v])) e[x][v] = e[u][v], e[v][x] = e[v][u];
    for (int v = 1; v <= n; ++v) if (b[u][v]) b[x][v] = u;
  }
  ss(x);
}
void ex(int u) {
  for (int x : p[u]) ch(x, x);
  int a = b[u][e[u][f[u]].u], r = gr(u, a);
  for (int i = 0; i < r; i += 2) {
    int x = p[u][i], y = p[u][i + 1];
    f[x] = e[y][x].u; s[x] = 1; s[y] = 0; sl[x] = 0; ss(y); ins(y);
  }
  s[a] = 1; f[a] = f[u];
  for (int i = r + 1; i < p[u].size(); ++i) s[p[u][i]] = -1, ss(p[u][i]);
  st[u] = 0;
}
bool on(const Q &e) {
  int u = st[e.u], v = st[e.v], a;
  if (s[v] == -1) {
    f[v] = e.u, s[v] = 1, a = st[lk[v]], sl[v] = sl[a] = s[a] = 0, ins(a);
  } else if (!s[v]) {
    a = lca(u, v); if (!a) return aug(u, v), aug(v, u), 1; else add(u, a, v);
  }
  return 0;
}

