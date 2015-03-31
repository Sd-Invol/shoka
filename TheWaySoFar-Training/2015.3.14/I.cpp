#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;

const int N = 5005;

int f[5000][5000][2];
int first[N], tot, top[N], rtop[N], degree[N];

struct Edge {
    int y, nex;
}edge[100000];

int n, m, A, B, C, D, r;

vector<int> P[N];

void addedge(int x, int y) {
    edge[tot] = (Edge) {y, first[x]};
    first[x] = tot++;
}

void dfs1(int x) {
    if (degree[x] != 0) return ;
    top[r] = x;
    rtop[x] = r++;
    for (int k = first[x]; ~k; k = edge[k].nex)
        if (--degree[edge[k].y] == 0)
            dfs1(edge[k].y);
    degree[x] = -1;
}

int aa[N], cc[N], n0, n1;

int dp(int x, int y, int s) {
    //printf("%d %d\n", top[x], top[y]);
    //if (x > B) return f[x][y][s] = -2;
    //if (y > D) return f[x][y][s] = -2;
    if (x == B && y == D) {
        f[x][y][s] = 0;
        return 0;
    }
    if (f[x][y][s] != -1) return f[x][y][s];
    int ret = 1 << 30;
    if (x == B || (x >= y && y != D)) {
        int X = top[y];
        for (int k = first[X]; ~k; k = edge[k].nex) {
            int yy = edge[k].y;
            if (s == 1 && rtop[yy] == x) continue;
            int K = dp(x, rtop[yy], x == y);
            if (K == -2) continue;
            ret = min(ret, K + 1);
        }
    }
    if (y == D || (y >= x && x != B)){
        int X = top[x];
        for (int k = first[X]; ~k; k = edge[k].nex) {
            int xx = edge[k].y;
            if (s == 1 && rtop[xx] == y) continue;
            int K = dp(rtop[xx], y, x == y);
            if (K == -2) continue;
            ret = min(ret, K + 1);
        }
    }
    if (ret == (1 << 30)) f[x][y][s] = -2;
    else f[x][y][s] = ret;
    return f[x][y][s];
}

void dfs(int x, int y, int s) {
    if (x == B && y == D) 
        return ;
    if (x == B || (x >= y && y != D)) {
        int X = top[y];
        for (int k = first[X]; ~k; k = edge[k].nex) {
            int yy = edge[k].y;
            if (s == 1 && rtop[yy] == x) continue;
            int K = dp(x, rtop[yy], x == y);
            if (K == -2) continue;
            if (K + 1 == f[x][y][s]) {
                cc[++n1] = yy;
                dfs(x, rtop[yy], x == y);
                return ;
            }
        }
    }
    if (y == D || (y >= x && x != B)) {
        int X = top[x];
        for (int k = first[X]; ~k; k = edge[k].nex) {
            int xx = edge[k].y;
            if (s == 1 && rtop[xx] == y) continue;
            int K = dp(rtop[xx], y, x == y);
            if (K == -2) continue;
            if (K + 1 == f[x][y][s]) {
                aa[++n0] = xx;
                dfs(rtop[xx], y, x == y);
                return ;
            }
        }
    }
}

int main() {
    freopen("two-paths.in", "r", stdin);
    freopen("two-paths.out", "w", stdout);
    //cout << (sizeof(f) + sizeof(T) + sizeof(edge) + sizeof(pre)) / 1024 / 1024 << endl;
    int n, m;
    scanf("%d%d", &n, &m);
    memset(f, -1, sizeof(f));
    memset(first, -1, sizeof(first));
    for (int i = 1; i <= m; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        --x; --y;
        addedge(x, y);
        ++degree[y];
    }
    scanf("%d%d%d%d", &A, &B, &C, &D);
    --A;  --B; --C; -- D;
    for (int i = 0; i < n; ++i) dfs1(i);
    A = rtop[A], B = rtop[B], C = rtop[C], D = rtop[D];
    dp(A, C, 0);
    if (f[A][C][0] == -2) {
        puts("NO");
        return 0;
    }
    puts("YES");
    aa[++n0] = top[A], cc[++n1] = top[C];
    dfs(A, C, 0);
    printf("%d\n", n0);
    for (int i = 1; i <= n0; ++i)
        printf("%d%c", aa[i] + 1, " \n"[i == n0]);
    printf("%d\n", n1);
    for (int i = 1; i <= n1; ++i)
        printf("%d%c", cc[i] + 1, " \n"[i == n1]);
    return 0;
}
