#include <bits/stdc++.h>
using namespace std;

int n, A, B;
int grid[55][55];
int first[100], tot, S, T;

struct Edge {
    int y, s1, s2, nex;
}edge[100 * 100];
    
void addedge(int x, int y, int s1, int s2) {
    edge[tot] = (Edge) {y, s1, s2, first[x]};
    first[x] = tot++;
}

void add(int x, int y, int s1, int s2) {
    addedge(x, y, s1, s2);
    addedge(y, x, 0, -s2);
}

int check(int &flow, int &cost) {
    static int dis1[100], dis2[100], bo[100];
    static int pre[100], prd[100];
    for (int i = 1; i <= T; ++i) {
        dis1[i] = 0;
        dis2[i] = -(1 << 30);
        bo[i] = 0;
    }
    queue<int> que;
    dis1[S] = 1 << 30;
    dis2[S] = 0;
    que.push(S);
    while (!que.empty()) {
        int x = que.front(); que.pop();
        bo[x] = 0;
        for (int k = first[x]; ~k; k = edge[k].nex) {
            int y = edge[k].y;
            if (edge[k].s1 && dis2[y] < dis2[x] + edge[k].s2) {
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
    flow += dis1[T], cost += dis1[T] * dis2[T];
    for (int x = T; x != S; x = pre[x]) {
        edge[prd[x]].s1 -= dis1[T];
        edge[prd[x] ^ 1].s1 += dis1[T];
    }
    return 1;
}

int numC;

int check(int &x) {
    memset(first, -1, sizeof(first));
    tot = 0;
    S = n * 2 + 1, T = S + 1;
    for (int i = 1; i <= n; ++i)
        add(i + n, i, x * A / B, 0);
    int sum = 0, flow = 0, cost = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            if (grid[i][j] == 'C') {
                add(S, j + n, 1, 0);
                add(i, T, 1, 0);
                ++sum;
            }
            if (grid[i][j] == '.') {
                add(S, j + n, 1, 0);
                add(i, T, 1, 0);
                ++sum;
                ++cost;
                addedge(i, j + n, 0, 1);
                addedge(j + n, i, 1, -1);
            }
        }
    while (check(flow, cost));
    // printf("%d %d %d %d\n", flow, cost, x, sum);
    if (flow != sum) {
        x = numC;
        return 0;
    }
    if (cost + numC < x) {
        x = cost + numC + 1;
        return 0;
    }
    return 1;
}

int main() {
    while (scanf("%d%d%d", &n, &A, &B), n || A || B) {
        int ans = 0;
        numC = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j) {
                int &ch = grid[i][j];
                while (ch = getchar(), ch != '.' && ch != '/' && ch != 'C');
                if (ch == '.') {
                    ++ans;
                }
                if (ch == 'C') {
                    ++ans;
                    ++numC;
                }
            }
        for (; ans >= numC; --ans) 
            if (check(ans)) break;
        static int ca = 0;
        printf("Case %d: ", ++ca);
        if (ans < numC) puts("impossible");
        else printf("%d\n", ans - numC);
    }
    return 0;
}
