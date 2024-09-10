struct Dsu {
  int n;
  vector<pair<int &, int>> s;
  vector<int> p, sz;
  // other info

  Dsu(int n) : n(n), p(n), sz(n, 1){
    iota(all(p), 0);
  }

  int get(int u) {
    while (u != p[u]) u = p[u];
    return u;
  }

  bool merge(int u, int v) {
    u = get(u), v = get(v);
    if (u == v) return false;
    if (sz[v] < sz[u]) swap(u, v);
    s.app({p[u], p[u]});
    s.app({sz[v], sz[v]});
    // app other info like s.app({comp, comp});
    p[u] = v;
    sz[v] += sz[u];
    return true;
  }

  void rollback(int sz) {
    while (s.size() != sz) {
      s.back().first = s.back().second;
      s.pop_back();
    }
  }
};

struct DcpOffline {
  int n;
  vector<vector<pair<int, int>>> d;

  void addEdgeOnSegment(int l, int r, int a, int b) {
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l & 1) d[l++].app({a, b});
      if (r & 1) d[--r].app({a, b});
    }
  }

  template<typename T>
  void dfs(Dsu &dsu, T act) {
    dfs(1, 0, n, dsu, act);
  }

  template<typename T>
  void dfs(int v, int l, int r, Dsu &dsu, T act) {
    int sz = dsu.s.size();
    for (auto [u, v]: d[v]) {
      dsu.merge(u, v);
    }
    if (l + 1 == r) {
      act(l, dsu);
    } else {
      int m = (l + r) / 2;
      dfs(v * 2, l, m, dsu, act);
      dfs(v * 2 + 1, m, r, dsu, act);
    }
    dsu.rollback(sz);
  }

  DcpOffline(int maxt) : n(2 << __lg(maxt + 1)), d(2 * n) {}
};