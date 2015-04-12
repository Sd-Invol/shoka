#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
using namespace std;

const int C[4] = {0, 0, 1, -1};
const int D[4] = {1, -1, 0, 0};

set<pair<int, int> > visit[20];

struct Point {
    int x, y, mask, dis;
    
    const int operator < (const Point &a) const {
        return dis > a.dis;
    }
};
    
    
map<pair<int, int>, int> ext;
priority_queue<Point> que;
map<pair<int, int>, int> vi[20];

int n, m;
int xx[20], yy[20];

int getDis(int x, int y, int num) {
    static int p[20];
    int ans = 0, r = 0;
    for (int i = 0; i < n; ++i)
        p[r++] = abs(x - xx[i]) + abs(y - yy[i]);
    sort(p, p + r);
    for (int i = 0; i < num; ++i)
        ans += p[i];
    return ans;
}

int S, T, tot, etot;
int first[10000];

struct Edge {
    int y, s1, s2, nex;
}edge[3000000];

void addedge(int x, int y, int s1, int s2) {
    edge[etot] = (Edge) {y, s1, s2, first[x]};
    first[x] = etot++;
}

void add(int x, int y, int s1, int s2) {
    addedge(x, y, s1, s2);
    addedge(y, x, 0, -s2);
}

int check(int &ans) {
    static int dis1[10000], dis2[10000], bo[10000];
    static int pre[10000], prd[10000];
    for (int i = 1; i <= T; ++i) {
        dis1[i] = 0;
        dis2[i] = 1 << 30;
        bo[i] = 0;
    }
    queue<int> que;
    que.push(S);
    dis1[S] = 1 << 30;
    dis2[S] = 0;
    while (!que.empty()) {
        int x = que.front(); que.pop();
        bo[x] = 0;
        for (int k = first[x]; ~k; k = edge[k].nex) {
            int y = edge[k].y;
            if (edge[k].s1 && dis2[y] > dis2[x] + edge[k].s2) {
                dis2[y] = dis2[x] + edge[k].s2;
                pre[y] = x;
                prd[y] = k;
                dis1[y] = min(dis1[x], edge[k].s1);
                if (!bo[y]) {
                    bo[y] = 1;
                    que.push(y);
                }
            }
        }
    }
    if (dis1[T] == 0) return 0;
    ans += dis1[T] * dis2[T];
    for (int x = T; x != S; x = pre[x]) {
        edge[prd[x]].s1 -= dis1[T];
        edge[prd[x] ^ 1].s1 += dis1[T];
    }
    return 1;
}

void costflow() {
    static int table[20];
    memset(table, 0, sizeof(table));
    for (int i = 1; i <= m; ++i) {
        int c;
        scanf("%d", &c);
        ++table[c];
    }
    tot = n;
    etot = 0;
    memset(first, -1, sizeof(first));
    for (int i = 1; i <= n; ++i)
        for (map<pair<int, int>, int>::iterator it = vi[i].begin();
             it != vi[i].end(); ++it) {
            int x = it -> first.first, y = it -> first.second, dis = it -> second;
            int flag = 0;
            for (int j = 0; j < n; ++j)
                if (x == xx[j] && y == yy[j])
                    flag = 1;
            if (flag) continue;
            pair<int, int> tmp = make_pair(x, y);
            if (!ext.count(tmp))
                ext[tmp] = ++tot;
            add(i, ext[tmp], 1, dis);
            //printf("%d %d %d %d\n", i, x, y, dis);
        }
    S = tot + 1, T = tot + 2;
    for (int i = n + 1; i <= tot; ++i)
        add(i, T, 1, 0);
    for (int i = 1; i <= n; ++i)
        add(S, i, table[i], 0);
    int ans = 0;
    while (check(ans));
    printf("%d\n", ans);
}

void getPoint() {
    while (!que.empty()) {
        Point tmp = que.top(); que.pop();
        int num = __builtin_popcount(tmp.mask);
        if (vi[num].size() >= n + m) continue;
        if (tmp.x < 0 || tmp.y < 0) continue;
        if (tmp.x > 5000 || tmp.y > 5000) continue;
        if (vi[num].count(make_pair(tmp.x, tmp.y)))
            continue;
        vi[num][make_pair(tmp.x, tmp.y)] = tmp.dis;
        for (int k = 0; k < 4; ++k) {
            int px = tmp.x + C[k], py = tmp.y + D[k];
            if (px < 0 || py < 0) continue;
            if (px > 5000 || py > 5000) continue;
            if (visit[num].count(make_pair(px, py)))
                continue;
            visit[num].insert(make_pair(px, py));
            que.push((Point){px, py, tmp.mask, getDis(px, py, num)});
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i)
        scanf("%d%d", &xx[i], &yy[i]);
    for (int mask = 1; mask < 1 << n; ++mask) {
        static int p[20];
        int r = 0, x = 0, y = 0;
        for (int i = 0; i < n; ++i)
            if (mask >> i & 1) p[r++] = xx[i];
        sort(p, p + r);
        x = p[(r + 1) / 2 - 1];
        r = 0;
        for (int i = 0; i < n; ++i)
            if (mask >> i & 1) p[r++] = yy[i];
        sort(p , p + r);
        y = p[(r + 1) / 2 - 1];
        int num = __builtin_popcount(mask);
        que.push((Point){x, y, mask, getDis(x, y, num)});
        visit[num].insert(make_pair(x, y));
    }
    getPoint();
    costflow();
    return 0;
}
