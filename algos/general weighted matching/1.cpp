#define d(x) (lab[x.u] + lab[x.v] - 2 * e[x.u][x.v].w)
const int N = 403*2;
const int inf = 1e18;
struct Q{ int u, v, w; } e[N][N];
vector<int> p[N];
int n, m = 0, id, h, t, lk[N], sl[N], st[N], f[N], b[N][N], s[N], ed[N], q[N], lab[N];
void upd(int u, int v) { if (!sl[v] || d(e[u][v]) < d(e[sl[v]][v])) sl[v] = u; }
void ss(int v) {
  sl[v] = 0;
  for (int u = 1; u <= n; ++u) if (e[u][v].w > 0 && st[u] != v && !s[st[u]]) upd(u, v);
}
void ins(int u){ if (u <= n) q[++t] = u; else for (int v : p[u]) ins(v); }
void ch(int u, int w) { st[u] = w; if (u > n) for (int v : p[u]) ch(v, w); }
int gr(int u, int v) {
  if ((v = find(all(p[u]), v) - p[u].begin()) & 1) {
    reverse(1 + all(p[u]));
    return (int)p[u].size() - v;
  }
  return v;
}
void stm(int u, int v) {
  lk[u] = e[u][v].v;
  if (u <= n) return; Q w = e[u][v];
  int x = b[u][w.u], y = gr(u,x);
  for (int i = 0; i < y; ++i) stm(p[u][i], p[u][i^1]);
  stm(x, v); rotate(p[u].begin(), y+all(p[u]));
}
void aug(int u, int v) {
  int w = st[lk[u]];stm(u, v);if (!w) return;
  stm(w, st[f[w]]);
  aug(st[f[w]], w);
}
int lca(int u, int v) {
  for (id++; u|v; swap(u, v)) {
    if (!u) continue;if(ed[u] == id) return u;
    ed[u] = id; if (u = st[lk[u]]) u = st[f[u]]; // =, not ==
  }
  return 0;
}

//cf1d55
