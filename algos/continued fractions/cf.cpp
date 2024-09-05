int floor(int a, int b) {
    return a / b - ((a ^ b) < 0 && a % b);
}
vector<int> decompose(int p, int q) {
    vector<int> f;
    while (q != 0) {
        f.push_back(floor(p, q));
        p -= q * f.back();
        swap(p, q);
    }
    return f;
}

using matrix = array<int, 4>;

matrix operator*(matrix a, matrix b) {
    matrix c{0,0,0,0};
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                c[2 * i + k] += a[2 * i + j] * b[2 * j + k];
            }
        }
    }
    return c;
}

#define x first
#define y second

// computes lower convex hull for 0 <= x <= N, 0 <= y <= (ax + b) / c
vector<pair<int, int>> lower_convex_hull(int a, int b, int c, int n) {
    matrix m = {1, 0, 0, 1};
    auto f = decompose(a, c);
    vector<pair<int, int>> conv{{1, 0}, {0, 1}};
    for (int x : f) {
        m = m * matrix{x, 1, 1, 0};
        conv.emplace_back(m[2], m[0]);
        if (m[2] > n) break; // there should be one (if any) with .x > n
    }
    auto diff = [&](int x, int y) {
        return c * y - a * x;
    };
    int x = 0, y = b / c;
    vector<pair<int, int>> res{{x, y}};
    int i;
    for (i = 2; i + 1 < conv.size(); i += 2) {
        while (diff(x + conv[i + 1].x, y + conv[i + 1].y) <= b) {
            int t = 1 + (diff(x + conv[i - 1].x, y + conv[i - 1].y) - b - 1) / abs(diff(conv[i].x, conv[i].y));
            auto [dx, dy] = tuple{conv[i - 1].x + t * conv[i].x, conv[i - 1].y + t * conv[i].y};
            int k = (n - x) / dx;
            if (k == 0) break;
            if (diff(dx, dy)) k = min(k, (b - diff(x, y)) / diff(dx, dy));
            x += k * dx, y += k * dy;
            res.push_back({x, y});
        }
    }
    if (i >= conv.size()) i -= 2;
    for (; i > 0; i -= 2) {
        auto [dx1, dy1] = conv[i];
        if (x + dx1 > n) continue;
        x += dx1, y += dy1;
        if (i + 1 < conv.size()) {
            auto [dx2, dy2] = conv[i + 1];
            int k = (n - x) / dx2;
            x += k * dx2;
            y += k * dy2;
        }
        res.emplace_back(x, y);
        int k = (n - x) / dx1;
        if (k == 0) continue;
        x += k * dx1;
        y += k * dy1;
        res.emplace_back(x, y);
    }
    return res;
}

// number of (x, y) under pq line such that p.x <= x < q.x && 0 < y
int area(auto p, auto q) {
    int integers = gcd(q.x - p.x, q.y - p.y);
    return ((p.y + q.y - 1) * (q.x - p.x + 1) + integers + 1) / 2 - q.y;
}

// sum of (ax + b) / c for 0 <= x < n
int get_area(int a, int b, int c, int n) { // SUM (ax + b) / c for 0 <= x < n
    auto ch = lower_convex_hull(a, b, c, n);
    int sum = 0;
    for (int i = 0; i + 1 < ch.size(); ++i) {
        sum += area(ch[i], ch[i + 1]);
        assert(ch[i] != ch[i + 1]);
    }
    return sum;
}

// min of (ax + b) % c for 0 <= x < n
int get_min(int a, int b, int c, int n) {
    auto ch = lower_convex_hull(a, b, c, n - 1);
    // in fact, here we need only the last point of the first half of the algo (that is going up)
    int mn = c;
    for (auto [x, y] : ch) mn = min(mn, (a * x + b) % c);
    return mn;
}