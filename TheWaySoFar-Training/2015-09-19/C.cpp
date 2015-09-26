#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
#include <map>
#include <set>
#include <queue>
using namespace std;
typedef long long LL;
const int N = 20005;
int n , m , pre[N] , mcnt , ca;
struct edge {
    int x , next;
}e[N << 1];
int Lev , f[16][N] , dep[N];
int res[N];

void dfs(int x , int fa) {
    f[0][x] = fa , dep[x] = dep[fa] + 1;
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (y != fa) {
            dfs(y , x);
        }
    }
}

int LCA(int x , int y) {
    if (dep[x] < dep[y])
        swap(x , y);
    for (int i = Lev ; i >= 0 ; -- i)
        if (dep[x] - dep[y] >> i & 1)
            x = f[i][x];
    if (x == y) return y;
    for (int i = Lev ; i >= 0 ; -- i)
        if (f[i][x] != f[i][y]) {
            x = f[i][x];
            y = f[i][y];
        }
    return f[0][y];
}
int ans;
void DFS(int x , int fa) {
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (y != fa) {
            DFS(y , x);
            ans = min(ans , res[y]);
            res[x] += res[y];
        }
    }

}

void work() {
    scanf("%d%d" , &n , &m);
    memset(pre , -1 , sizeof(pre));
    mcnt = 0;
    for (int i = 1 ; i < n ; ++ i) {
        int x , y;
        scanf("%d%d" , &x , &y);
        e[mcnt] = (edge) {x , pre[y]} , pre[y] = mcnt ++;
        e[mcnt] = (edge) {y , pre[x]} , pre[x] = mcnt ++;
    }
    dfs(1 , 0);
    Lev = 0;
    for (int j = 1 ; 1 << j < n ; ++ j) {
        for (int i = 1 ; i <= n ; ++ i) {
            f[j][i] = f[j - 1][f[j - 1][i]];
        }
        Lev = j;
    }
    memset(res , 0 , sizeof(res));
    for (int i = 0 ; i < m - n + 1 ; ++ i) {
        int x , y;
        scanf("%d%d" , &x , &y);
        int z = LCA(x , y);
        ++ res[x] , ++ res[y];
        -- res[z] , -- res[z];
    }
    ans = 1 << 30;
    DFS(1 , 0);
    printf("Case #%d: %d\n" , ++ ca , 1 + ans);
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}
