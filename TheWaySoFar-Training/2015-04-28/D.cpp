#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

pair<LL , LL> cal(LL n , LL x) {
    if (x == 1) {
        return make_pair(n + 1 >> 1 , n >> 1);
    } else {
        pair<LL , LL> y = cal(n - 1 , (x + 1) >> 1);
        if (n & 1) {
            if (x & 1)
                ++ y.first;
            else
                ++ y.second;
        } else {
            if (~x & 1)
                ++ y.first;
            else
                ++ y.second;            
        }
        return y;
    }
}

int main() {
    LL n;
    int X , Y , Q;
    scanf("%lld%d%d%d",&n,&X,&Y,&Q);
    while (Q --) {
        LL x;
        scanf("%lld" , &x);
        pair<LL , LL> k = cal(n , x);
        printf("%lld %lld\n" , k.first , k.second);
    }
    return 0;
}
