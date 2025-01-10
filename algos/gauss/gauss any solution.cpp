optional<vector<int> > gauss(vector<vector<int> > A,vector<int> b) ///returns v such that Av=b
{
    int n=A.size();assert(b.size()==n);int m=A[0].size();
    for(int &x:b) {x%=p;x+=p;x%=p;}
    for(int i=0;i<n;++i) {for(int &x:A[i]) {x%=p;x+=p;x%=p;}}
    int bi=0;
    for(int i=0;i<n;++i)
    {
        if(bi==m) break;
        for(int j=i;j<n;++j)
        {
            if(A[j][bi])
            {
                if(j!=i) {swap(A[i],A[j]);swap(b[i],b[j]);}
                break;
            }
        }
        if(A[i][bi])
        {
            int o=inv(A[i][bi]);
            for(int j=i+1;j<n;++j)
            {
                int we=(A[j][bi]*o)%p;
                b[j]-=we*b[i];b[j]%=p;if(b[j]<0) b[j]+=p;
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
    vector<int> v(m);
    for(int i=n-1;i>=0;--i)
    {
        int bi=0;
        while(bi<m && !A[i][bi]) {++bi;}
        if(bi==m)
        {
            if(b[i]) {return nullopt;}
            else {continue;}
        }
        {
        int cur=b[i];
        for(int j=bi+1;j<m;++j)
        {
            cur-=A[i][j]*v[j];cur%=p;
        }
        v[bi]=cur*inv(A[i][bi]);v[bi]%=p;if(v[bi]<0) v[bi]+=p;
        }
    }
    return v;
}
