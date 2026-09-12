vector<pair<int,int> > kuhn(int n1,int n2,vector<pair<int,int> > edges) { ///(i,j) in edges, 0<=i<n1 , 0<=j<n2
    vector<vector<int> > g(n1);
    for(auto [x,y]:edges) {
        g[x].app(y);
    }
    vector<bool> par(n1);vector<int> mt(n2,-1);vector<bool> used(n1);
    function<bool(int)> dfs=[&](int x) {
        used[x]=true;
        for(int v:g[x]) {
            if(mt[v]==(-1) || (!used[mt[v]] && dfs(mt[v]))) {
                mt[v]=x;
                return true;
            }
        }
        return false;
    };
    while(true) {
        fill(all(used),false);
        bool ok=false;
        for(int i=0;i<n1;++i) {
            if(!par[i]) {
                if(dfs(i)) {
                    par[i]=true;
                    ok=true;
                }
            }
        }
        if(!ok) break;
    }
    vector<pair<int,int> > res;
    for(int i=0;i<n2;++i) {
        if(mt[i]!=(-1)) {
            res.app({mt[i],i});
        }
    }
    return res;
}
