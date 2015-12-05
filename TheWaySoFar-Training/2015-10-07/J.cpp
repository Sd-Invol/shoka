#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cassert>
#include <queue>
using namespace std;

const int N = 1e5 + 5;

int first[N], tot, degree[N];
int m1, bo[N], m2, f[N];

struct Edge {
    int y, s, m, nex;
}edge[N * 2];

int mark[N];

int find(int x) {
    if (f[x] != x) f[x] = find(f[x]);
    return f[x];
}

void addedge(int x, int y, int s, int m) {
    edge[tot] = (Edge) {y, s, m, first[x]};
    first[x] = tot++;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, q;
        scanf("%d%d", &n, &q);
        memset(first, -1, sizeof(first));
        memset(degree, 0, sizeof(degree));
        memset(bo, 0, sizeof(bo));
        tot = 0;
        for (int i = 1; i <= n; ++i) {
            int x, y, s;
            scanf("%d%d%d", &x, &y, &s);
            addedge(x, y, s, i == n);
            addedge(y, x, s, i == n);
            ++degree[x];
            ++degree[y];
            if (i == n) {
                m1 = x;
                m2 = s; 
            }
        }
        queue<int> que;
        for (int i = 1; i <= n; ++i)
            if (degree[i] == 1) {
                que.push(i);
                bo[i] = 1;
            }
        for (int i = 1; i <= n; ++i)
            f[i] = i;
        while (!que.empty()) {
            int x = que.front(); que.pop();
            for (int k = first[x]; k != -1; k = edge[k].nex) {
                int y = edge[k].y;
                f[find(x)] = find(y);
                if (!bo[y] && --degree[y] <= 1) {
                    bo[y] = 1;
                    que.push(y);
                }
            }
        }
        vector<pair<int, int> > ver;
        int x = m1;
        ver.push_back(make_pair(m1, m2));
        while (1) {
            int y = 0;
            bo[x] = 1;
            for (int k = first[x]; k != -1; k = edge[k].nex) {
                int yy = edge[k].y;
                if (!bo[yy] && edge[k].m != 1) {
                    ver.push_back(make_pair(yy, edge[k].s));
                    y = yy;
                    break;
                }
            }
            if (y == 0) break;
            x = y;
        }
        // for (int i = 0; i < ver.size(); ++i)
        //    printf("!%d %d\n", ver[i].first, ver[i].second);
        for (int i = 0; i < ver.size(); ++i)
            mark[ver[i].first] = i;
        for (int i = 1; i < ver.size(); ++i)
            ver[i].second += ver[i - 1].second;
        static int ca = 0;
        printf("Case #%d:\n", ++ca);
        while (q--) {
            int x, y;
            scanf("%d%d", &x, &y);
            if (find(x) == find(y)) puts("0");
            else {
                x = mark[find(x)];
                y = mark[find(y)];
                if (x > y) swap(x, y);
                int ans1 = ver[y].second -
                    ver[x].second;
                int ans2 = ver.back().second - ans1;
                if (ans2 < ans1) printf("%d\n", ans1 - ans2);
                else puts("0");
            }
        }
    }
    return 0;
}