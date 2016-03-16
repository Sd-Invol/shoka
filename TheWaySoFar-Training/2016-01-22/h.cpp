#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long LL;
const int N = 1025;
int n , K;
int S[N][N] , a[2][2];
LL f[2][N][N];
int main() {
    scanf("%d%d" , &n , &K);
    for (int i = 0 ; i < n ; ++ i)
        for (int j = 0 ; j < n ; ++ j)
            scanf("%d" , &S[i][j]);
    for (int i = 0 ; i < 2 ; ++ i)
        for (int j = 0 ; j < 2 ; ++ j)
            scanf("%d" , &a[i][j]);
    int cur = 0 , nxt = 1;
    for (int i = 0 ; i < n ; ++ i)
        for (int j = 0 ; j < n ; ++ j)
            f[cur][i][j] = S[i][j];
    for (int k = 0 ; k <= K ; ++ k) {
        LL mn = 1LL << 60 , mx = -1LL << 60;
        for (int i = 0 ; i + (1 << k) - 1 < n ; ++ i)
            for (int j = 0 ; j + (1 << k) - 1 < n ; ++ j) {
                mn = min(mn , f[cur][i][j]);
                mx = max(mx , f[cur][i][j]);                
            }
        printf("%lld %lld\n" , mn , mx);
        for (int i = 0 ; i + (1 << k + 1) - 1 < n ; ++ i)
            for (int j = 0 ; j + (1 << k + 1) - 1 < n ; ++ j) {
                f[nxt][i][j] = 0;
                f[nxt][i][j] += a[0][0] * f[cur][i][j];
                f[nxt][i][j] += a[1][0] * f[cur][i + (1 << k)][j];
                f[nxt][i][j] += a[0][1] * f[cur][i][j + (1 << k)];
                f[nxt][i][j] += a[1][1] * f[cur][i + (1 << k)][j + (1 << k)];
            }
        swap(cur , nxt);
    }

    
    return 0;
}
