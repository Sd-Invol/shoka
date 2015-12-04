#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <bitset>
#include <stack>
using namespace std;

const int N = 1e4 + 5;
typedef long long LL;

bitset<N> b1[N], b2[N];
int first[N], tot;
int m1[N], m2[N];

struct Edge {
    int y, nex;
}edge[N << 1];

void addedge(int x, int y) {
    edge[tot] = (Edge) {y, first[x]};
    first[x] = tot++;
}

int color[N], dfn[N], mark[N], sum = 0;;
int cnt = 0;

stack<int> sta;

void dfs(int x) {
    dfn[x] = mark[x] = ++sum;
    sta.push(x);
    for (int k = first[x]; k != -1; k = edge[k].nex) {
        int y = edge[k].y;
        if (dfn[y]) mark[x] = min(mark[x], dfn[y]);
        else {
            dfs(y);
            mark[x] = min(mark[x], mark[y]);
        }
    }
    if (mark[x] == dfn[x]) {
        ++cnt;
        int y;
        do {
            y = sta.top(); sta.pop();
            mark[y] = dfn[y] = 1 << 30;
            color[y] = cnt;
        } while (x != y);
    }
}

void dfs1(int x, int flag) {
    if (dfn[x]) return ;
    dfn[x] = 1;
    for (int k = first[x]; k != -1; k = edge[k].nex)
        if ((k & 1) == flag) {
            dfs1(edge[k].y, flag);
            b1[x] |= b1[edge[k].y];
        }
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    memset(first, -1, sizeof(first));
    tot = 0;
    for (int i = 1; i <= m; ++i) {
        int &x = m1[i], &y = m2[i];
        scanf("%d%d", &x, &y);
        addedge(x, y);
    }
    for (int i = 1; i <= n; ++i)
        if (!dfn[i]) dfs(i);
    for (int i = 1; i <= n; ++i)
        b1[color[i]].set(i);
    memset(first, -1, sizeof(first));
    tot = 0;
    for (int i = 1; i <= m; ++i)
        if (color[m1[i]] != color[m2[i]]) {
            addedge(color[m1[i]], color[m2[i]]);
            addedge(color[m2[i]], color[m1[i]]);
        }
    memset(dfn, 0, sizeof(dfn));
    for (int i = 1; i <= cnt; ++i)
        if (dfn[i] == 0) dfs1(i, 0);
    memset(dfn, 0, sizeof(dfn));
    for (int i = 1; i <= cnt; ++i)
        if (dfn[i] == 0) dfs1(i, 1);
    LL ans = 0;
    for (int i = 1; i <= n; ++i)
        ans += b1[color[i]].count();
    cout << ans << endl;
    return 0;
}
