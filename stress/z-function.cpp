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
vector<int> z_function (string s) { // z[i] - lcp of s and s[i:]
    int n = (int) s.length();
    vector<int> z (n);
    for (int i=1, l=0, r=0; i<n; ++i) {
        if (i <= r)
            z[i] = min (r-i+1, z[i-l]);
        while (i+z[i] < n && s[z[i]] == s[i+z[i]])
            ++z[i];
        if (i+z[i]-1 > r)
            l = i,  r = i+z[i]-1;
    }
    return z;
}

void solve() {
    while (true) {
        int n = rng() % 20 + 1;
        string s(n, 'a');
        for (char &c : s) c = "abcd"[rng() % 4];
        vector<int> p(n);
        for (int i = 1; i < n; ++i) {
            while (i + p[i] < n && s[p[i]] == s[i + p[i]]) {
                p[i]++;
            }
        }
        assert(p == z_function(s));
        cout << "test passed" << endl;
    }
}

