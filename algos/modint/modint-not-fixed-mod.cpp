#define int long long
int MOD;
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
        res *= half;
        res *= half;
        return res;
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

ModInt operator+(ModInt a, ModInt b) { return a += b; }

ModInt operator-(ModInt a, ModInt b) { return a -= b; }

ModInt operator*(ModInt a, ModInt b) { return a *= b; }

ModInt operator/(ModInt a, ModInt b) { return a /= b; }

bool operator==(ModInt a, ModInt b) { return a.value == b.value; }

bool operator!=(ModInt a, ModInt b) { return a.value != b.value; }

using mint = ModInt;
const int maxn=1e6+5;
mint fact[maxn];mint invf[maxn];
void init() {
    fact[0]=1;for(int i=1;i<maxn;++i) {fact[i]=(fact[i-1]*i);}
    invf[maxn-1]=((mint) (1))/fact[maxn-1];for(int i=maxn-2;i>=0;--i) invf[i]=(invf[i+1]*(i+1));
}
mint C(int n,int k) {
    if(n<0 || k<0 || n<k) return 0;
    return fact[n]*invf[k]*invf[n-k];
}
