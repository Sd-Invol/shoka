#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;

int C[1005][1005];
int bo[1005];
LL dis[1005], num[1005];

const int P = 1e9;

int s, t, n;

LL dfs(int x) {
    if (num[x] != -1) return num[x];
    if (x == t) return num[x] = 1;
    num[x] = 0;
    for (int i = 1; i <= n; ++i)
        if (i != x && dis[i] == dis[x] + C[x][i]) {
            num[x] = (num[x] + dfs(i)) % P;
        }
    return num[x];
}

int main() {
    scanf("%d%d%d", &n, &s, &t);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            scanf("%d", &C[i][j]);
    memset(dis, 63, sizeof(dis));
    dis[s] = 0;  num[s] = 1;
    for (int tt = 1; tt <= n; ++tt) {
        int K = -1;
        for (int i = 1; i <= n; ++i)
            if (!bo[i] && (K == -1 || dis[i] < dis[K]))
                K = i;
        if (K == -1) continue;
        bo[K] = 1;
        for (int i = 1; i <= n; ++i)
            if (!bo[i])
                if (dis[i] > dis[K] + C[K][i]) {
                    dis[i] = dis[K] + C[K][i];
                }
    }
    memset(num, -1, sizeof(num));
    cout << dfs(s) << endl;
    return 0;
}
/*

4 2 3
0 1 2 1
1 0 3 2
2 3 0 1
1 2 1 0
 */
