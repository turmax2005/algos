#define PROBLEM "https://judge.yosupo.jp/problem/scc"

#include <bits/stdc++.h>

#define int long long

using namespace std;
using ll = long long;

void solve();

template<typename ...Args>
void println(Args... args) {
    apply([](auto &&... args) { ((cout << args), ...); }, tuple(args...));
    cout << '\n';
}

int32_t main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int t = 1;
//    cin >> t;
    for (int tc = 0; tc < t; ++tc) {
        solve();
    }
    return 0;
}

#define all(x) x.begin(), x.end()

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }
    vector<vector<int>> r(g.size());
    for (int i = 0; i < g.size(); ++i) {
        for (int j : g[i]) r[j].push_back(i);
    }
    vector<int> used(g.size()), tout(g.size());
    int time = 0;
    auto dfs = [&](auto dfs, int cur) -> void {
        if (used[cur]) return;
        used[cur] = 1;
        for (int nxt : g[cur]) {
            dfs(dfs, nxt);
        }
        // used[cur] = 2;
        tout[cur] = time++;
    };
    for (int i = 0; i < g.size(); ++i) if (!used[i]) dfs(dfs, i);
    vector<int> ind(g.size());
    iota(ind.begin(), ind.end(), 0);
    sort(all(ind), [&](int i, int j){return tout[i] > tout[j];});
    vector<int> scc(g.size(), -1);
    auto go = [&](auto go, int cur, int color) -> void {
        if (scc[cur] != -1) return;
        scc[cur] = color;
        for (int nxt : r[cur]) {
            go(go, nxt, color);
        }
    };
    int color = 0;
    for (int i : ind) {
        if (scc[i] == -1) go(go, i, color++);
    }
    vector<vector<int>> where(color);
    for (int x = 0; x < n; ++x) where[scc[x]].push_back(x);
    cout << color << '\n';
    for (int i = 0; i < color; ++i) {
        cout << where[i].size();
        for (int x : where[i]) cout << ' ' << x;
        cout << '\n';
    }
}

