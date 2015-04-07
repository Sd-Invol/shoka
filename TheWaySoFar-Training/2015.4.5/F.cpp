#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <bitset>
#include <queue>
using namespace std;

const int N = 1005;

int first[N], tot, cur[N];

struct Edge {
    int y, s, nex;
}edge[N * 20];

int n, m, S, T;

void addedge(int x, int y, int s) {
    edge[tot] = (Edge) {y, s, first[x]};
    first[x] = tot++;
}

void add(int x, int y, int s) {
    addedge(x, y, s);
    addedge(y, x, 0);
}

int d[N];

int BFS() {
    queue<int> que;
    for (int i = 1; i <= n; ++i) d[i] = -1;
    d[S] = 0;
    que.push(S);
    while (!que.empty()) {
        int x = que.front(); que.pop();
        for (int k = first[x]; ~k; k = edge[k].nex)
            if (edge[k].s && d[edge[k].y] == -1) {
                d[edge[k].y] = d[x] + 1;
                que.push(edge[k].y);
            }
    }
    return d[T] != -1;
}

int maxFlow(int x, int flow) {
    if (x == T) return flow;
    int ans = 0;
    for (int &k = cur[x]; ~k; k = edge[k].nex)
        if (edge[k].s && d[edge[k].y] == d[x] + 1) {
            int y = edge[k].y;
            int tmp = maxFlow(y, min(flow - ans, edge[k].s));
            edge[k].s -= tmp;
            edge[k ^ 1].s += tmp;
            ans += tmp;
            if (flow == ans) break;
        }
    if (ans == 0) d[x] = -1;
    return ans;
}

int dis[2][N];

int main() {
    while (scanf("%d%d%d%d", &n, &m, &S, &T), n || m || S || T) {
        memset(first, -1, sizeof(first));
        tot = 0;
        for (int i = 1; i <= m; ++i) {
            int x, y;
            scanf("%d%d", &x, &y);
            add(x, y, 1);
        }
        int ans = 0;
        while (BFS()) {
            memcpy(cur, first, sizeof(cur));
            ans += maxFlow(S, 1 << 30); 
        }
        for (int i = 1; i <= n; ++i) {
            dis[0][i] = 0;
            dis[1][i] = 0;
        }
        queue<pair<int, int> > que;
        que.push(make_pair(S, 0));
        que.push(make_pair(T, 1));
        dis[0][S] = 1;
        dis[1][T] = 1;
        while (!que.empty()) {
            int x = que.front().first;
            int p = que.front().second;
            que.pop();
            for (int k = first[x]; ~k; k = edge[k].nex)
                if (edge[k ^ p].s && dis[p][edge[k].y] == 0) {
                    dis[p][edge[k].y] = 1;
                    que.push(make_pair(edge[k].y, p));
                }
        }
        int num = 0;
        for (int i = 1; i <= n; ++i)
            for (int k = first[i]; ~k; k = edge[k].nex) 
                if (!(k & 1) && edge[k].s) {
                    int y = edge[k].y;
                    if (dis[0][y] && dis[1][i]) ++num;
                }
        if (num) ++ans;
        printf("%d %d\n", ans, num);
    }
    return 0;
}
