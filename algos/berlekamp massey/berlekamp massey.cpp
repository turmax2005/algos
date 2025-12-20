template<typename T>
vector<T> berlekampMassey(const vector<T> &s) {
  int n = s.size(), l = 0, m = 1;
  vector<T> b(n), c(n);
  T ld = b[0] = c[0] = 1;
  for (int i=0; i<n; i++, m++) {
    T d = s[i];
    for (int j=1; j<=l; j++)
      d += c[j] * s[i-j];
    if (d == 0) continue;
    vector<T> temp = c;
    T coef = d / ld;
    for (int j=m; j<n; j++) c[j] -= coef * b[j-m];
    if (2 * l <= i) {
      l = i + 1 - l;
      b = temp;
      ld = d;
      m = 0;
    }
  }
  c.resize(l + 1);
  c.erase(c.begin());
  for (T &x : c)
    {x = 0-x;}
  return c;
}
mint inv2=((mint) (1))/((mint) (2));
vector<mint> operator+(vector<mint> a,vector<mint> b) {
    while(a.size()<b.size()) a.app(0);
    for(int i=0;i<b.size();++i) a[i]+=b[i];
    return a;
}
vector<mint> operator-(vector<mint> a,vector<mint> b) {
    while(a.size()<b.size()) a.app(0);
    for(int i=0;i<b.size();++i) a[i]-=b[i];
    return a;
}
vector<mint> operator*(vector<mint> a,vector<mint> b) { ///O(n^2)
    vector<mint> c(a.size()+b.size()-1);
    for(int i=0;i<a.size();++i) for(int j=0;j<b.size();++j) c[i+j]+=a[i]*b[j];
    return c;
}
mint kitamasa(vector<mint> a,vector<mint> b,int n) {
    if(a.empty()) a.app(0);
    if(n==0) {
        return a[0]/b[0];
    }
    if(n%2==0) {
        vector<mint> bmi=b;for(int i=1;i<bmi.size();i+=2) {bmi[i]=(0-b[i]);}
        vector<mint> ami=a;for(int i=1;i<ami.size();i+=2) {ami[i]=(0-a[i]);}
        vector<mint> P=a*bmi+b*ami;
        vector<mint> Q=b*bmi;
        vector<mint> P1,Q1;
        for(int i=0;i<P.size();i+=2) {P1.app(P[i]);}
        for(int i=0;i<Q.size();i+=2) {Q1.app(Q[i]);}
        return inv2*kitamasa(P1,Q1,n/2);
    }
    else {
        vector<mint> bmi=b;for(int i=1;i<bmi.size();i+=2) {bmi[i]=(0-b[i]);}
        vector<mint> ami=a;for(int i=1;i<ami.size();i+=2) {ami[i]=(0-a[i]);}
        vector<mint> P=a*bmi-b*ami;
        vector<mint> Q=b*bmi;
        vector<mint> P1,Q1;
        for(int i=1;i<P.size();i+=2) {P1.app(P[i]);}
        for(int i=0;i<Q.size();i+=2) {Q1.app(Q[i]);}
        return inv2*kitamasa(P1,Q1,n/2);
    }
}
mint coeff(vector<mint> A,int b) {
    if(b<A.size()) {return A[b];}
    vector<mint> v=berlekampMassey(A);v.insert(v.begin(),0);
    for(mint &x:v) {x=0-x;}
    v[0]=1;
    vector<mint> v1;
    for(int i=A.size()-v.size()+1;i<A.size();++i) v1.app(A[i]);
    v1=v1*v;v1.resize(v.size()-1);
    return kitamasa(v1,v,b-(A.size()-v.size()+1));
}
