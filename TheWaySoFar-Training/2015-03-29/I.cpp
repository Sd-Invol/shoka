#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 2005;

LL n; int m;
LL res[N] , C[N][N];

int main() {
    int i , j , k;
    cin >> n >> m;
    for (i = 0 ; i <= 2000; ++ i) {
        C[i][0] = 1;
        for (j = 1 ; j <= i ; ++ j)
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
    }
    for (i = m ; i > 0 ; -- i) {
        if (!n)
            res[i] = i - 1;
        else {
            if (i > 10) {
                j = i;
                while (C[j + 1][i] > C[j][i] && C[j + 1][i] <= n)
                    ++ j;
                res[i] = j;
                n -= C[j][i];
            } else {
                LL l = i , r = n , mid;
                while (l < r) {
                    mid = l + r + 1 >> 1;
                    LL x = 1; double y = 1;
                    for (j = 1 ; j <= i ; ++ j) { 
                        y *= mid - j + 1;
                        y /= j;
                        x *= mid - j + 1;
                        x /= j;
                    }
                    if (y <= n + 100 && x <= n)
                        l = mid;
                    else
                        r = mid - 1;
                }
                mid = l;
                LL x = 1;
                for (j = 1 ; j <= i ; ++ j) {
                    x *= mid - j + 1;
                    x /= j;
                }
                res[i] = l;
                n -= x;
            }
        }        
    }
    for (i = m ; i > 0 ; -- i)
        printf("%lld%c" , res[i] , " \n"[i == 1]);
    
    return 0;
}
