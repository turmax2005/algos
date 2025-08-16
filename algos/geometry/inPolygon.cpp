auto inT = [&] (Point a, Point b, Point c, Point p) {
  a = a-p; b = b-p; c = c-p;
  int ab = a * b, bc = b * c, ca = c * a;
  return abs(ab)+abs(bc)+abs(ca) == abs(ab+bc+ca);
};
auto inP = [&] (Point p) {
//a must be in counterclockwise order!
//assuming no three points of a are collinear
  if (n == 1) return p == a[0];
  if (n == 2) return (p-a[0]) * (a[1]-a[0]) == 0 && (p-a[0]) % (p-a[1]) <= 0;
  int l = 1, r = n - 1;
  while (l < r - 1) {
    int m = (l + r) / 2;
    if ((a[m] - a[0]) < (p - a[0])) {
      l = m;
    } else {
      r = m;
    }
  }
  return inT(a[l], a[0], a[r], p);
};

