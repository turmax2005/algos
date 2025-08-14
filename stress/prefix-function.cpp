#include <bits/stdc++.h>

#define int long long

using namespace std;
using ll = long long;

void solve();

template<typename ...Args>
void println(Args... args) {
    apply([](auto &&... args) { ((cout << args << ' '), ...); }, tuple(args...));
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

mt19937 rng(0);
vector<int> prefix_function(string s) {
    vector<int> p(s.size());
    for (int i = 1; i < s.size(); ++i) {
        p[i] = p[i - 1];
        while (p[i] && s[p[i]] != s[i]) p[i] = p[p[i] - 1];
        p[i] += s[i] == s[p[i]];
    }
    return p;
}

void solve() {
    while (true) {
        int n = rng() % 20 + 1;
        string s(n, 'a');
        for (char &c : s) c = "abcd"[rng() % 4];
        vector<int> p(n);
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j <= i; ++j) if (s.substr(0, j) == s.substr(i - j + 1, j)) p[i] = j;
        }
        assert(p == prefix_function(s));
        cout << "test passed" << endl;
    }
}

