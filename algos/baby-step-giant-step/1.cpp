#define T int
int mod;
int gcd(int a, int b, int &x, int &y) {
  if (b==0) { x = 1; y = 0; return a; }
  int d = gcd(b,a%b,y,x);
  y-=a/b*x;
  return d;
}
int inv(int r, int m) {
  int x, y;
  gcd(r,m,x,y);
  return (x+m)%m;
}
int crt(int r, int n, int c, int m) { return r + ((c - r) % m + m) * inv(n, m) % m * n; }
T inv(T a)
{
  return inv(a,mod);
}
T mul(T a,T b)
{
  return (a*b)%mod;
}
vector<int> rasl(int x)
{
  vector<int> v;
  if(x==1) {return v;}
  for(int i=2;i*i<=x;++i)
  {
    if(x%i==0)
    {
      v=rasl(x/i);v.app(i);return v;
    }
  }
  v.app(x);return v;
}
T po(T a,int b) ///b>=1
{
  if(b==1) {return a;}
  if(b%2==0)
  {
    T u=po(a,b/2);
    return mul(u,u);
  }
  else
  {
    T u=po(a,b-1);
    return mul(a,u);
  }
}
T getper(T a,T one,int per,vector<int> v)
{
  for(int p:v)
  {
    if(po(a,per/p)==one)
    {
      per/=p;
    }
  }
  return per;
}
vector<pair<int,int> > shanks(T a,vector<T> b,T one,int per) ///a^per=1 and b[i]^per=1 /// all right numbers in output are equal
{
  if(b.empty()) {return {};}
  int n=b.size();
  vector<int> vp=rasl(per);
  int pera=getper(a,one,per,vp);per=pera;
  vp=rasl(pera);
  vector<int> have(n,0);
  int cur2=per;T cura=a;T invcura=inv(a);
  int curad=1;
  vector<pair<T,int> > v;
  vector<bool> ok(n,true);
  vector<T> poinvzx;
  for(int p:vp)
  {
    T ca=po(cura,cur2/p);
    if(ca==one) {continue;}
    T invca=po(invcura,cur2/p);
    int step=sqrt(b.size()*p)+2;
    int wee=p/step+2;
    v.clear();poinvzx.clear();
    T zx=one;T invzx=one;T buba=one;
    vector<T> zhe;
    T lu=one;
    for(int i=0;i<step;++i)
    {
      v.app({zx,i});zhe.app(lu);
      zx=mul(zx,ca);invzx=mul(invzx,invca);buba=mul(buba,cura);lu=mul(lu,invcura);
    }
    poinvzx.app(one);
    for(int j=0;j<wee;++j)
    {
      poinvzx.app(mul(poinvzx.back(),buba));
    }
    sort(all(v));
    for(int i=0;i<n;++i)
    {
      if(!ok[i]) {continue;}
      T uu=po(b[i],cur2/p);
      bool okkk=false;
      for(int j=0;j<wee;++j)
      {
        auto it=lower_bound(all(v),make_pair(uu,0LL));
        if(it!=v.end() && (*it).first==uu)
        {
          okkk=true;
          have[i]-=(curad*step*j);
          have[i]+=(curad*(*it).second);
          have[i]%=pera;if(have[i]<0) {have[i]+=pera;}
          b[i]=mul(b[i],poinvzx[j]);b[i]=mul(b[i],zhe[(*it).second]);
          assert(po(b[i],cur2/p)==one);
          break;
        }
        uu=mul(uu,zx);
      }
      if(!okkk) {ok[i]=false;}
    }
    cur2/=p;cura=po(cura,p);invcura=po(invcura,p);curad*=p;
  }
  vector<pair<int,int> > res;
  for(int i=0;i<n;++i)
  {
    if(ok[i] && b[i]==one)
    {
      res.app({(have[i]%pera+pera)%pera,pera});
    }
    else
    {
      res.app({-1,pera});
    }
  }
  return res;
}
int shanks2(int x,int y,int mod1) ///only for T=long long, 0^0 = 1 by default
{
  mod=mod1;
  vector<int> v=rasl(mod);sort(all(v));
  int per=1;for(int i=0;i<v.size();++i) {if(i==0 || v[i]!=v[i-1]) {per*=(v[i]-1);} else {per*=v[i];}}
  if(y==1 || mod==1) {return 0;}
  int C=61;
  for(int i=1;i<C;++i)
  {
    if(po(x,i)==y) {return i;}
  }
  if(y==0) {return (-1);}
  T h=po(x,C);
  int lc1=gcd(h,mod);int lc2=gcd(y,mod);
  if(lc1!=lc2) {return (-1);}
  mod/=lc2;T h1=h/lc2;T y1=y/lc2;
  vector<pair<int,int> > s=shanks(x%mod,{mul(y1,inv(h1))},1,per);
  if(s[0].first!=(-1))
  {
    return s[0].first+C;
  }
  else
  {
    return (-1);
  }
}