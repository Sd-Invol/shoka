#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 50;
const int Q = 1e9 + 7;
int n , m , G , B;
int g[N][N][3] , deg[N][3] , val[N][N];

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

int cal(int X , int Y) {
    int i , j;
    memset(a , 0 , sizeof(a));
    for (i = 0 ; i + 1 < n ; ++ i)
        for (j = 0 ; j + 1 < n ; ++ j) {
            a[i][j] -= g[i][j][0] + g[i][j][1] * X + g[i][j][2] * Y;
            if (i == j)
                a[i][j] += deg[i][0] + deg[i][1] * X + deg[i][2] * Y;
            a[i][j] = (a[i][j] + Q) % Q;
        }
    /*for (i = 0 ; i + 1 < n ; ++ i)
        for (j = 0 ; j + 1 < n ; ++ j)
        printf("%d%c" , a[i][j] , " \n"[j + 2 == n]);*/
    return det();
}
int f[2][N];
int L[N][N] , res[N][N];

void work() {
    int i , j , k , x , y , z;
    scanf("%d%d%d%d" , &n , &m , &G , &B);
    for (i = 0 ; i < m ; ++ i) {
        scanf("%d%d%d" , &x,&y,&z);
        -- x , -- y , -- z;
        ++ g[x][y][z] , ++ g[y][x][z];
        ++ deg[x][z] , ++ deg[y][z];
    }
    for (i = 0 ; i < n ; ++ i)
        for (j = 0 ; j < n ; ++ j) {
            val[i][j] = cal(i , j);
            //printf("%d%c" , val[i][j] , " \n"[j + 1 == n]);
        }
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
    for (i = 0 ; i < n ; ++ i) {
        for (j = 0 ; j < n ; ++ j) {
            for (x = 0 ; x < n ; ++ x)
                for (y = 0 ; y < n ; ++ y) {
                    res[x][y] += (LL)L[i][x] * L[j][y] % Q * val[i][j] % Q;
                    res[x][y] %= Q;
                    //cout << res[x][y] << endl;
                }
        }
    }
    int ans = 0;
    for (i = 0 ; i <= G ; ++ i)
        for (j = 0 ; j <= B ; ++ j)
            ans = (ans + res[i][j]) % Q;
    cout << ans << endl;
}

int main() {
    work();
    return 0;
}
