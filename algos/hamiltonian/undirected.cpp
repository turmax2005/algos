#include <bits/stdc++.h>
using namespace std;
namespace hamil {
    template <typename T> bool chkmax(T &x,T y){return x<y?x=y,true:false;}
    template <typename T> bool chkmin(T &x,T y){return x>y?x=y,true:false;}
    #define vi vector<int>
    #define pb push_back
    #define mp make_pair
    #define pi pair<int, int>
    #define fi first
    #define se second
    #define ll long long
    using namespace LCT;
    vector<vi> used;
    unordered_set<int> caneg;
    void cut(int a, int b) {
    	LCT::cut(a, b);
    	for (int s = 0; s < 2; s++) {
	    	for (int i = 0; i < used[a].size(); i++)
	    		if (used[a][i] == b) {
	    			used[a].erase(used[a].begin() + i);
	    			break;
				}
			if (used[a].size() == 1) caneg.insert(a);
			swap(a, b);
		}
	}
	void link(int a, int b) {
		LCT::link(a, b);
		for (int s = 0; s < 2; s++) {
			used[a].pb(b);
			if (used[a].size() == 2) caneg.erase(a);
			swap(a, b);
		}
	}
    vi work(int n, vector<pi> eg, ll mx_ch = -1) {
        // mx_ch : max number of adding/replacing  default is (n + 100) * (n + 50)
        // n : number of vertices. 1-indexed.
        // eg: vector<pair<int, int> > storing all the edges.
        // return a vector<int> consists of all indices of vertices on the path. return empty list if failed to find one.

        LCT::init(n);
        if (mx_ch == -1) mx_ch = 1ll * (n + 100) * (n + 50); //default
        used.resize(n + 1);
        caneg.clear();
        for (int i = 1; i <= n; i++) used[i].clear();

        vector<vi> edges(n + 1);
        for (auto v : eg)
            edges[v.fi].pb(v.se),
            edges[v.se].pb(v.fi);

        for (int i = 1; i <= n; i++)
            caneg.insert(i);

        mt19937 x(chrono::steady_clock::now().time_since_epoch().count());
        int tot = 0;
        while (mx_ch >= 0) {
        //    cout << tot << ' ' << mx_ch << endl;
            vector<pi> eg;
            for (auto v : caneg)
                for (auto s : edges[v])
                    eg.pb(mp(v, s));

            shuffle(eg.begin(), eg.end(), x);
            if (eg.size() == 0) break;
            for (auto v : eg) {
                mx_ch--;
                int a = v.fi, b = v.se;
                if (used[a].size() < used[b].size()) swap(a, b);
                if (used[b].size() >= 2) continue;
                if (x() & 1) continue;
                if (LCT::fdr(a) == LCT::fdr(b)) continue;
                if (used[a].size() < 2 && used[b].size() < 2)
                	tot++;
                if (used[a].size() == 2) {
                	int p = used[a][x() % 2];
                	cut(a, p);
                }
                link(a, b);
            }
            if (tot == n - 1) {
                vi cur;
                for (int i = 1; i <= n; i++)
                    if (used[i].size() <= 1) {
                        int pl = i, ls = 0;
                        while (pl) {
                            cur.pb(pl);
                            int flag = 0;
                            for (auto v : used[pl])
                            	if (v != ls) {
                            		ls = pl;
                            		pl = v;
                            		flag = 1;
                            		break;
								}
							if (!flag) break;
                        }
                        break;
                    }
                return cur;
            }
        }
        //failed to find a path
        return vi();
    }
}