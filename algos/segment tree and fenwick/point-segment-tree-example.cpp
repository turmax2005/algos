void example () {
  // max
  SegmentTree segtree(n, -(int)1e18,  [](int x, int y) { return max(x, y); });

  // sum
  SegmentTree ones(n, 0LL,  [](int x, int y) { return x + y; });

  auto left_zero = [&](int r) { // nearest zero strictly to the left
    return ones.firstTrue(r, [r](int sum, int l){ return r - l == sum; }) - 1;
  };
  auto right_zero = [&](int l) { // nearest zero strictly to the right
    return ones.lastTrue(l + 1, [l](int sum, int r){ return r - (l + 1) == sum; });
  };
}

