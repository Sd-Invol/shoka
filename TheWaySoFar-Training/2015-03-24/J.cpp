#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 3e5 + 5;
int first[N], tot;
typedef long long LL;

struct Edge {
    int y;
    LL s1, s2;
    int nex;
}edge[N * 2];

void addedge(int x, int y, LL s1, LL s2) {
    edge[tot] = (Edge) {y, s1, s2, first[x]};
    first[x] = tot++;
}

LL dis1[N], dis2[N], K, val[N];
int flag, bo[N];

int check(LL a, LL b, LL c, LL d) {
    LL y = a - c;
    LL z = d - b;
    if (!flag) {
        if (z == 0) {
            if (y != 0) return 0;
            else return 1;
        }
        if (y % z != 0) return 0;
        K = y / z;
        flag = 1;
        return 1;
    }
    if (y != z * K) return 0;
    return 1;
}

void work() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        first[i] = -1;
    tot = 0;
    for (int i = 1; i <= m; ++i) {
        int x, y, s;
        scanf("%d%d%d", &x, &y, &s);
        addedge(x, y, s, 1);
        addedge(y, x, -s, -1);
    }
    flag = 0;
    for (int i = 1; i <= n; ++i) 
        bo[i] = 0;
    flag = 0;
    queue <int> que;
    for (int i = 1; i <= n; ++i)
        if (!bo[i]) {
            que.push(i);
            dis1[1] = dis2[1] = 0;
            bo[i] = 1;
            while (!que.empty()) {
                int x = que.front();  que.pop();
                for (int k = first[x]; ~k; k = edge[k].nex) {
                    int y = edge[k].y;
                    if (!bo[y]) {
                        dis1[y] = dis1[x] + edge[k].s1;
                        dis2[y] = dis2[x] + edge[k].s2;
                        bo[y] = 1;
                        que.push(y);
                    }
                    else {
                        if (!check(dis1[x] + edge[k].s1, dis2[x] + edge[k].s2, dis1[y], dis2[y])) {
                            puts("NO");
                            return ;
                        }
                    }
                }
            }
        }
    if (!flag) K = 0;
    LL INF = 1e18;
    for (int i = 1; i <= n; ++i) {
        val[i] = dis1[i] + dis2[i] * K;
        if (abs(val[i]) > INF) {
            puts("NO");
            return ;
        }
    }
    puts("YES");
    for (int i = 1; i <= n; ++i) printf("%lld%c", val[i], " \n"[i == n]);
    return ;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        work();
    }
    return 0;
}
