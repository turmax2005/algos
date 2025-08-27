struct Line{
  int a, b;
  Line(){}
  Line (int a, int b) : a(a), b(b) {}
  int get(int x) { return a + b * x;}
};

struct Lichao {
  int n;
  vector <int> x;
  vector <Line> t;
  Lichao(){}
  Lichao (int n, vector<int> x) : n(n), t(n << 2, Line(inf, 0)), x(x) {}

  void put(int v, int l, int r, Line L) {
    if (l + 1 == r) {
      if (L.get(x[l]) < t[v].get(x[l])) {
        t[v] = L;
      }
      return;
    }
    int m = (l + r) / 2;
    if (L.get(x[m]) < t[v].get(x[m])) {
      swap(L, t[v]);
    }
    if (L.b > t[v].b) {
      put(2 * v + 1, l, m, L);
    }
    else {
      put(2 * v + 2, m, r, L);
    }
  }

  int get(int v, int l, int r, int i) {
    if (l + 1 == r) {
      return t[v].get(x[l]);
    }
    int m = (l + r) / 2;
    int ans = t[v].get(x[i]);
    if (i < m) {
      ans = min(ans, get(2 * v + 1, l, m, i));
    } else {
      ans = min(ans, get(2 * v + 2, m, r, i));}
    return ans;
  }

  void put(Line L) {
    put(0, 0, n, L);
  }

  int get(int i) {
    return get(0, 0, n, i);
  }
};

//99f5fa
