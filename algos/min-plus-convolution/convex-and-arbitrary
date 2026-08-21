std::vector<int> solve(std::vector<int> a, std::vector<int> b){ ///a must be convex, b is arbitrary  (copied from Nachia)
    int n = a.size();
    int m = b.size();
    if(n==0 || m==0) return {};
    int z = n + m - 1;
    std::vector<int> c(z, inf);
    std::vector<int> idx(z+1);
    c[0] = a[0] + b[0];
    idx.back() = m-1;
    int d = 1; while(d < z) d *= 2;
    for(int q=d/2; q>0; q/=2){
        for(int h=q; h<z; h+=q*2){
            int l = h-q, r = std::min(h+q, z);
            idx[h] = idx[l];
            for(int t=idx[l]; t<=idx[r]; t++){
                if(t<=h && h-t<n && c[h] > b[t] + a[h-t]){
                    c[h] = b[t] + a[h-t];
                    idx[h] = t;
                }
            }
        }
    }
    return c;
}
