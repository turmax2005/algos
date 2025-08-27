//n - number of vertices, m - number of edges, parallel edges -- ???, color of any edge is the color of its lower end
vector <vector <int> > dfstree(n);
vector <int> used(n), cut(n), h(n), up(n);
auto findCutPoints = [&] (auto self, int u) -> void {
    used[u] = 1;
    up[u] = h[u];
    for (int v : g[u]) {
        if (!used[v]) {
            dfstree[u].push_back(v);
            h[v] = h[u] + 1;
            self(self, v);
            up[u] = min(up[u], up[v]);
            if (up[v] >= h[u]) {
                cut[v] = 1;
            }
        }
        else {
            up[u] = min(up[u], h[v]);
        }
    }
};
findCutPoints(findCutPoints, 0);
vector <vector <int> > tree(n + m);
vector<int> color(n);color[0]=0;int ptr=n;
auto build = [&] (auto self, int u) -> void {
    for (int v : dfstree[u]) {
        if (cut[v]) {
            color[v]=ptr;++ptr;
            self(self, v);
        }
        else {
            color[v]=color[u];
            self(self, v);
        }
    }
};
build(build, 0);
for(int i=0;i<n;++i) {
    set<int> to;
    for(int j:g[i]) {
        int x=i,y=j;
        if(h[x]<h[y]) swap(x,y);
        to.insert(color[x]);
    }
    for(int j:to) {
        tree[i].app(j);tree[j].app(i);
    }
}
//2ebfbb
