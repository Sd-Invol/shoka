#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 305;

int n;
int g[N][N] , P[N][N];
vector<int> t[N << 1];
inline int id(int l , int r) {
    return l + r | l != r;
}
int b[20][N][N];

void floyd(int f[][N] , int k) {
    for (int i = 1 ; i <= n ; ++ i)
        for (int j = 1 ; j <= n ; ++ j)
            f[i][j] = min(f[i][j] , f[i][k] + f[k][j]);
}

void add(int l , int r , int top , int bot , int x) {
    int p = id(l , r);
    if (top <= l && r <= bot) {
        t[p].push_back(x);
    } else {
        int mid = l + r >> 1;
        if (top <= mid)
            add(l , mid , top , bot , x);
        if (bot > mid)
            add(mid + 1 , r , top , bot , x);
    }
}

void dfs(int d , int l , int r) {
    int p = id(l , r);
    memcpy(b[d] , g , sizeof(g));
    for (auto &k : t[p])
        floyd(g , k);

    if (l == r) {
        int res = 1 << 30;
        for (int i = 1 ; i <= n ; ++ i)
            for (int j = 1 ; j <= n ; ++ j)
                if (g[i][j] != 0x3f3f3f3f && l != i && l != j && i != j)
                    res = min(res , P[l][i] + g[i][j] + P[j][l]);
        if (res >= 0x3f3f3f3f)
            res = -1;
        printf("%d\n" , res);
    } else {
        int mid = l + r >> 1;
        dfs(d + 1 , l , mid);
        dfs(d + 1 , mid + 1 , r);
    }

    memcpy(g , b[d] , sizeof(g));
}

int main() {
    scanf("%d" , &n);
    for (int i = 1 ; i <= n ; ++ i)
        for (int j = 1 ; j <= n ; ++ j) {
            scanf("%d" , &g[i][j]);
            if (g[i][j] == -1)
                g[i][j] = 0x3f3f3f3f;
        }
    memcpy(P , g , sizeof(P));
    for (int i = 1 ; i <= n ; ++ i) {
        if (i > 1)
            add(1 , n , 1 , i - 1 , i);
        if (i < n)
            add(1 , n , i + 1 , n , i);
    }
    dfs(0 , 1 , n);
    return 0;
}
