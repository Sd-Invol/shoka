#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 50;
const int Q = 1e9 + 7;
int n , m , ca , K;
int g[N][N][2] , deg[N][2] , val[N];

int inverse(int x) {
    return x == 1 ? 1 : (LL)(Q - Q / x) * inverse(Q % x) % Q;
}

int a[N][N];

int det() {
    int n = ::n - 1 , res = 1 , i , j , k , Rank = 0;
    for (i = 0 ; i < n ; ++ i) {
        int pivot = Rank;
        while (pivot < n && !a[pivot][i])
            ++ pivot;
        if (pivot >= n)
            return 0;
        if (pivot != Rank) {
            res = (Q - res) % Q;
            for (j = 0 ; j < n ; ++ j)
                swap(a[Rank][j] , a[pivot][j]);
        }
        res = (LL)res * a[Rank][i] % Q;
        int tmp = inverse(a[Rank][i]);
        for (k = 0 ; k < n ; ++ k) {
            if (k != Rank) {
               int times = (LL)a[k][i] * tmp % Q;
               for (j = 0 ; j < n ; ++ j) {
                   a[k][j] += Q - (LL)a[Rank][j] * times % Q;
                   a[k][j] %= Q;
               } 
            }
        }
        ++ Rank;
    }
    return res;
}

int cal(int X) {
    int i , j;
    memset(a , 0 , sizeof(a));
    for (i = 0 ; i + 1 < n ; ++ i)
        for (j = 0 ; j + 1 < n ; ++ j) {
            a[i][j] -= g[i][j][0] * X + g[i][j][1];
            if (i == j)
                a[i][j] += deg[i][0] * X + deg[i][1];
            a[i][j] = (a[i][j] + Q) % Q;
        }
    return det();
}
int f[2][N];
int L[N][N] , res[N];

void work() {
    int i , j , k , x , y , z;
    scanf("%d%d%d" , &n , &m , &K);
    memset(g , 0 , sizeof(g));
    memset(deg , 0 , sizeof(deg));
    for (i = 0 ; i < m ; ++ i) {
        scanf("%d%d%d" , &x,&y,&j);
        -- x , -- y;
        if (j & 1) {
            z = 0;
            ++ g[x][y][z] , ++ g[y][x][z];
            ++ deg[x][z] , ++ deg[y][z];
        }
        if (j & 2) {
            z = 1;
            ++ g[x][y][z] , ++ g[y][x][z];
            ++ deg[x][z] , ++ deg[y][z];
        }        
    }
    for (i = 0 ; i < n ; ++ i)
        val[i] = cal(i);
    
    for (i = 0 ; i < n ; ++ i) {
        int cur = 0 , nxt = 1;
        memset(f[cur] , 0 , sizeof(f[cur]));
        f[cur][0] = 1;
        for (j = 0 ; j < n ; ++ j) {
            if (i != j) {
                x = inverse((i - j + Q) % Q);
                y = (LL)(Q - j) * x % Q;
                //printf("%d %d : %d %d\n" , i , j , x , y);
                memset(f[nxt] , 0 , sizeof(f[nxt]));
                for (k = 0 ; k < n ; ++ k) {
                    if (f[cur][k]) {
                        f[nxt][k] += (LL)f[cur][k] * y % Q;
                        f[nxt][k] %= Q;
                        f[nxt][k + 1] += (LL)f[cur][k] * x % Q;
                        f[nxt][k + 1] %= Q;                        
                    }
                }
                swap(cur , nxt);
            }
        }
        for (j = 0 ; j < n ; ++ j) {
            L[i][j] = f[cur][j];
            //printf("%d%c" , L[i][j] , " \n"[j + 1 == n]);
        }
    }
    memset(res , 0 , sizeof(res));
    for (i = 0 ; i < n ; ++ i)
        for (x = 0 ; x < n ; ++ x) {
            res[x] += (LL)L[i][x] * val[i] % Q;
            res[x] %= Q;
        }
    int ans = 0;
    for (i = 0 ; i <= K ; ++ i)
        ans = (ans + res[i]) % Q;
    printf("Case #%d: %d\n" , ++ ca , ans);
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}
