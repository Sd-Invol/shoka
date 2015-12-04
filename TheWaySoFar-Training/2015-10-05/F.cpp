#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <vector>
#include <map>
#include <set>
#include <queue>
using namespace std;

const int N = 205;

struct Edge {
    int y, d, v, nex;
}edge[N * N * 2];

int first[N], tot;

void addedge(int x, int y, int d, int v) {
    edge[tot] = (Edge) {y, d, v, first[x]};
    first[x] = tot++;
}

int dis[1005][N];
double mx[1005];

int main() {
    int n, m, P;
    scanf("%d%d%d", &n, &m, &P);
    memset(first, -1, sizeof(first));
    tot = 0;
    for (int i = 1; i <= m; ++i) {
        int x, y, d, v;
        scanf("%d%d%d%d", &x, &y, &d, &v);
        mx[x] = max(mx[x], (double)v / d);
        mx[y] = max(mx[y], (double)v / d);
        addedge(x, y, d, v);
        addedge(y, x, d, v);
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= P; ++j)
            dis[j][i] = -1;
    dis[0][1] = 0;
    for (int i = 0; i <= P; ++i)
        for (int j = 1; j <= n; ++j)
            if (dis[i][j] != -1) {
                for (int k = first[j]; k != -1; k = edge[k].nex)
                    if (edge[k].d + i <= P && dis[i + edge[k].d][edge[k].y] < dis[i][j] + edge[k].v) {
                        dis[i + edge[k].d][edge[k].y] = dis[i][j] + edge[k].v;
                    }
            }
    double ans = 0;
    //  for (int i = 1; i <= n; ++i)
    //    for (int j = 0; j <= P; ++j)
    //        printf("%d %d %d\n", i, j, dis[j][i]);
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j + j <= P; ++j)
            if (dis[j][i] != -1) {
                ans = max(ans, (double)dis[j][i] * 2 + (double)(P - 2 * j) * mx[i]);
            }
    }
    printf("%.10f\n", ans);
    return 0;
}
