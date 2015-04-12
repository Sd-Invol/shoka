#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 905;

int S, T;
int first[N], tot;

struct Edge {
    int y, s1, s2, nex;
}edge[1000000];

void addedge(int x, int y, int s1, int s2) {
    edge[tot] = (Edge) {y, s1, s2, first[x]};
    first[x] = tot++;
}

void add(int x, int y, int s1, int s2) {
    addedge(x, y, s1, s2);
    addedge(y, x, 0, -s2);
}

int check() {
    static int bo[N], dis1[N], dis2[N];
    static int pre[N], prd[N];
    for (int i = 1; i <= T; ++i) {
        bo[i] = 0;
        dis1[i] = 0;
        dis2[i] = 1 << 30;
    }
    queue<int> que;
    dis1[S] = 1 << 30, dis2[S] = 0;
    que.push(S);
    while (!que.empty()) {
        int x = que.front(); que.pop();
        bo[x] = 0;
        for (int k = first[x]; ~k; k = edge[k].nex) {
            int y = edge[k].y;
            if (edge[k].s1 && dis2[y] > dis2[x] + edge[k].s2) {
                dis2[y] = dis2[x] + edge[k].s2;
                dis1[y] = min(dis1[x], edge[k].s1);
                pre[y] = x;
                prd[y] = k;
                if (!bo[y]) {
                    bo[y] = 1;
                    que.push(y);
                }
            }
        }
    }
    if (dis1[T] == 0) return 0;
    for (int x = T; x != S; x = pre[x]) {
        edge[prd[x]].s1 -= dis1[T];
        edge[prd[x] ^ 1].s1 += dis1[T];
    }
    return 1;
}

vector<int> jobs[N];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    S = m + n + n + 1, T = S + 1;
    memset(first, -1, sizeof(first));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            int ch;
            while (ch = getchar(), !isdigit(ch));
            if (ch == '1') add(j, i + m, 1, 0);
        }
    for (int i = 1; i <= m; ++i)
        add(S, i, 1, 0);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            add(i + m, i + m + n, 1, 2 * j);
    for (int i = 1; i <= n; ++i)
        add(i + m + n, T, 1 << 30, 0);
    while (check());
    for (int i = 1; i <= m; ++i)
        for (int k = first[i]; ~k; k = edge[k].nex)
            if (edge[k].y > m && edge[k].y <= n + m)
                if (edge[k].s1 == 0)
                    jobs[edge[k].y - m].push_back(i);
    for (int i = 1; i <= n; ++i) {
        sort(jobs[i].begin(), jobs[i].end());
        printf("%d", (int)jobs[i].size());
        for (int j = 0; j < jobs[i].size(); ++j)
            printf(" %d", jobs[i][j]);
        puts("");
    }
    return 0; 
}
