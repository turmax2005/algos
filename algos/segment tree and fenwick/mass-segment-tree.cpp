#ifdef LOCAL
int __lg(int x) { return 63 - __builtin_clzll(x); }
#endif

template<typename Data, typename Mod, typename UniteData, typename UniteMod, typename Apply>
struct MassSegmentTree {
  int h, n;
  Data zd;
  Mod zm;
  vector<Data> data;
  vector<Mod> mod;

  UniteData ud; // Data (Data, Data)
  UniteMod um; // Mod (Mod, Mod);
  Apply a; // Data (Data, Mod, int); last argument is the length of current segment (could be used for range += and sum counting, for instance)

  template<typename I>
  MassSegmentTree(int sz, Data zd, Mod zm, UniteData ud, UniteMod um, Apply a, I init) : h(__lg(sz > 1 ? sz - 1 : 1) + 1), n(1 << h), zm(zm), zd(zd), data(2 * n, zd), mod(n, zm), ud(ud), um(um), a(a) {
    for (int i = 0; i < sz; ++i) data[i + n] = init(i);
    for (int i = n - 1; i > 0; --i) data[i] = ud(data[2 * i], data[2 * i + 1]);
  }

  MassSegmentTree(int sz, Data zd, Mod zm, UniteData ud, UniteMod um, Apply a) : h(__lg(sz > 1 ? sz - 1 : 1) + 1), n(1 << h), zm(zm), zd(zd), data(2 * n, zd), mod(n, zm), ud(ud), um(um), a(a) {}

  void push(int i) {
    if (mod[i] == zm) return;
    apply(2 * i, mod[i]);
    apply(2 * i + 1, mod[i]);
    mod[i] = zm;
  }

  // is used only for apply
  int length(int i) { return 1 << (h - __lg(i)); }

  // used only for descent
  int left(int i) {
    int lvl = __lg(i);
    return (i & ((1 << lvl) - 1)) * (1 << (h - lvl));
  }

  // used only for descent
  int right(int i) {
    int lvl = __lg(i);
    return ((i & ((1 << lvl) - 1)) + 1) * (1 << (h - lvl));
  }

  template<typename S>
  void apply(int i, S x) {
    data[i] = a(data[i], x, length(i));
    if (i < n) mod[i] = um(mod[i], x);
  }

  void update(int i) {
    if (mod[i] != zm) return;
    data[i] = ud(data[2 * i], data[2 * i + 1]);
  }

  template<typename S>
  void update(int l, int r, S x) { // [l; r)
    l += n, r += n;
    for (int shift = h; shift > 0; --shift) {
      push(l >> shift);
      push((r - 1) >> shift);
    }
    for (int lf = l, rg = r; lf < rg; lf /= 2, rg /= 2) {
      if (lf & 1) apply(lf++, x);
      if (rg & 1) apply(--rg, x);
    }
    for (int shift = 1; shift <= h; ++shift) {
      update(l >> shift);
      update((r - 1) >> shift);
    }
  }

  Data get(int l, int r) { // [l; r)
    l += n, r += n;
    for (int shift = h; shift > 0; --shift) {
      push(l >> shift);
      push((r - 1) >> shift);
    }
    Data leftRes = zd, rightRes = zd;
    for (; l < r; l /= 2, r /= 2) {
      if (l & 1) leftRes = ud(leftRes, data[l++]);
      if (r & 1) rightRes = ud(data[--r], rightRes);
    }
    return ud(leftRes, rightRes);
  }

  // l \in [0; n) && ok(get(l, l), l);
  // returns last r: ok(get(l, r), r)
  template<typename C>
  int lastTrue(int l, C ok) {
    l += n;
    for (int shift = h; shift > 0; --shift) push(l >> shift);
    Data cur = zd;
    do {
      l >>= __builtin_ctz(l);
      Data with1;
      with1 = ud(cur, data[l]);
      if (ok(with1, right(l))) {
        cur = with1;
        ++l;
      } else {
        while (l < n) {
          push(l);
          Data with2;
          with2 = ud(cur, data[2 * l]);
          if (ok(with2, right(2 * l))) {
            cur = with2;
            l = 2 * l + 1;
          } else {
            l = 2 * l;
          }
        }
        return l - n;
      }
    } while (l & (l - 1));
    return n;
  }

  // r \in [0; n) && ok(get(r, r), r);
  // returns first l: ok(get(l, r), l)
  template<typename C>
  int firstTrue(int r, C ok) {
    r += n;
    for (int shift = h; shift > 0; --shift) push((r - 1) >> shift);
    Data cur = zd;
    while (r & (r - 1)) {
      r >>= __builtin_ctz(r);
      Data with1;
      with1 = ud(data[--r], cur);
      if (ok(with1, left(r))) {
        cur = with1;
      } else {
        while (r < n) {
          push(r);
          Data with2;
          with2 = ud(data[2 * r + 1], cur);
          if (ok(with2, left(2 * r + 1))) {
            cur = with2;
            r = 2 * r;
          } else {
            r = 2 * r + 1;
          }
        }
        return r - n + 1;
      }
    }
    return 0;
  }
};

void example () {
  // max and +=
  MassSegmentTree segtree(n, 0LL, 0LL,
  [](int x, int y) { return max(x, y); },
  [](int x, int y) { return x + y; },
  [](int x, int y, int len) { return x + y; });

  // sum and +=
  MassSegmentTree segtree(n, 0LL, 0LL,
  [](int x, int y) { return x + y; },
  [](int x, int y) { return x + y; },
  [](int x, int y, int len) { return x + y * len; });

  // sum and assignment
  MassSegmentTree segtree(n, 0LL, -1LL,
  [](int x, int y) { return x + y; },
  [](int x, int y) { return y; },
  [](int x, int y, int len) { return y * len; });
}
