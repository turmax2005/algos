struct LCAandHLD {
    int n;vector<vector<int> > g;vector<vector<int32_t> > u; ///u is binups
    vector<int> tin;vector<int> tout;int timer;vector<bool> used;vector<int> sub;vector<int> top;int lg;vector<int> corn;vector<int> tin_inverse;
    void dfs0(int x) {
        used[x]=true;
        sub[x]=1;
        for(int v:g[x]) {
            if(!used[v]) {
                corn[v]=corn[x]+1;
                dfs0(v);
                sub[x]+=sub[v];
            }
        }
        used[x]=false;
    };
    void dfs(int x) {
        tin[x]=timer;++timer;used[x]=true;
        for(int i=1;i<lg;++i) {
            u[x][i]=u[u[x][i-1]][i-1];
        }
        vector<int> ch;for(int v:g[x]) if(!used[v]) ch.app(v);
        sort(all(ch),[&](int x,int y) {return sub[x]>sub[y];});
        if(!ch.empty()) {
            top[ch[0]]=top[x];
            for(int i=1;i<ch.size();++i) {
                top[ch[i]]=ch[i];
            }
        }
        for(int v:ch) {
            u[v][0]=x;
            dfs(v);
        }
        tout[x]=timer;used[x]=false;
    };
    LCAandHLD(int n,vector<vector<int> > g) {
        this->n=n;this->g=g;lg=1;while((1<<lg)<n) ++lg;
        u.resize(n);used.resize(n);tin.resize(n);tout.resize(n);sub.resize(n);top.resize(n);corn.resize(n);tin_inverse.resize(n);
        for(int i=0;i<n;++i) u[i].resize(lg);
        timer=0;dfs0(0);dfs(0);
        for(int i=0;i<n;++i) tin_inverse[tin[i]]=i;
    };
    bool pred(int x,int y) {
        return (tin[x]<=tin[y] && tout[x]>=tout[y]);
    };
    int lca(int x,int y) {
        if(pred(x,y)) return x;
        for(int i=lg-1;i>=0;--i) {
            int x1=u[x][i];
            if(!pred(x1,y)) x=x1;
        }
        return u[x][0];
    };
    vector<pair<int,int> > verticalpath(int x,int px,bool includelast) {
        vector<pair<int,int> > res;
        while(true) {
            if(x==px && !includelast) {
                break;
            }
            if(top[x]==px) {
                if(includelast) {
                    res.app({tin[px],tin[x]});
                }
                else {
                    res.app({tin[px]+1,tin[x]});
                }
                break;
            }
            if(pred(px,top[x])) {
                res.app({tin[top[x]],tin[x]});
                x=u[top[x]][0];
            }
            else {
                if(includelast) {
                    res.app({tin[px],tin[x]});
                }
                else {
                    res.app({tin[px]+1,tin[x]});
                }
                break;
            }
        }
        return res;
    };
    vector<pair<int,int> > vpath(int x,int y) { ///vertices on path between x and y
        int o=lca(x,y);
        vector<pair<int,int> > v1=verticalpath(x,o,true);
        vector<pair<int,int> > v2=verticalpath(y,o,false);
        for(auto h:v2) {
            v1.app(h);
        }
        return v1;
    };
    vector<pair<int,int> > epath(int x,int y) { ///path between x and y without lca (edge path)
        int o=lca(x,y);
        vector<pair<int,int> > v1=verticalpath(x,o,false);
        vector<pair<int,int> > v2=verticalpath(y,o,false);
        for(auto h:v2) {
            v1.app(h);
        }
        return v1;
    };
};
