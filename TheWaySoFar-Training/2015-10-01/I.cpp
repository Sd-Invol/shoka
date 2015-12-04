#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cctype>
#include <string>
#include <queue>
using namespace std;

const int N = 1e5 + 5;
const int M = 1e6 + 5;
typedef long long LL;

pair<int, int> edge[M];
int dis[N];
int f[N];

int find(int x) {
    if (f[x] != x) f[x] = find(f[x]);
    return f[x];
}

LL solve1(int n, int m, int a, int b) {
    int ans = a;
    for (int i = 0; i <= n + 1; ++i) {
        f[i] = i;
        dis[i] = -1;
    }
    dis[1] = 0;
    queue<int> que;
    que.push(1);
    while (!que.empty()) {
        int x = que.front(); que.pop();
        int k1 = lower_bound(edge, edge + m, make_pair(x, -1)) - edge;
        int k2 = lower_bound(edge, edge + m, make_pair(x + 1, -1)) - edge;
        int s = find(1); 
        for (int i = k1; i < k2; ++i) {
            int y = edge[i].second;
            while (s < y) {
                if (dis[s] == -1) {
                    dis[s] = dis[x] + 1;
                    que.push(s);
                }
                f[find(s)] = find(s + 1);
                s = find(s);
            }
            if (s == y) s = find(s + 1);
        }
        while (s <= n) {
            if (dis[s] == -1) {
                dis[s] = dis[x] + 1;
                que.push(s);
            }
            f[find(s)] = find(s + 1);
            s = find(s);
        }
    }
    if (dis[n] == -1) return ans;
    else return min((LL)ans, (LL)dis[n] * b);
}

LL solve2(int n, int m, int a, int b) {
    int ans = b;
    for (int i = 1; i <= n; ++i) dis[i] = -1;
    dis[1] = 0;
    queue<int> que;
    que.push(1);
    while (!que.empty()) {
        int x = que.front(); que.pop();
        int k1 = lower_bound(edge, edge + m, make_pair(x, -1)) - edge;
        int k2 = lower_bound(edge, edge + m, make_pair(x + 1, -1)) - edge;
        for (int i = k1; i < k2; ++i)
            if (dis[edge[i].second] == -1) {
                dis[edge[i].second] = dis[x] + 1;
                que.push(edge[i].second);
            }
    }
    if (dis[n] == -1) return ans;
    else return min((LL)ans, (LL)dis[n] * a);
}

int main() {
    int n, m, a, b;
    while (scanf("%d%d%d%d", &n, &m, &a, &b) == 4) {
        for (int i = 0; i < m; ++i) {
            int x, y;
            scanf("%d%d", &x, &y);
            edge[i * 2] = make_pair(x, y);
            edge[i * 2 + 1] = make_pair(y, x);
        }
        m = m * 2;
        sort(edge, edge + m);
        int flag = 0;
        for (int i = 0; i < m; ++i)
            if (edge[i] == make_pair(1, n)) {
                flag = 1;
                break;
            }
        if (flag) printf("%lld\n", solve1(n, m, a, b));
        else printf("%lld\n", solve2(n, m, a, b));
    }
    return 0;
}