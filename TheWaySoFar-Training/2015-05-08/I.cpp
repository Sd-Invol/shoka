#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 505;

int n , m , a , b , h[N][N];
int d[N] , L[N] , R[N] , s[N] , top;
int main() {
    int i , j , k;
    scanf("%d%d%d%d",&a,&b,&n,&m);
    if (a > b) swap(a , b); 
    for (i = 1 ; i <= n ; ++ i)
        for (j = 1 ; j <= m ; ++ j)
            scanf("%d" , &h[i][j]);
    LL res = 0;
    for (j = 1 ; j <= n ; ++ j) {
        for (i = 1 ; i <= m ; ++ i)
            d[i] = 1 << 30;
        for (k = j ; k <= n ; ++ k) {
            int w = k - j + 1 , l;
            if (w > b) break;
            if (w <= a)
                l = b;
            else
                l = a;            
            for (i = 1 ; i <= m ; ++ i)
                d[i] = min(d[i] , h[k][i]);
            for (i = 1 ; i <= m ; ++ i) {
                while (top && d[i] < d[s[top]])
                    R[s[top --]] = i;
                s[++ top] = i;
            }
            while (top)
                R[s[top --]] = i;
            for (i = m ; i > 0 ; -- i) {
                while (top && d[i] < d[s[top]])
                    L[s[top --]] = i;
                s[++ top] = i;
            }
            while (top)
                L[s[top --]] = i;
            for (i = 1 ; i <= m ; ++ i) {
                int x = R[i] - L[i] - 1;
                x = min(x , l);
                LL y = ((LL)n * m * d[i] - 1) / (n * m - w * x);
                res = max(res , x * y * w);
            }
        }
    }
    printf("%lld\n" , res);    
    return 0;
}
