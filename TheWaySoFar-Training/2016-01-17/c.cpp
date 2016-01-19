#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack> 
using namespace std;

const int N = 3e5 + 5;
const int LIMIT = 2e9;

int first[N], tot;
int bo[N], degree[N];

struct Edge {
    int y, s, nex;
}edge[N * 10];

void addedge(int x, int y, int s) {
    edge[tot] = (Edge) {y, s, first[x]};
    first[x] = tot++;
}

int n, m, r;

typedef long long LL;

int op[N], fr[N], ed[N], val[N];
int dfn[N], mark[N], color[N];
int cnt, ltot;
stack<int> sta;

void dfs(int x) {
    dfn[x] = mark[x] = ++ltot;
    sta.push(x);
    for (int k = first[x]; k != -1; k = edge[k].nex) {
        int y = edge[k].y;
        if (!dfn[y]) {
            dfs(y);
        }
        mark[x] = min(mark[x], mark[y]);
    }
    if (mark[x] == dfn[x]) {
        ++cnt;
        int y;
        do {
            y = sta.top();
            sta.pop();
            color[y] = cnt;
            mark[y] = 1 << 30;
        } while (y != x);
    }
}

int scc_num() {
    memset(dfn, 0, sizeof(dfn));
    ltot = 0;
    cnt = 0;
    for (int i = 1; i <= m + r; ++i)
        if (!dfn[i]) dfs(i);
    return cnt;
}

int dis[N];

int main() {
    scanf("%d%d", &n, &m);
    memset(first, -1, sizeof(first));
    tot = 0;
    r = 0;
    for (int i = 1; i <= n; ++i) {
        int x1, x2, y1, y2;
        scanf("%d%d%d%d%d", &op[i], &x1, &x2, &y1, &y2);
        if (x1 == 0) fr[i] = x2;
        else {
            val[(++r) + m] = x2;
            fr[i] = r + m;
        }
        if (y1 == 0) ed[i] = y2;
        else {
            val[(++r) + m] = y2;
            ed[i] = r + m;
        }
        
    }
    for (int i = 1; i <= n; ++i)
        if (op[i] == 0) {
            addedge(fr[i], ed[i], 0);
        }
    int n1 = scc_num();
    for (int i = 1; i <= n; ++i)
        if (op[i] == 1)
            addedge(fr[i], ed[i], 0);
    int n2 = scc_num();
    if (n1 != n2) {
        puts("NO");
        return 0;
    }
    memset(first, -1, sizeof(first));
    for (int i = 1; i <= n; ++i)
        if (color[fr[i]] != color[ed[i]]) {
            addedge(color[fr[i]], color[ed[i]], op[i]);
            ++degree[color[ed[i]]];
        }
    for (int i = m + 1; i <= m + r; ++i)
        bo[color[i]] = i;
    queue<int> que;
    for (int i = 1; i <= n2; ++i)
        if (degree[i] == 0) {
            que.push(i);
            dis[i] = -LIMIT;
        }
        else dis[i] = -LIMIT;
    while (!que.empty()) {
        int x = que.front(); que.pop();
        if (bo[x] != 0) {
            if (val[bo[x]] < dis[x]) {
                puts("NO");
                return 0;
            }
            dis[x] = val[bo[x]];
        }
        for (int k = first[x]; k != -1; k = edge[k].nex) {
            int y = edge[k].y;
            dis[y] = max(dis[y], dis[x] + edge[k].s);
            if (--degree[y] == 0) {
                que.push(y);
            }
        }
    }
    for (int i = m + 1; i <= m + r; ++i)
        if (dis[color[i]] != val[i]) {
            puts("NO");
            return 0;
        }
    for (int i = 1; i <= n; ++i)
        if (dis[color[fr[i]]] + op[i] <= dis[color[ed[i]]]) {
        }
        else {
            puts("NO");
            return 0;
        }
    puts("YES");
    for (int i = 1; i <= m; ++i)
        printf("%d\n", dis[color[i]]);
}
