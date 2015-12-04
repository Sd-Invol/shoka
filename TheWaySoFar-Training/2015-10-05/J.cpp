#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <vector>
#include <map>
#include <set>
#include <queue>
using namespace std;

const int N = 1e5 + 5;
int a[N], id[N * 10];
pair<int, int> E[N * 4];
int first[N], tot, bo[N];

struct Edge {
    int y, s, nex;
}edge[N * 20];

void addedge(int x, int y , int s) {
    edge[tot] = (Edge) {y, s, first[x]};
    first[x] = tot++;
}

int dis[N], F[N], degree[N];

typedef long long LL;

int cmp(int aa, int bb) {
    return a[aa] < a[bb];
}

int find(int x) {
    if (F[x] != x) F[x] = find(F[x]);
    return F[x];
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++i) F[i] = i;
    int m;
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        E[i] = make_pair(x, y);
        E[i + m] = make_pair(y, x); 
    }
    m *= 2;
    memset(first, -1, sizeof(first));
    tot = 0;
    sort(E + 1, E + 1 + m);
    m = unique(E + 1, E + 1 + m) - (E + 1);
    for (int i = 1; i <= n; ++i) {
        int t1 = lower_bound(E + 1, E + 1 + m, make_pair(i, -1)) - E;
        int t2 = lower_bound(E + 1, E + 1 + m, make_pair(i + 1, -1)) - E - 1;
        int r = 0;
        id[r++] = i; 
        for (int j = t1; j <= t2; ++j)
            id[r++] = E[j].second;
        sort(id, id + r);
        r = unique(id, id + r) - id;
        sort(id, id + r, cmp);
        for (int j = 1; j < r; ++j)
            if (a[id[j]] == a[id[j - 1]])
                F[find(id[j])] = find(id[j - 1]);
    }
    for (int i = 1; i <= n; ++i) {
        int t1 = lower_bound(E + 1, E + 1 + m, make_pair(i, -1)) - E;
        int t2 = lower_bound(E + 1, E + 1 + m, make_pair(i + 1, -1)) - E - 1;
        int r = 0;
        id[r++] = i; 
        for (int j = t1; j <= t2; ++j)
            id[r++] = E[j].second;
        sort(id, id + r);
        r = unique(id, id + r) - id;
        sort(id, id + r, cmp);
        addedge(0, find(id[0]), 1);
        ++degree[find(id[0])];
        for (int j = 1; j < r; ++j) {
            if (a[id[j - 1]] < a[id[j]]) {
                addedge(find(id[j - 1]), find(id[j]), 1);
                ++degree[find(id[j])];
            }
        }
    }
    queue<int> que;
    memset(dis, 0, sizeof(dis));
    dis[find(0)] = 0;
    que.push(find(0));
    while (!que.empty()) {
        int x = que.front(); que.pop();
        for (int k = first[x]; k != -1; k = edge[k].nex) {
            int y = edge[k].y;
            if (dis[y] < dis[x] + edge[k].s) {
                dis[y] = dis[x] + edge[k].s;
            }
            if (--degree[y] == 0) {
                que.push(y);
            }
        }
    }
    long long ans = 0, mn = 0;
    for (int i = 1; i <= n; ++i) {
        int k = dis[find(i)];
        ans += k;
        mn = min(mn, (LL)k);
        //     printf("%d %d\n", i, dis[i]);
    }
    cout << (ans - mn * n) << endl;
    return 0;
}
