__int128 one=1;
int po(int a,int b,int p)
{
  int res=1;
  while(b) {if(b & 1) {res=(res*one*a)%p;--b;} else {a=(a*one*a)%p;b>>=1;}} return res;
}
bool chprime(int n) ///miller-rabin
{
  if(n==2) return true;
  if(n<=1 || n%2==0) return false;
  int h=n-1;int d=0;while(h%2==0) {h/=2;++d;}
  for(int a:{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37})
    {
    if(a==n) return true;
    int u=po(a,h,n);bool ok=0;
    if(u%n==1) continue;
    for(int c=0;c<d;++c)
      {
      if((u+1)%n==0) {ok=1;break;}
      u=(u*one*u)%n;
    }
    if(!ok) return false;
  }
  return true;
}
//86b2ed
