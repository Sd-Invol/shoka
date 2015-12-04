#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cctype>
#include <string>
#include <queue>
using namespace std;

const int N = 2005;
const int M = 1000005; 
int w[N], p[N];
int first[N], b[N];
int m1[M], m2[M], tot;

struct Edge {
    int y, s, nex;
}edge[M];

int color[N];

void col(int x, int s) {
    if (color[x] != -1) return ;
    color[x] = s;
    for (int k = first[x]; k != -1; k = edge[k].nex)
        col(edge[k].y, s ^ 1);
}

int S, T;

void addedge(int x, int y, int s) {
    edge[tot] = (Edge) {y, s, first[x]};
    first[x] = tot++;
}

void add(int x, int y, int s) {
    // printf("%d %d %d\n", x, y, s);
    addedge(x, y, s);
    addedge(y, x, 0);
}

int d[N];

int bfs() {
    memset(d, -1, sizeof(d));
    queue<int> que;
    que.push(S);
    d[S] = 1;
    while (!que.empty()) {
        int x = que.front(); que.pop();
        for (int k = first[x]; k != -1; k = edge[k].nex) {
            int y = edge[k].y;
            if (d[y] == -1 && edge[k].s) {
                d[y] = d[x] + 1;
                que.push(y);
            }
        }
    }
    return d[T] != -1;
}

int cur[N];

int dfs(int x, int flow) {
    if (x == T) return flow;
    int ans = 0;
    for (int &k = cur[x]; k != -1; k = edge[k].nex) {
        int y = edge[k].y;
        if (d[y] == d[x] + 1 && edge[k].s) {
            int tmp = dfs(y, min(flow - ans, edge[k].s));
            edge[k].s -= tmp;
            edge[k ^ 1].s += tmp;
            ans += tmp;
            if (ans == flow) return ans;
        }
    }
    if (ans == 0) d[x] = -1;
    return ans;
}

int mark[N];

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) == 2) {
        for (int i = 1; i <= n; ++i)
            scanf("%d", &w[i]);
        for (int i = 1; i <= n; ++i)
            scanf("%d", &p[i]);
        memset(first, -1, sizeof(first));
        memset(color, -1, sizeof(color));
        tot = 0;
        for (int i = 1; i <= m; ++i) {
            int x, y;
            scanf("%d%d", &x, &y);
            m1[i] = x;  m2[i] = y;
            addedge(x, y, 0);
            addedge(y, x, 0);
        }
        for (int i = 1; i <= n; ++i)
            col(i, 0);
        memset(first, -1, sizeof(first));
        tot = 0;
        S = n * 2 + 1;
        T = S + 1;
        for (int i = 1; i <= n; ++i)
            add(i, i + n, w[i]);
        for (int i = 1; i <= n; ++i)
            if (p[i] != 3) {
                if ((color[i] == 0 && p[i] == 1) ||
                    (color[i] == 1 && p[i] == 2)) {
                    add(S, i, 1 << 30);
                    mark[i] = 0;
                }
                else {
                    add(i + n, T, 1 << 30);
                    mark[i] = 2;
                }
            }
            else mark[i] = 1;
        for (int i = 1; i <= m; ++i) {
            // printf("%d %d\n", mark[m1[i]], mark[m2[i]]);
            if (mark[m1[i]] == 1 && mark[m2[i]] == 1) {
                if (color[m1[i]] == 1) swap(m1[i], m2[i]);
                add(m1[i] + n, m2[i], 1 << 30);
                add(m2[i] + n, m1[i], 1 << 30);
            }
            else {
                if (mark[m1[i]] > mark[m2[i]])
                    swap(m1[i], m2[i]);
                
                add(m1[i] + n, m2[i], 1 << 30);
                //printf("%d %d\n", m1[i], m2[i]);
            }
        }
        int ans = 0;
        while (bfs()) {
            memcpy(cur, first, sizeof(cur));
            ans += dfs(S, 1 << 30);
        }
        printf("%d\n", ans);
    }
    return 0;
}