#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <set>
using namespace std;
typedef long long LL;
const int N = 100005;
int n , L , a[N] , d[N] , D;
int c[N] , f[N] , g[N];
void work() {
    scanf("%d%d" , &n , &L);
    D = 0;
    for (int i = 1 ; i <= n ; ++ i) {
        scanf("%d" , &a[i]);
        d[D ++] = a[i];
    }
    sort(d , d + D);
    D = unique(d , d + D) - d;
    for (int i = 1 ; i <= n ; ++ i) {
        a[i] = lower_bound(d , d + D , a[i]) - d + 1;
    }
    memset(c , 0 , sizeof(c));
    f[0] = 0;
    for (int i = 1 ; i <= n ; ++ i) {
        f[i] = 0;
        for (int j = a[i] - 1 ; j > 0 ; j -= j & -j)
            f[i] = max(f[i] , c[j]);
        ++ f[i];
        for (int j = a[i] ; j <= D ; j += j & -j)
            c[j] = max(c[j] , f[i]);        
    }
    memset(c , 0 , sizeof(c));
    g[n + 1] = 0;
    for (int i = n ; i > 0 ; -- i) {
        g[i] = 0;
        for (int j = a[i] + 1 ; j <= D ; j += j & -j)
            g[i] = max(g[i] , c[j]);
        ++ g[i];
        for (int j = a[i] ; j > 0 ; j -= j & -j)
            c[j] = max(c[j] , g[i]);        
    }    
    int res = 0;
    for (int i = 1 ; i <= n - L ; ++ i)
        res = max(res , f[i]);
    for (int i = L + 1 ; i <= n ; ++ i)
        res = max(res , g[i]);    
    memset(c , 0 , sizeof(c));
    for (int i = n ; i > 0 ; -- i) {
        for (int j = a[i] ; j > 0 ; j -= j & -j)
            c[j] = max(c[j] , g[i]);        
        if (i - L - 1 > 0) {
            int p = f[i - L - 1];
            for (int j = a[i - L - 1] + 1 ; j <= D ; j += j & -j)
                res = max(res , p + c[j]);            
        }
    }
    static int ca = 0;
    printf("Case #%d: %d\n" , ++ ca , res);
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}