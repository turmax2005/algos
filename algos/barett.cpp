using u64 = unsigned long long;
using u128 = __uint128_t;
struct barrett{
  u64 p, m;
  barrett() {}
  barrett(u64 p) : p(p), m(-1ULL / p) {}
  int reduce(u64 x) {
    u64 q = (u128(m) * x) >> 64, r = x - q * p;
    return r - p * (r >= p);
  }
} ba;

// Usage example:
void solve() {
  int p = ...;
  ba = barrett(p);
  int x = ..., y = ...;
  int prod = ba.reduce(x * y);
}
