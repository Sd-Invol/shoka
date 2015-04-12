#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 200005;
int n;
pair<int , int> a[N];
int xx[N], yy[N], first[N * 2], tot;
LL dis[N * 2];

struct Edge {
    int y, s, nex;
}edge[N * 20];

void addedge(int x, int y, int s) {
    edge[tot] = (Edge) {y, s, first[x]};
    first[x] = tot++;
}

void add(int x, int y, int s) {
    addedge(x, y, s);
    addedge(y, x, s);
}

priority_queue<pair<LL, int> > que;

int main() {
    int i , j , x , y;
    scanf("%d",&n);
    tot = 0;
    memset(first, -1, sizeof(first));
    for (int i = 1; i <= n ; ++ i) {  
        scanf("%d%d",&x,&y);
        a[i] = make_pair(x , y);
        xx[i] = x;
        yy[i] = y;
    }
    sort(xx + 1, xx + 1 + n);
    sort(yy + 1, yy + 1 + n);
    int nx = unique(xx + 1, xx + 1 + n) - xx - 1;
    int ny = unique(yy + 1, yy + 1 + n) - yy - 1;
    for (int i = 1; i <= n; ++i) {
        a[i].first = lower_bound(xx + 1, xx + 1 + nx, a[i].first) - xx;
        a[i].second = lower_bound(yy + 1, yy + 1 + ny, a[i].second) - yy;
        add(a[i].first, a[i].second + nx, 0);
    }
    for (int i = 1; i < nx; ++i) {
        add(i, i + 1, abs(xx[i] - xx[i + 1]));
    }
    for (int i = 1; i < ny; ++i)
        add(i + nx, i + 1 + nx, abs(yy[i] - yy[i + 1]));
    memset(dis, 63, sizeof(dis));
    dis[a[1].first] = 0;  
    que.push(make_pair(-dis[a[1].first], a[1].first));
    static int bo[N * 2];
    while (!que.empty()) {
        int x = que.top().second; que.pop();
        if (bo[x]) continue;
        bo[x] = 1;
        for (int k = first[x]; ~k; k = edge[k].nex)
            if (dis[edge[k].y] > dis[x] + edge[k].s) {
                int y = edge[k].y;
                dis[y] = dis[x] + edge[k].s;
                que.push(make_pair(-dis[y], y));
            }
    }
    printf("%lld\n", dis[a[n].first]);
    return 0;
}
