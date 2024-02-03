    auto max = [&] (auto cmp) {
        int k = 0;
        for (int lg = 18; lg >= 0; --lg) {
            int i = k + (1 << lg), j = k - (1 << lg);
            i = (i % n + n) % n;
            j = (j % n + n) % n;
            array<int, 3> ind{i, j, k};
            sort(all(ind), cmp);
            k = ind[2];
        }
        return k;        
    };
    auto uppert = [&](Point p) { //last vertex in counterclockwise order about p
        auto cmp = [&] (int i, int j) {return (a[i] - p) < (a[j] - p); };
        return max(cmp);
    };
    auto lowert = [&](Point p) { //first vertex in counterclockwise order about p
        auto cmp = [&] (int i, int j) {return (a[i] - p) > (a[j] - p); };
        return max(cmp);
    };
    auto uppertinf = [&](Point p) { //upper tangent line parallel to vector p
        swap(p.x, p.y);
        p.x = -p.x;
        auto cmp = [&] (int i, int j) { return a[i] % p < a[j] % p; };
        return max(cmp);
    };
    auto lowertinf = [&](Point p) { //lower tangent line parallel to vector p
        swap(p.x, p.y);
        p.x = -p.x;
        auto cmp = [&] (int i, int j) { return a[i] % p > a[j] % p; };
        return max(cmp);
    };
