ll div_up(ll a, ll b) { return a/b+((a^b)>0&&a%b); } // divide a by b rounded up

struct Line {
    ll k, b;

    Line() : k(), b() {}
    Line (ll _k, ll _b) : k(_k), b(_b) {}

    ll getVal(ll x) {
        return k * x + b;
    }
};
struct Hull {
    vector<Line> lines;
    vector<ll> borders;

    Hull() : lines(), borders() {}

    void addLine(Line L) {
        while(!lines.empty()) {
            if (lines.back().getVal(borders.back()) >= L.getVal(borders.back())) {
                lines.pop_back();
                borders.pop_back();
            } else break;
        }
        if (lines.empty()) {
            lines.push_back(L);
            borders.push_back(0LL); //leftmost query
            return;
        }
        if (lines.back().k <= L.k) return;
        ll x = div_up(L.b - lines.back().b, lines.back().k - L.k); //must work for negative!
        lines.push_back(L);
        borders.push_back(x);
    }
    ll getMinVal(ll x) {
        int pos = upper_bound(borders.begin(), borders.end(), x) - borders.begin();
        if (pos == 0) throw;
        pos--;
        return lines[pos].getVal(x);
    }
};