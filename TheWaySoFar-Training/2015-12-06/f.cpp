#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;

typedef long long LL;
const int N = 1005;

int n , w;
int X[N] , Y[N];
LL g[N][N];
int f[N] , I , J;
int getf(int x) {
    return f[x] == x ? x : f[x] = getf(f[x]);
}
bool check(LL v) {
    for (int i = 0 ; i < n + 2 ; ++ i)
        f[i] = i;
    for (int i = 0 ; i < n + 2 ; ++ i)
        for (int j = i + 1 ; j < n + 2 ; ++ j) {
            if (g[i][j] <= v / 4) {
                f[getf(i)] = getf(j);
            }
        }
    if (getf(n) == getf(n + 1)) {
        I = n , J = n + 1;
        return 1;
    }
    for (int i = 0 ; i < n + 2 ; ++ i)
        for (int j = i + 1 ; j < n + 2 ; ++ j) {
            if (g[i][j] <= v) {
                if (getf(i) == getf(n) && getf(j) == getf(n + 1)) {
                    I = i , J = j;
                    return 1;
                }
                if (getf(j) == getf(n) && getf(i) == getf(n + 1)) {
                    I = i , J = j;
                    return 1;
                }                
            }            
        }
    return 0;
}

int main() {
    //  freopen("landscape.in", "r", stdin);
    //  freopen("landscape.out", "w", stdout);

    scanf("%d%d" , &w , &n);
    for (int i = 0 ; i < n ; ++ i)
        scanf("%d%d" , &X[i] , &Y[i]);    
    for (int i = 0 ; i < n ; ++ i) {
        g[n][i] = g[i][n] = (LL)X[i] * X[i];
        g[n + 1][i] = g[i][n + 1] = (LL)(w - X[i]) * (w - X[i]);
        for (int j = i + 1 ; j < n ; ++ j) {
            int dx = X[i] - X[j];
            int dy = Y[j] - Y[i];
            g[i][j] = g[j][i] = (LL)dx * dx + (LL)dy * dy; 
        }
    }
    g[n][n + 1] = g[n + 1][n] = (LL)w * w;
    I = n , J = n + 1;
    LL l = 0 , r = 4e18 , mid;
    while (l < r) {
        mid = l + r >> 1;
        if (check(mid))
            r = mid;
        else
            l = mid + 1;
    }    
    check(r);
    double xx = (X[I] + X[J]) / 2.0;
    double yy = (Y[I] + Y[J]) / 2.0;
    if (I == n && J == n + 1)
        xx = w / 2.0 , yy = 0;
    else if (J == n) {
        xx = X[I] / 2.0 , yy = Y[I];
    } else if (J == n + 1) {
        xx = X[I] + (w - X[I]) / 2.0 , yy = Y[I];    
    }
    printf("%.3f %.3f\n" , xx , yy);
    return 0;
}
