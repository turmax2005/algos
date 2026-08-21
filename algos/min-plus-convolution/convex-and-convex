vector<int> solve(vector<int> a, vector<int> b){ ///a must be convex, b must be convex (and both nonempty) (copied from https://judge.yosupo.jp/submission/324929)
    int n = a.size(), m = b.size();

    int i = 0, j = 0;
    int cur = a[0] + b[0];
    vector<int> c(n+m-1);
    for(int _ = 0; _ < n + m - 1; ++_){
        c[_] = cur;
        if (i + 1 == n || (j + 1 < m && b[j+1] - b[j] < a[i+1] - a[i])){
            cur += b[j+1] - b[j];
            j++;
        }
        else {
            cur += a[i+1] - a[i];
            i++;
        }
    }
    return c;
}
