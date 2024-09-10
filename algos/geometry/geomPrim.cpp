struct Point {
  int x, y;
  Point(){}
  Point (int x_, int y_) {
    x = x_; y = y_;
  }
  Point operator + (Point p) {
    return Point(x+p.x,y+p.y);
  }
  Point operator - (Point p) {
    return Point(x - p.x, y - p.y);
  }
  int operator * (Point p) {
    return x * p.y - y * p.x;
  }
  int operator % (Point p) {
    return x * p.x + y * p.y;
  }
  bool operator < (Point v) {
    return (*this) * v > 0;
  }
  bool operator > (Point v) {
    return v < (*this);
  };
  bool operator <= (Point v) {
    return (*this) * v >= 0;
  }
};
bool line(Point a, Point b, Point c) {
  return (b-a)*(c-b)==0;
}
bool ord(Point a, Point p, Point b) {
  return (p - a)%(p - b)<0;
}

int hp(Point a) {
  if (a.y == 0) return a.x >= 0;
  return a.y > 0;
}

bool comp(Point a, Point b) {
  if (hp(a) != hp(b)) return hp(a) < hp(b);
  return a.x * b.y - a.y * b.x > 0;
}
