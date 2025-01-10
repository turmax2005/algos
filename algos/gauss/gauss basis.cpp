vector<vector<int> > gaussbasis(vector<vector<int> > A) ///returns basis of Av=0
{
    int n=A.size();int m=A[0].size();
    for(int i=0;i<n;++i) {for(int &x:A[i]) {x%=p;x+=p;x%=p;}}
    int bi=0;
    for(int i=0;i<n;++i)
    {
        if(bi==m) break;
        for(int j=i;j<n;++j)
        {
            if(A[j][bi])
            {
                if(j!=i) {swap(A[i],A[j]);}
                break;
            }
        }
        if(A[i][bi])
        {
            int o=inv(A[i][bi]);
            for(int j=i+1;j<n;++j)
            {
                int we=(A[j][bi]*o)%p;
                for(int k=bi;k<m;++k)
                {
                    A[j][k]-=we*A[i][k];A[j][k]%=p;if(A[j][k]<0) A[j][k]+=p;
                }
            }
        }
        else
        {
            ++bi;--i;continue;
        }
    }
    vector<int> indices(m);iota(all(indices),0);
    for(int i=n-1;i>=0;--i)
    {
        int bi=0;
        while(bi<m && !A[i][bi]) {++bi;}
        if(bi<m)
        {
            indices.erase(find(all(indices),bi));
        }
    }
    vector<vector<int> > v(indices.size(),vector<int>(m,0));
    for(int i=0;i<indices.size();++i)
    {
        v[i][indices[i]]=1;
    }
    for(int i=n-1;i>=0;--i)
    {
        int bi=0;
        while(bi<m && !A[i][bi]) {++bi;}
        if(bi==m) continue;
        for(int k=0;k<indices.size();++k) {
        int cur=0;
        for(int j=bi+1;j<m;++j)
        {
            cur-=A[i][j]*v[k][j];cur%=p;
        }
        v[k][bi]=cur*inv(A[i][bi]);v[k][bi]%=p;if(v[k][bi]<0) v[k][bi]+=p;
        }
    }
    return v;
}
