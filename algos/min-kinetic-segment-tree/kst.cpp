using lint = long long;
const lint inf = 4e18;
const int MAXT = 4100000;
using pi = array<lint, 2>;

struct line {
    lint A, B;
    int idx;
 
    lint eval(lint x) { return A * x + B; }
 
    // returns the x-intercept of intersection "strictly" larger than T
    lint cross_after(line &x, lint T) {
        if (x.A == A) {
            return inf;
        }
        lint up = x.B - B;
        lint dn = A - x.A;
        if (dn < 0) {
            dn *= -1;
            up *= -1;
        }
        lint incep = (up <= 0 ? -((-up) / dn) : (up + dn - 1) / dn);
        if (incep > T)
            return incep;
        return inf;
    }
};
 
struct kst { // min kinetic segment tree
    line tree[MAXT];
    lint melt[MAXT], T;
    pi lazy[MAXT];
    int n;
 
    bool cmp(line &a, line &b) {
        lint l = a.eval(T), r = b.eval(T);
        if (l != r)
            return l > r;
        return a.A > b.A;
    }
 
    void pull(int p) {
        tree[p] = cmp(tree[2 * p], tree[2 * p + 1]) ? tree[2 * p + 1] : tree[2 * p];
        melt[p] = min({melt[2 * p], melt[2 * p + 1], tree[2 * p].cross_after(tree[2 * p + 1], 0)});
    }
 
    void init(int s, int e, int p, vector<line> &l) {
        if (s == e) {
            tree[p] = l[s];
            melt[p] = inf;
            lazy[p] = {0, 0};
            return;
        }
        lazy[p] = {0, 0};
        int m = (s + e) / 2;
        init(s, m, 2 * p, l);
        init(m + 1, e, 2 * p + 1, l);
        pull(p);
    }
 
    void lazydown(int p) {
        for (int i = 2 * p; i < 2 * p + 2; i++) {
            lazy[i][0] += lazy[p][0];
            lazy[i][1] += lazy[p][1];
            tree[i].B += lazy[p][0] * tree[i].A + lazy[p][1];
            melt[i] -= lazy[p][0];
        }
        lazy[p][0] = lazy[p][1] = 0;
    }
 
    void propagate(int p) {
        if (melt[p] > 0)
            return;
        lazydown(p);
        propagate(2 * p);
        propagate(2 * p + 1);
        pull(p);
    }
 
    lint query(int s, int e, int ps, int pe, int p = 1) {
        if (e < ps || pe < s)
            return inf;
        if (s <= ps && pe <= e)
            return tree[p].eval(0);
        int pm = (ps + pe) / 2;
        lazydown(p);
        return min(query(s, e, ps, pm, 2 * p), query(s, e, pm + 1, pe, 2 * p + 1));
    }
 
    void heaten(int s, int e, int ps, int pe, int p, lint v) {
        if (e < ps || pe < s)
            return;
        if (s <= ps && pe <= e) {
            lazy[p][0] += v;
            tree[p].B += v * tree[p].A;
            melt[p] -= v;
            propagate(p);
            return;
        }
        lazydown(p);
        int pm = (ps + pe) / 2;
        heaten(s, e, ps, pm, 2 * p, v);
        heaten(s, e, pm + 1, pe, 2 * p + 1, v);
        pull(p);
    }
 
    void add(int s, int e, int ps, int pe, int p, lint v) {
        if (e < ps || pe < s)
            return;
        if (s <= ps && pe <= e) {
            lazy[p][1] += v;
            tree[p].B += v;
            return;
        }
        lazydown(p);
        int pm = (ps + pe) / 2;
        add(s, e, ps, pm, 2 * p, v);
        add(s, e, pm + 1, pe, 2 * p + 1, v);
        pull(p);
    }
 
    void init(vector<line> &l, lint _T) {
        n = l.size();
        T = _T;
        init(0, n - 1, 1, l);
    }
};