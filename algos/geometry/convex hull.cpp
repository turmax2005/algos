using pt = pair<int, int>;
#define x first
#define y second

int cross(pt p, pt q) { return p.x * q.y - p.y * q.x; }
pt operator-(pt a, pt b) { return {a.x - b.x, a.y - b.y}; }

vector<point> convex(vector<point> a) {
    sort(all(a));
    a.erase(unique(all(a)), a.end());
    vector<point> h;
    for (int t = 0; t < 2; ++t) {
        int sz = h.size() - t;
        for (auto p: a) {
            while (h.size() >= sz + 2 && cross(p - h.end()[-1], h.end()[-2] - h.end()[-1]) <= 0) h.pop_back();
            h.push_back(p);
        }
        reverse(all(a));
    }
    return h; // h is circular: h.empty() || h.front() == h.back()
}


