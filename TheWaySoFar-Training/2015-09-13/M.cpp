#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
typedef long long LL;
const int N = 50005;
int n , m , pre[N] , mcnt;
struct edge {
    int x , next;
}e[N << 1];
int s[N] , dep[N] , f[16][N];
LL p[16][N];

void dfs(int x , int fa) {
    s[x] = 1 , dep[x] = dep[fa] + 1 , f[0][x] = fa;
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (y != fa) {
            dfs(y , x);
            s[x] += s[y];
        }
    }
    p[0][x] = s[x];
}
int LCA(int x , int y) {
    if (dep[x] < dep[y])
        swap(x , y);
    for (int i = 0 ; i < 16 ; ++ i)
        if (dep[x] - dep[y] >> i & 1)
            x = f[i][x];
    if (x == y) return x;
    for (int i = 15 ; i >= 0 ; -- i)
        if (f[i][x] != f[i][y]) {
            x = f[i][x];
            y = f[i][y];
        }
    return f[0][x];
}

LL cal(int x , int y) {
    ++ x , ++ y;
    int z = LCA(x , y);
    int go = dep[x] - dep[z];
    LL res = 0;
    for (int i = 0 ; i < 16 ; ++ i)
        if (go >> i & 1) {
            res += p[i][x] * 2;
            x = f[i][x];
        }
    res -= go;
    go = dep[y] - dep[z];
    res += (LL)2 * n * go;
    for (int i = 0 ; i < 16 ; ++ i)
        if (go >> i & 1) {
            res -= p[i][y] * 2;
            y = f[i][y];
        }
    res -= go;
    return res;
}
int ca;
void work() {
    if (ca ++) puts("");
    scanf("%d" , &n);
    memset(pre , -1 , sizeof(pre));
    mcnt = 0;
    for (int i = 1 ; i < n ; ++ i) {
        int x , y;
        scanf("%d%d" , &x , &y);
        ++ x , ++ y;
        e[mcnt] = (edge) {y , pre[x]} , pre[x] = mcnt ++;
        e[mcnt] = (edge) {x , pre[y]} , pre[y] = mcnt ++;
    }
    dfs(1 , 0);
    for (int j = 1 ; j < 16 ; ++ j) {
        for (int i = 1 ; i <= n ; ++ i) {
            f[j][i] = f[j - 1][f[j - 1][i]];
            p[j][i] = p[j - 1][i] + p[j - 1][f[j - 1][i]];
        }
    }
    scanf("%d" , &m);
    for (int i = 0 ; i < m ; ++ i) {
        int x , y , w;
        LL res = 0;
        scanf("%d%d" , &w , &x);
        for (int j = 0 ; j < w ; ++ j) {
            scanf("%d" , &y);
            res += cal(x , y);
            x = y;
        }
        printf("%lld.0000\n" , res);
    }
}
int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}
