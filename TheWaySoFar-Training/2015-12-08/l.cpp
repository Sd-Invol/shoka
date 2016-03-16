#include <cstdio>
#include <queue>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 1e6 + 5;

typedef long long LL;

int first[N], tot;
int size[N];

struct Edge {
    int y, nex;
}edge[N << 1];

void addedge(int x, int y) {
    edge[tot] = (Edge) {y, first[x]};
    first[x] = tot++;
}

LL f[N], g[N];

int n;

LL pre[N], suf[N], pres[N], sufs[N];

void dfs(int x, int fa) {
    //printf("%d -> %d\n", fa, x);
    f[x] = 0;
    size[x] = 1;
    vector<pair<int, int> > son;
    for (int k = first[x]; k != -1; k = edge[k].nex) {
        int y = edge[k].y;
        if (y != fa) {
            dfs(y, x);
            size[x] += size[y];
            son.push_back(make_pair(-size[y], y));
        }
    }
    if (fa != 0)
        son.push_back(make_pair(-(n - size[x]), -1));
    sort(son.begin(), son.end());
    int m = son.size();
    for (int i = 0, sum = 0; i < m; ++i) {
        int y = son[i].second;
        if (y == -1) continue;
        f[x] += f[y] + (LL)size[y] * (sum + 1);
        sum += size[y] * 2;
    }
    pre[0] = 0;
    pres[0] = 0;
    for (int i = 0; i < m; ++i) {
        int y = son[i].second;
        pre[i + 1] = pre[i] + (LL)(pres[i] * 2 + 1) * (-son[i].first);
        pres[i + 1] = pres[i] + (-son[i].first);
        if (y != -1) pre[i + 1] += f[y];
    }
    suf[m] = 0;
    sufs[m] = 0;
    for (int i = m - 1; i >= 0; --i) {
        int y = son[i].second;
        suf[i] = suf[i + 1] + (LL)(sufs[i + 1] * 2 + 1) * (-son[i].first);
        sufs[i] = sufs[i + 1] + (-son[i].first); 
        if (y != -1) suf[i] += f[y];
    }
    g[x] = pre[m];
    for (int i = 0; i < m; ++i) {
        int y = son[i].second;
        if (y == -1) continue;
        LL tmp = g[y];
        tmp += pre[i] + suf[i + 1];
        tmp += sufs[i + 1] * (pres[i] * 2);
        g[x] = min(g[x], tmp);
    }
}

int main() {
    memset(first, -1, sizeof(first));
    tot = 0;
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        addedge(x, y);
        addedge(y, x);
    }
    dfs(1, 0);
    cout << g[1] << endl;
    // for (int i = 1; i <= n; ++i)
    //    printf("%d %lld %lld\n", i, f[i], g[i]);
    return 0;
}
