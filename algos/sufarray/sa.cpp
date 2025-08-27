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
vector <int> SA(const T &a) {
  int m = *max_element(all(a)) + 1, n = a.size();
  vector <int> sa(n), nsa(n), pre(max(n, m)), x(a.begin(), a.end()), y(n);
  for (int e : x) pre[e]++;
  for (int i = 1; i < m; ++i) pre[i] += pre[i - 1];
  for (int i = 0; i < n; ++i) sa[--pre[x[i]]]=i;
  int dif = 1;
  y[sa.front()]=0;
  for (int i = 1; i < n; ++i) {
    dif += x[sa[i]]!=x[sa[i-1]];
    y[sa[i]] = dif - 1;
  }
  x = y;
  for (int h = 1; dif < n; h *= 2) {
    fill(all(pre), 0);
    for (int e : x) pre[e]++;
    for (int i = 1; i < dif; ++i) pre[i] += pre[i - 1];
    for (int t = n; t--; ) {
      int i = sa[t];
      if (i>=h) {
        nsa[--pre[x[i-h]]]=i-h;
      }
      else if (i + 1 != h) {
        nsa[--pre[x[i-h+n+1]]]=i-h+n+1;
      }
    }
    nsa[--pre[x[n - h]]]=n-h;
    sa = nsa;
    auto getr = [&] (int i) {
      if (i + h < n) {
        return x[i + h];
      }
      else {
        return x[i + h - n - 1];
      }
    };
    dif = 1;
    y[sa.front()]=0;
    for (int i = 1; i < n; ++i) {
      if (x[sa[i]]!=x[sa[i-1]] || sa[i-1]+h==n) {
        dif++;
      }
      else {
        dif += getr(sa[i]) != getr(sa[i-1]);
      }
      y[sa[i]]=dif-1;
    }
    x = y;
  }
  return sa;
}

template <typename T>
struct suar {
  vector <int> sa, lcp, pos; rmq t;
  suar (const T &a) : t((int)a.size() - 1) {
    sa = SA(a);
    int n = (int)a.size(), k = 0;
    lcp.resize(n - 1);
    pos.resize(n);
    for (int i = 0; i < n; ++i) pos[sa[i]] = i;
    for (int i = 0; i < n; ++i) {
      if (pos[i]+1<n) {
        int j = sa[pos[i]+1];  
        while (i+k<n&&j+k<n&&a[i+k]==a[j+k])k++;
        lcp[pos[i]]=k;
      }
      if (k) {
        k--;
      }
    }
    t.build(lcp);
  }
  int getLcp(int i, int j) {
    i = pos[i]; j = pos[j];
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
//6327c9
