#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 405;
const int M = 50005;

int n , m , ca;
int X[N] , Y[N] , Z[N] , K[N];
pair<int , int> e[M];
double res;
int f[N] , s[N];
double dist[N][N];
double g[N][N] , d[N];
bool vis[N];
int getf(int x) {
    return f[x] == x ? x : f[x] = getf(f[x]);
}

double cal(int H) {
    int i , j , x , y , z;
    for (i = 1 ; i <= n ; ++ i) {
        if (Z[i] <= H) {
            f[i] = i;
            s[i] = K[i];
        }
    }
    for (i = 0 ; i < m ; ++ i) {
        x = e[i].first , y = e[i].second;
        if (Z[x] > H || Z[y] > H)
            continue;
        x = getf(x) , y = getf(y);
        if (x != y) {
            f[x] = y;
            s[y] += s[x];
        }
    }
    int S = getf(1) , T = getf(n);
    if (s[S] < 1 || s[T] < 1)
        return 1e40;
    for (i = 1 ; i <= n ; ++ i)
        for (j = 1 ; j <= n ; ++ j)
            g[i][j] = 1e40;
    for (i = 1 ; i <= n ; ++ i) {
        if (Z[i] <= H && K[i]) {
            for (j = 1 ; j <= n ; ++ j) {
                if (Z[j] <= H && K[j]) {
                    x = getf(i);
                    y = getf(j);
                    g[x][y] = min(g[x][y] , dist[i][j]);
                }
            }
        }
    }
    for (i = 1 ; i <= n ; ++ i)
        d[i] = 1e40 , vis[i] = 0;
    d[S] = 0;
    while (1) {
        x = -1;
        for (i = 1 ; i <= n ; ++ i)
            if (!vis[i] && (!~x || d[i] < d[x]))
                x = i;
        if (x == -1 || d[x] > 1e30)
            break;
        vis[x] = 1 , d[x] += s[x] * 0.5;
        if (x == T) break;
        for (i = 1 ; i <= n ; ++ i)
            if (!vis[i] && g[x][i] < 1e30) {
                if (i == T || s[i] > 1)
                    d[i] = min(d[i] , d[x] + g[x][i] - 1);
            }
    }
    return d[T];
}


void work() {
    int i , j;
    for (i = 1 ; i <= n ; ++ i) {
        scanf("%d%d%d%d",&X[i] ,&Y[i] ,&Z[i] ,&K[i]);
    }
    for (i = 0 ; i < m ; ++ i) {
        scanf("%d%d",&e[i].first , &e[i].second);
    }
    for (i = 1 ; i <= n ; ++ i) {
        for (j = 1 ; j <= n ; ++ j) {
            int dx = X[i] - X[j];
            int dy = Y[i] - Y[j];
            int dz = Z[i] - Z[j];
            dist[i][j] = sqrt(dx * dx + dy * dy + dz * dz);
        }
    }
    res = 1e40;
    for (i = 1 ; i <= n ; ++ i)
        if (Z[i] >= Z[1] && Z[i] >= Z[n])
            res = min(res , cal(Z[i]));
    printf("Case %d: " , ++ ca);
    if (res > 1e30)
        puts("impossible");
    else
        printf("%.4f\n" , res);
}

int main() {
    while (~scanf("%d%d",&n,&m))
        work();
    return 0;
}
