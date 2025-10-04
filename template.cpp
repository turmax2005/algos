#include <bits/stdc++.h>

using namespace std;
#define int long long
const int p=1e9+7;
int po(int a,int b) {if(b==0) return 1; if(b==1) return a; if(b%2==0) {int u=po(a,b/2);return (u*1LL*u)%p;} else {int u=po(a,b-1);return (a*1LL*u)%p;}}
int inv(int x) {return po(x,p-2);}
mt19937 rnd;
#define app push_back
#define all(x) (x).begin(),(x).end()
#ifdef LOCAL
#define debug(...) [](auto...a){ ((cout << a << ' '), ...) << endl;}(#__VA_ARGS__, ":", __VA_ARGS__)
#define debugv(v) do {cout<< #v <<" : {"; for(int izxc=0;izxc<v.size();++izxc) {cout << v[izxc];if(izxc+1!=v.size()) cout << ","; }cout <<"}"<< endl;} while(0)
#else
#define debug(...)
#define debugv(v)
#endif
#define lob(a,x) lower_bound(all(a),x)
#define upb(a,x) upper_bound(all(a),x)
#define print(x) cout<<(x)<<'\n'
#define suma(a) accumulate(all(a),0LL)
#define maxpos(a) max_element(all(a))-a.begin()
#define minpos(a) min_element(all(a))-a.begin()
#define maxa(a) *max_element(all(a))
#define mina(a) *min_element(all(a))
pair<int,vector<int> > read()
{
    int n;cin>>n;vector<int> a(n);for(int &x:a) {cin>>x;} return {n,a};
}
int32_t main()
{
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int t;cin>>t;
    while(t--)
    {

    }
    return 0;
}
