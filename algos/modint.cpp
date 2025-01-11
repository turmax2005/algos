template<int32_t MOD>
struct ModInt {
    int32_t value;

    ModInt() : value(0) {}

    ModInt(long long v) : value(v % MOD) { if (value < 0) value += MOD; }

    ModInt(int32_t v) : value(v < 0 ? MOD + v : v) {}

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
