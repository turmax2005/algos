const int INF = 1e9;
/// https://codeforces.com/blog/entry/158509
struct BottleneckTree {
  vector<int> link, cost;   // all inserted costs must be < INF
  BottleneckTree(int n) : link(n, 0), cost(n, INF) {
    link[0] = -1; cost[0] = INF + 1;
  }
  void rot(int x) {
    int p = link[x], g = link[p];
    swap(cost[x], cost[p]);
    link[x] = g, link[p] = x;
  }
  void skip(int x) { link[x] = link[link[x]]; }
  void access(int x) {
    for (int p = link[x]; p != -1; p = link[x]) {
      int g = link[p];
      if (cost[x] <= cost[p]) rot(x);                  // (A)
      else if (cost[p] > cost[g]) skip(p), skip(x);    // (B)
      else if (cost[g] <= cost[x]) rot(p), skip(x);    // (C)
      else skip(x);                                    // (D)
    }
  }
  int Query(int x, int y) {      // x != y; INF if disconnected
    access(x); access(y);
    return cost[x];
  }
  int AddEdge(int x, int y, int c) {   // x != y
    access(x); access(y);
    if (cost[x] > c) swap(cost[x], c);
    return c;
  }
};
int32_t main()
{
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int n,q;cin>>n>>q;
    BottleneckTree bt(n);
    map<pair<int,int>,int> ls;
    vector<vector<array<int,3> > > add(q+1);
    vector<bool> que(q+1);
    for(int cyc=0;cyc<q;++cyc) {
        char c;cin>>c;
        if(c=='+') {
        int u,v;cin>>u>>v;--u;--v;
        if(u>v) swap(u,v);
        ls[{u,v}]=cyc;
        }
        else if(c=='-') {
            int u,v;cin>>u>>v;--u;--v;
            if(u>v) swap(u,v);
            add[cyc].app({u,v,ls[{u,v}]});
            ls.erase({u,v});
        }
        else {
            assert(c=='?');
            que[cyc]=1;
        }
    }
    for(auto [key,val]:ls) {
        add[q].app({key.first,key.second,val});
    }
    vector<int> cnt(q+1);int res=0;
    vector<int> answer;
    for(int i=q;i>=0;--i) {
        for(auto h:add[i]) {
            int u=h[0];int v=h[1];int co=h[2];
            int c1=bt.AddEdge(u,v,co);
            if(co<=i+1) ++res;
            if(c1<=i+1) --res;
            cnt[co]++;if(c1<=q) cnt[c1]--;
        }
        if(i+1<=q) res-=cnt[i+1];
        if(que[i]) {
            answer.app(n-res);
        }
    }
    reverse(all(answer));
    for(int x:answer) cout<<x<<'\n';
    return 0;
}
