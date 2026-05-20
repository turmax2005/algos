vector<vector<int> > sift(vector<vector<int> > a,int s1,int s2) { ///all a[i] has a size of s1, we need the same nonintersections with s2 , a[i] < 998244353 !!!
    vector<mint> dets(1<<(s1+s2));
    vector<vector<mint> > gauss;
    vector<int> firstbits;
    vector<vector<int> > answer;
    for(vector<int> v:a) {
        fill(all(dets),0);
        dets[0]=1;
        for(int i=0;i<s1;++i) {
            mint cur=1;
            for(int j=0;j<s1+s2;++j) {
                for(int was=0;was<(1<<(s1+s2));++was) {
                    if(__builtin_popcount(was)==i) {
                        if(!(was & (1<<j))) {
                            mint sn=1;
                            for(int h=j+1;h<s1+s2;++h) {
                                if(was & (1<<h)) {
                                    sn*=(-1);
                                }
                            }
                            dets[was+(1<<j)]+=dets[was]*cur*sn;
                        }
                    }
                }
                cur*=v[i];
            }
        }
        vector<mint> A;
        for(int mask=0;mask<(1<<(s1+s2));++mask) {
            if(__builtin_popcount(mask)==s1) {
                A.app(dets[mask]);
            }
        }
        int fb=0;bool ins=false;
        for(int i=0;i<gauss.size();++i) {
            while(fb<A.size() && A[fb]==0) ++fb;
            if(fb==A.size()) break;
            if(fb<firstbits[i]) {
                firstbits.insert(firstbits.begin()+i,fb);
                gauss.insert(gauss.begin()+i,A);
                answer.app(v);
                ins=true;
                break;
            }
            if(fb==firstbits[i]) {
                mint o=(A[fb]/gauss[i][fb]);
                for(int j=fb;j<A.size();++j) {
                    A[j]=A[j]-o*gauss[i][j];
                }
            }
        }
        while(fb<A.size() && A[fb]==0) ++fb;
        if(fb<A.size() && !ins) {
            firstbits.app(fb);
            gauss.app(A);
            answer.app(v);
        }
    }
    return answer;
}
