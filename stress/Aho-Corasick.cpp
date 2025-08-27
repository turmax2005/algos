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

struct node{
    node *next[26] = {}, *link[26] = {};
    node *suf = nullptr;
    vector<int> term;
    int visited = 0;
    node() {}
    node *get_next(char c) {
        if (next[c - 'a'] == nullptr) next[c - 'a'] = new node();
        return next[c - 'a'];
    }
};

void solve() {
    const int N = 100, L1 = 20, L2 = 10000;
    while (true) {
        int n = rng() % N + 1;
        vector<string> s(n);
        for (auto &s : s) {
            s.resize(rng() % L1 + 1, 'a');
            for (auto &c : s) c = "ab"[rng() % 2];
        }
        string t(rng() % L2 + 1, 'a');
        for (auto &c : t) c = "ab"[rng() % 2];
        vector<int> count(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j + s[i].size() <= t.size(); ++j) {
                if (t.substr(j, s[i].size()) == s[i]) count[i]++;
            }
        }

        node *root = new node();
        for (int i = 0; i < s.size(); ++i) {
            node *cur = root;
            for (char c : s[i]) cur = cur->get_next(c);
            cur->term.push_back(i);
        }
        vector<node *> bfs_order;
        queue<node *> bfs;
        root->suf = root;
        for (char c = 'a'; c <= 'z'; ++c) root->link[c - 'a'] = (root->next[c - 'a'] ? root->next[c - 'a'] : root);
        bfs.push(root);
        while (!bfs.empty()) {
            node *cur = bfs.front();
            bfs_order.push_back(cur);
            bfs.pop();
            for (char c = 'a';  c <= 'z'; ++c) {
                node *nxt = cur->next[c - 'a'];
                if (!nxt) continue;
                nxt->suf = (cur == root ? cur : cur->suf->link[c - 'a']);
                for (char c = 'a'; c <= 'z'; ++c) nxt->link[c - 'a'] = (nxt->next[c - 'a'] ? nxt->next[c - 'a'] : nxt->suf->link[c - 'a']);
                bfs.push(nxt);
            }
        }
        node *cur = root;
        for (char c : t) {
            cur = cur->link[c - 'a'];
            cur->visited++;
        }
        vector<int> count2(n);
        for (int i = bfs_order.size() - 1; i >= 0; --i) {
            node *cur = bfs_order[i];
            for (int idx : cur->term) count2[idx] = cur->visited;
            cur->suf->visited += cur->visited;
        }
        assert(count == count2);
        cout << "test passed" << endl;
        for (int x : count) cout << x << ' ';
        cout << endl;
    }
}
//eba8e2
