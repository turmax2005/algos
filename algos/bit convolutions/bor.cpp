vector<int> bor(vector<int> a,vector<int> b)
{
  int n=0;while((1<<n)<a.size()) ++n;
  a.resize(1<<n);b.resize(1<<n);
  for(int i=0;i<n;++i) for(int mask=0;mask<(1<<n);++mask) if(!(mask & (1<<i))) {a[mask+(1<<i)]+=a[mask];a[mask+(1<<i)]%=p;}
  for(int i=0;i<n;++i) for(int mask=0;mask<(1<<n);++mask) if(!(mask & (1<<i))) {b[mask+(1<<i)]+=b[mask];b[mask+(1<<i)]%=p;}
  vector<int> c(1<<n,0);
  for(int mask=0;mask<(1<<n);++mask) {c[mask]=a[mask]*b[mask];c[mask]%=p;}
  for(int i=0;i<n;++i) for(int mask=0;mask<(1<<n);++mask) if(mask & (1<<i)) {c[mask]-=c[mask-(1<<i)];c[mask]%=p;}
  return c;
}