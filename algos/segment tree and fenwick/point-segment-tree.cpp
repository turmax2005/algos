template<typename T, typename U>
struct SegmentTree {
    int n;
    T neutral;
    U unite;
    vector<T> data;
 
    template<typename I>
    SegmentTree(int n, T neutral, U unite, I init) : n(n), neutral(neutral), unite(unite), data(2 * n) {
        for (int i = 0; i < n; ++i) data[i + n] = init(i);
        for (int i = n - 1; i > 0; --i) data[i] = unite(data[2 * i], data[2 * i + 1]);
    }
 
    SegmentTree(int n, T neutral, U unite) : n(n), neutral(neutral), unite(unite), data(2 * n, neutral) {}
 
    void set(int i, T x) {
        data[i += n] = x;
        for (i /= 2; i > 0; i /= 2) data[i] = unite(data[2 * i], data[2 * i + 1]);
    }
 
    T get(int l, int r) {
        T leftRes = neutral, rightRes = neutral;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l & 1) leftRes = unite(leftRes, data[l++]);
            if (r & 1) rightRes = unite(data[--r], rightRes);
        }
        return unite(leftRes, rightRes);
    }
};

void example () {
  // max
  SegmentTree segtree(n, -(long long)1e18,  [](int x, int y) { return max(x, y); });

  // sum
  MassSegmentTree segtree(n, 0LL,  [](int x, int y) { return x + y; });
}
