#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 3e5 + 5;

int S, T, first[N], tot, _S, _T, cur[N];

struct Edge {
    int y, s, nex;
}edge[N * 10];

void addedge(int x, int y, int s) {
    edge[tot] = (Edge) {y, s, first[x]};
    first[x] = tot++;
}

void add(int x, int y, int s) {
    addedge(x, y, s);
    addedge(y, x, 0);
}

int grid[105][1005], mark[105][1005], sign[1005];
int d[N];

int bfs() {
    for (int i = 1; i <= T; ++i)
        d[i] = -1;
    d[S] = 0;
    static int que[N];
    int head = 1, tail = 1;
    que[1] = S;
    while (head <= tail) {
        int x = que[head++];
        for (int k = first[x]; ~k; k = edge[k].nex)
            if (edge[k].s && d[edge[k].y] == -1) {
                d[edge[k].y] = d[x] + 1;
                que[++tail] = edge[k].y;
            }
    }
    return d[T] != -1;
}

int dfs(int x, int flow) {
    if (x == T) return flow;
    int ans = 0;
    for (int &k = cur[x]; ~k; k = edge[k].nex) {
        int y = edge[k].y;
        if (d[x] + 1 == d[y] && edge[k].s) {
            int tmp = dfs(y, min(edge[k].s, flow - ans));
            ans += tmp;
            edge[k].s -= tmp;
            edge[k ^ 1].s += tmp;
            if (flow == ans) break;
        }
    }
    if (cur[x] == -1) d[x] = -1;
    return ans;
}

struct sw {
    int a, b, num;
};

int main() {
    int n, K, Q, sum = 0;
    memset(first, -1, sizeof(first));
    tot = 0;
    scanf("%d%d%d", &n, &K, &Q);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= Q; ++j) {
            int &ch = grid[i][j];
            while (ch = getchar(), !isdigit(ch));
            ch -= '0';
            mark[i][j] = ++sum;
        }
    _S = sum * 2 + (Q - 1) * 2 + 1;
    _T = _S + 1;
    S = _T + 1;
    T = S + 1;
    add(S, _S, K);
    add(_T, T, K);
    for (int i = 1; i < Q; ++i) {
        sign[i] = sum * 2 + (i - 1) * 2 + 1;
        add(sign[i], sign[i] + 1, 1);
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= Q; ++j)
            if (grid[i][j]) {
                if (j == 1) add(_S, mark[i][j], 1);
                else add(sign[j - 1] + 1, mark[i][j], 1);
                if (j == Q) add(mark[i][j] + sum, _T, 1);
                else {
                    add(mark[i][j] + sum, sign[j], 1);
                    if (grid[i][j + 1])
                        add(mark[i][j] + sum, mark[i][j + 1], 1);
                }
                add(mark[i][j], mark[i][j] + sum, 1);
            }
    int ans = 0;
    while (bfs()) {
        for (int i = 1; i <= T; ++i) cur[i] = first[i];
        ans += dfs(S, 1 << 30);
    }
    if (ans != K) puts("FAIL");
    else {
        puts("WIN");
        vector<int> ver;
        for (int k = first[_S]; ~k; k = edge[k].nex)
            if (edge[k].y <= sum && edge[k].s == 0) {
                ver.push_back((edge[k].y + Q - 1) / Q);
            }
        for (int i = 0; i < ver.size(); ++i)
            printf("%d%c", ver[i], " \n"[i == K - 1]);
        vector<sw> ver1;
        for (int i = 1; i < Q; ++i) {
            int x = -1, y = -1;
            for (int k = first[sign[i]]; ~k; k = edge[k].nex)
                if (edge[k ^ 1].s == 0 && edge[k].y <= sum * 2)
                    x = (edge[k].y - sum - i) / Q + 1; 
            for (int k = first[sign[i] + 1]; ~k; k = edge[k].nex)
                if (edge[k].s == 0 && edge[k].y <= sum)
                    y = (edge[k].y - i - 1) / Q + 1;
            if (x != -1) ver1.push_back((sw){x, y, i});
        }
        printf("%d\n", (int)ver1.size());
        for (int i = 0; i < ver1.size(); ++i)
            printf("%d %d %d\n", ver1[i].num, ver1[i].a, ver1[i].b);
    }
    return 0;
}
