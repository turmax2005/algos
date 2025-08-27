namespace LCT {
  vector<vi> ch;
  vi fa, rev;
  void init(int n) {
    ch.resize(n + 1);
    fa.resize(n + 1);
    rev.resize(n + 1);
    for (int i = 0; i <= n; i++)
      ch[i].resize(2),
      ch[i][0] = ch[i][1] = fa[i] = rev[i] = 0;
  }
  bool isr(int a)
  {
    return !(ch[fa[a]][0] == a || ch[fa[a]][1] == a);
  }
  void pushdown(int a)
  {
    if(rev[a])
    {
      rev[ch[a][0]] ^= 1, rev[ch[a][1]] ^= 1;
      swap(ch[a][0], ch[a][1]);
      rev[a] = 0;
    }
  }
  void push(int a)
  {
    if(!isr(a)) push(fa[a]);
    pushdown(a);
  }
  void rotate(int a)
  {
    int f = fa[a], gf = fa[f];
    int tp = ch[f][1] == a;
    int son = ch[a][tp ^ 1];
    if(!isr(f))
      ch[gf][ch[gf][1] == f] = a;
    fa[a] = gf;

    ch[f][tp] = son;
    if(son) fa[son] = f;

    ch[a][tp ^ 1] = f, fa[f] = a;
  }
  void splay(int a)
  {
    push(a);
    while(!isr(a))
    {
      int f = fa[a], gf = fa[f];
      if(isr(f)) rotate(a);
      else
      {
        int t1 = ch[gf][1] == f, t2 = ch[f][1] == a;
        if(t1 == t2) rotate(f), rotate(a);
        else rotate(a), rotate(a);
      }
    }
  }
  void access(int a)
  {
    int pr = a;
    splay(a);
    ch[a][1] = 0;
    while(1)
    {
      if(!fa[a]) break;
      int u = fa[a];
      splay(u);
      ch[u][1] = a;
      a = u;
    }
    splay(pr);
  }
  void makeroot(int a)
  {
    access(a);
    rev[a] ^= 1;
  }
  void link(int a, int b)
  {
    makeroot(a);
    fa[a] = b;
  }
  void cut(int a, int b)
  {
    makeroot(a);
    access(b);
    fa[a] = 0, ch[b][0] = 0;
  }
  int fdr(int a)
  {
    access(a);
    while(1)
    {
      pushdown(a);
      if (ch[a][0]) a = ch[a][0];
      else {
        splay(a);
        return a;
      }
    }
  }
}
//647cca
