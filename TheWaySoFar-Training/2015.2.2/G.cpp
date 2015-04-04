#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 505;
const int Q = 1e9 + 7;

int n , m , K;
LL f[11][N] , p[N] , C[N][N];
LL power(LL A , LL B) {
    LL res = 1;
    while (B) {
        if (B & 1)
            res *= A , res %= Q;
        A *= A , A %= Q , B >>= 1;
    }
    return res;
}

void work() {
    int i , j , k;
    scanf("%d%d%d",&n,&m,&K);
    if (n < m) swap(n , m);   
    for (i = 0 ; i <= n ; ++ i) {
        C[i][0] = 1;
        p[i] = i ? (LL)p[i - 1] * i % Q : 1;
        for (j = 1 ; j <= i ; ++ j)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % Q;
    }
    f[0][0] = 1;
    for (i = 0 ; i < K ; ++ i) {
        for (j = 0 ; j <= m ; ++ j) {
            if (!f[i][j])
                continue;
            for (k = 0 ; j + k <= m ; ++ k) {                
                LL x = power(i , k * (n + m - k - j - j - 1)) * f[i][j] % Q * C[m - j][k] % Q * C[n - j][k] % Q * p[k] % Q;
                f[i + 1][j + k] += x;
                f[i + 1][j + k] %= Q;
            }
        }
    }
    int res = 0;
    for (i = 1 ; i <= m ; ++ i) {
        f[K][i] = power(K , (n - i) * (m - i)) * f[K][i] % Q;
        if (i & 1)
            res += f[K][i];
        else
            res += Q - f[K][i];
        res %= Q;
    }
    cout << res << endl;
}

int main() {
    work();    
    return 0;
}
