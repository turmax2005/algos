#include <bits/stdc++.h>

using namespace std;
#define int long long
template<int32_t MOD>
struct ModInt {
    int32_t value;

    ModInt() : value(0) {}

    ModInt(long long v) : value(v % MOD) { if (value < 0) value += MOD; }

    ModInt(int32_t v): value(v % MOD) { if (value < 0) value += MOD; }

    ModInt operator+=(ModInt m) {
        value += m.value;
        if (value >= MOD) value -= MOD;
        return value;
    }

    ModInt operator-=(ModInt m) {
        value -= m.value;
        if (value < 0) value += MOD;
        return value;
    }

    ModInt operator*=(ModInt m) {
        value = (value * 1LL * m.value) % MOD;
        return value;
    }

    ModInt power(long long exp) const {
        if (exp == 0) return 1;
        ModInt res = (exp & 1 ? value : 1);
        ModInt half = power(exp >> 1);
        return res * half * half;
    }

    ModInt operator/=(ModInt m) { return *this *= m.power(MOD - 2); }

    friend std::istream &operator>>(std::istream &is, ModInt &m) {
        is >> m.value;
        return is;
    }

    friend std::ostream &operator<<(std::ostream &os, const ModInt &m) {
        os << m.value;
        return os;
    }

    explicit operator int32_t() const { return value; }

    explicit operator long long() const { return value; }

    static int32_t mod() { return MOD; }
};

template<int32_t MOD>ModInt<MOD> operator+(ModInt<MOD> a, ModInt<MOD> b) { return a += b; }
template<int32_t MOD, typename L>ModInt<MOD> operator+(L a, ModInt<MOD> b) { return ModInt<MOD>(a) += b; }
template<int32_t MOD, typename R>ModInt<MOD> operator+(ModInt<MOD> a, R b) { return a += b; }

template<int32_t MOD>ModInt<MOD> operator-(ModInt<MOD> a, ModInt<MOD> b) { return a -= b; }
template<int32_t MOD, typename L>ModInt<MOD> operator-(L a, ModInt<MOD> b) { return ModInt<MOD>(a) -= b; }
template<int32_t MOD, typename R>ModInt<MOD> operator-(ModInt<MOD> a, R b) { return a -= b; }

template<int32_t MOD>ModInt<MOD> operator*(ModInt<MOD> a, ModInt<MOD> b) { return a *= b; }
template<int32_t MOD, typename L>ModInt<MOD> operator*(L a, ModInt<MOD> b) { return ModInt<MOD>(a) *= b; }
template<int32_t MOD, typename R>ModInt<MOD> operator*(ModInt<MOD> a, R b) { return a *= b; }

template<int32_t MOD>ModInt<MOD> operator/(ModInt<MOD> a, ModInt<MOD> b) { return a /= b; }
template<int32_t MOD, typename L>ModInt<MOD> operator/(L a, ModInt<MOD> b) { return ModInt<MOD>(a) /= b; }
template<int32_t MOD, typename R>ModInt<MOD> operator/(ModInt<MOD> a, R b) { return a /= b; }

template<int32_t MOD>bool operator==(ModInt<MOD> a, ModInt<MOD> b) { return a.value == b.value; }
template<int32_t MOD, typename L>bool operator==(L a, ModInt<MOD> b) { return a == b.value; }
template<int32_t MOD, typename R>bool operator==(ModInt<MOD> a, R b) { return a.value == b; }

template<int32_t MOD>bool operator!=(ModInt<MOD> a, ModInt<MOD> b) { return a.value != b.value; }
template<int32_t MOD, typename L>bool operator!=(L a, ModInt<MOD> b) { return a != b.value; }
template<int32_t MOD, typename R>bool operator!=(ModInt<MOD> a, R b) { return a.value != b; }

using mint = ModInt<998244353>;
//using mint = ModInt<(int32_t)(1e9 + 7)>;
//237c16
const int maxn=1e6+5;
mint fact[maxn];mint invf[maxn];
void init() {
    fact[0]=1;for(int i=1;i<maxn;++i) {fact[i]=(fact[i-1]*i);}
    invf[maxn-1]=((mint) (1))/fact[maxn-1];for(int i=maxn-2;i>=0;--i) invf[i]=(invf[i+1]*(i+1));
}
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
