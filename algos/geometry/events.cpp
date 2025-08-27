int cross(point p, point q) { return p.x * q.y - q.x * p.y; }
point operator-(point p, point q) { return {p.x - q.x, p.y - q.y}; }
int sgn(int x) { return x < 0 ? -1 : (x > 0); }
double dist(point p) { return sqrt(p.x * p.x + p.y * p.y); }
const __int128 one = 1;

double solve(vector<point> a, point p, point q) {
  int n = a.size();
  a.push_back(a[0]);
  point pq = q - p;
  vector<array<int, 3>> ev;
  for (int i = 0; i < n; ++i) {
    point u = a[i], v = a[i + 1];
    int s = sgn(cross(u - p, pq)), t = sgn(cross(v - p, pq));
    if (s == t) continue;
    int top = cross(u - p, v - u), bot = cross(pq, v - u);
    ev.push_back({sgn(bot) * top, abs(bot), t - s});
  }
  sort(all(ev), [](auto e, auto f) {
    return e[0] * one * f[1] < f[0] * one * e[1];
  });
  int bal = 0;
  for (int i = 0; i + 1 < ev.size(); ++i) {
    if (bal + ev[i][2] < 0 || bal + ev[i][2] > 2) {
      assert(ev[i][0] * ev[i+1][1] == ev[i+1][0] * ev[i][1]);
      swap(ev[i], ev[i + 1]);
    }
    bal += ev[i][2];
  }
  // example usage: now calculating length of longest segment inside
  bal = 0;
  double from = 0, ans = 0;
  for (auto [t, b, w] : ev) {
    double x = t * 1.0 / b;
    if (bal == 0) from = x;
    bal += w;
    assert(0 <= bal && bal <= 2);
    if (bal == 0) ans = max(ans, x - from);
  }
  return ans * dist(pq);
}
//fe0649
