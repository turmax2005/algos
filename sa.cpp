const int inf = 1e9;
struct rmq {
  int n;
  vector<int> a;
  void build(const vector<int> &x) {
    assert(x.size() == n);
    for (int i = 0; i < n; ++i) a[n + i] = x[i];
    for (int i = n - 1; i > 0; --i) a[i] = min(a[2 * i], a[2 * i + 1]);
  }
  rmq(int n) : n(n), a(2 * n, inf) {}
  void put(int i, int x) {
    a[i + n] = min(a[i + n], x);
    for (i = (i + n) / 2; i > 0; i /= 2) {
      a[i] = min(a[i * 2], a[i * 2 + 1]);
    }
  }
  int getMin(int l, int r) { //[l;r)
    assert(l < r);
    int res = inf;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l & 1) res = min(res, a[l++]);
      if (r & 1) res = min(res, a[--r]);
    }
    return res;
  }
};
template <typename T>
struct suar {
    vector <int> sa, lcp, rank; rmq t;
    suar (T s, int lim=256) : t((int)s.size() - 1) { // s must be nonempty, 0 < s[i] < lim!
        int n = (int)s.size() + 1, k = 0, a, b; s.app(0);
        vector <int> x(s.begin(), s.end()), y(n), ws(max(n, lim));rank.resize(n);
        sa = lcp = y, iota(sa.begin(), sa.end(), 0);
        for (int j = 0, p = 0; p < n; j = max(1ll, j * 2), lim = p) {
            p = j, iota(y.begin(), y.end(), n - j);
            for (int i = 0; i < n; i++) if (sa[i] >= j) y[p++] = sa[i] - j;
            fill(ws.begin(), ws.end(), 0);
            for (int i = 0; i < n; i++) ws[x[i]]++;
            for (int i = 1; i < lim; i++) ws[i] += ws[i - 1];
            for (int i = n; i--; ) sa[--ws[x[y[i]]]] = y[i];
            swap(x, y), p = 1, x[sa[0]] = 0;
            for (int i = 1; i < n; i++) a = sa[i - 1], b = sa[i], x[b] = (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
        }
        for (int i = 1; i < n; i++) rank[sa[i]] = i;
        for (int i = 0, j; i < n - 1; lcp[rank[i++]]=k)
          for (k && k--, j = sa[rank[i] - 1];
              s[i + k] == s[j + k]; k++);
        sa.erase(sa.begin()); lcp.erase(lcp.begin()); lcp.erase(lcp.begin());
        t.build(lcp);
        for (auto &e : rank) {
            e--;
        }
    }
    int getLcp(int i, int j) {
        i = rank[i]; j = rank[j];
        if (j < i) {
          swap(i, j);
        }
        if (i == j) {
          return inf;
        }
        else {
          return t.getMin(i, j);
        }
    }
};
