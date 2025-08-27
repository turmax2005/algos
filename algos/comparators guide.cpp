bool cmp1(int x, int y) { return x > y; }

struct cmp2{
  bool operator()(int x, int y) const { return x > y; }
};

int32_t main() {
  set<int, decltype(cmp1)*> s1({1, 2, 3}, cmp1);
  for (int x : s1) cout << x << ' '; cout << '\n';
  set<int, cmp2> s2({4, 5, 6});
  for (int x : s2) cout << x << ' '; cout << '\n';
  auto cmp3 = [&](int x, int y) { return x > y; };
  set<int, decltype(cmp3)> s3({7, 8, 9}, cmp3); // second cmp3 could be omitted if cmp3 = [](...) { ... }
  for (int x : s3) cout << x << ' '; cout << '\n';

  vector<int> v{3, 2, 1};
  cout << lower_bound(all(v), 2, cmp1) - v.begin();
  cout << lower_bound(all(v),2,cmp2()) - v.begin();
  cout << lower_bound(all(v), 2, cmp3) - v.begin();
}
//adea08
