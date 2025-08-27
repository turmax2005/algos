const int logn = 30; // any number, such that maxn is greater than coordinates. 20 is ok.
const int maxn = 1 << logn;
int hilbertorder(int x, int y) { // returns long long
    int d = 0; // long long
    for (int s = 1 << (logn - 1); s; s >>= 1)
    {
        bool rx = x & s, ry = y & s;
        d = (4 * d) | ((3 * rx) ^ ry);
        if (!ry) {
            if (rx) {
                x = maxn - x;
                y = maxn - y;
            }
            swap(x, y);
        }
    }
    return d;
}
// Usage example:
vector<int> sort_indices(int q, vector<pair<int, int>> &qs) {
    vector<int> ind(q), ord(q);
    iota(all(ind), 0);
    for (int i = 0; i < q; ++i) ord[i] = hilbertorder(qs[i].first, qs[i].second);
    sort(all(ind), [&](int i, int j) { return ord[i] < ord[j]; });
    return ind;
}
//134578
