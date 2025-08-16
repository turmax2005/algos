template<typename Check>
vector<point> intersect(vector<point> h, Check value) {
  int n = h.size();
  vector<int> pos(n);
  for (int i = 0; i < n; ++i) {
    pos[i] = value(h[i]) >= 0;
  }
  if (count(all(pos), 0) == 0) return h;
  if (count(all(pos), 1) == 0) return {};
  auto intersect = [&](point p, point q) {
    auto s = value(p);
    auto t = value(q);
    assert(s < 0 && t >= 0);
    return q + (p - q) * (t / (t - s));
  };
  int t01 = -1, t10 = -1;

  for (int i = 0; i < n; ++i) {
    h.push_back(h[i]);
    pos.push_back(pos[i]);
    if (pos[i] == 0 && pos[i + 1] == 1) t01 = i;
    if (pos[i] == 1 && pos[i + 1] == 0) t10 = i;
  }
  if (t10 < t01) t10 += n;
//for (int i = t01 + 1; i <= t10; ++i) assert(pos[i] == 1);
//for (int i = t10 + 1; i <= t01 + n; ++i) assert(pos[i] == 0);
  vector<point> res{intersect(h[t01], h[t01 + 1])};
  for (int i = t01 + 1; i <= t10; ++i) {
    res.push_back(h[i]);
  }
  res.push_back(intersect(h[t10 + 1], h[t10]));
  return res;
}

// Usage example:
void solve() {
    vector<point> p, q;
    // ... q must be in counterclockwise order; q[0] == q[m]
    for (int i = 0; i < m; ++i) {
        p = intersect(p, [&](point pt) { return cross(q[i + 1] - q[i], pt - q[i]); });
    }
}