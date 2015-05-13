#include <bits/stdc++.h>
using namespace std;

const int N = 105;
int a[N], b[N], A[N], B[N];

int first[N], tot;

struct Edge {
    int y, nex;
}edge[N << 1];

void addedge(int x, int y) {
    edge[tot] = (Edge) {y, first[x]};
    first[x] = tot++;
}

int cmp(pair<int, int> a, pair<int, int> b) {
    return (a.second + b.first) < (b.second + a.first);
}

void dfs(int x, int fa) {
    for (int k = first[x]; ~k; k = edge[k].nex) {
        int y = edge[k].y;
        if (y != fa) dfs(y, x);
    }
    static pair<int, int> p[105];
    int n = 0;
    for (int k = first[x]; k != -1; k = edge[k].nex) {
        int y = edge[k].y;
        if (y != fa)
            p[n++] = make_pair(A[y], B[y]);
    }
    sort(p, p + n, cmp);
    A[x] = max(a[x], b[x]), B[x] = b[x];
    int res = A[x] - B[x];
    for (int i = 0; i < n; ++i) {
        if (res < p[i].first) {
            A[x] += p[i].first - res;
            res = p[i].first;
        }
        B[x] += p[i].second;
        res -= p[i].second;
    }
}

int main() {
    int n;
    while (scanf("%d", &n), n) {
        memset(first, -1, sizeof(first));
        tot = 0;
        for (int i = 1; i <= n; ++i) {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            a[i] = x;
            b[i] = y + z;
        }
        for (int i = 1; i < n; ++i) {
            int x, y;
            scanf("%d%d", &x, &y);
            addedge(x, y);
            addedge(y, x);
        }
        int ans = 1 << 30;
        for (int i = 1; i <= n; ++i) {
            dfs(i, 0);
            ans = min(ans, A[i]);
        }
        static int ca = 0;
        printf("Case %d: %d\n", ++ca, ans);
    }
    return 0;
}
