    auto inT = [&] (Point a, Point b, Point c, Point p) {
        a = a-p; b = b-p; c = c-p;
        return abs(a*b)+abs(b*c)+abs(c*a) == abs(a*b+b*c+c*a);
    };
    auto inP = [&] (Point p) { //a must be in counterclockwise order!
        int l = 1, r = n - 1;
        while (l < r - 1) {
            int m = (l + r) / 2;
            if ((a[m] - a[0]) < (p - a[0])) {
                l = m;
            }
            else {
                r = m;
            }
        }
        return inT(a[l], a[0], a[r], p);
    };
