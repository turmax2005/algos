int div_up(int a, int b) { return a/b+((a^b)>0&&a%b); } // divide a by b rounded up
const int LQ = ..., RQ = ...; //leftmost query, rightmost query
int in(ii L, int x) {
  return L.x * x + L.y;
}
struct Hull {
vector <pair <int, int> > lines;
vector <int> borders;
void push(ii L) {
  while (lines.size() && in(L,borders.back()) < in(lines.back(),borders.back())) {
    lines.pop_back();
    borders.pop_back();
  }
  if (lines.empty()) {
    lines = {L};
    borders = {LQ};
  }
  else if (lines.back().x > L.x) {
    int x = div_up(L.y - lines.back().y, lines.back().x - L.x);
    if (x <= RQ) {
      lines.app(L);
      borders.app(x);
    }
  }
}
Hull (){}
Hull (vector <ii> a) {
  auto comp = [&] (ii u, ii v) {
    return u.x > v.x || (u.x == v.x && u.y < v.y);
  };
  sort(all(a), comp);
  for (auto L : a) {
    push(L);
  }
}
int get(int x) {
  int pos = upper_bound(all(borders), x) - borders.begin();
  assert(pos>0);
  pos--;
  return in(lines[pos],x);
}
};
