int fe[maxn];
void pl(int pos,int val) {while(pos<maxn) {fe[pos]+=val;pos|=(pos+1);}}
int get(int pos) {int ans=0;while(pos>=0) {ans+=fe[pos];pos&=(pos+1);--pos;} return ans;} /// [0,pos] - vkluchitelno!!!
int get(int l,int r) {return get(r-1)-get(l-1);} /// sum of [l,r)

//2991a1
