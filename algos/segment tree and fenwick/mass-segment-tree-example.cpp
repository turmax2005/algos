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
