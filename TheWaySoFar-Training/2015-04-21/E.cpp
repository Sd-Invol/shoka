#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n;
const int C[4] = {1, -1, 0, 0};
const int D[4] = {0, 0, 1, -1};

map<pair<int, int>, int> ext;

int first[N], tot;

struct Edge {
    int y, nex;
}edge[N * 10];

void addedge(int x, int y) {
    edge[tot] = (Edge) {y, first[x]};
    first[x] = tot++;
}

int dis[N];

int get_short() {
    memset(dis, -1, sizeof(dis));
    queue<int> que;
    que.push(1);
    dis[1] = 0;
    while (!que.empty()) {
        int x = que.front();
        que.pop();
        for (int k = first[x]; ~k; k = edge[k].nex) {
            int y = edge[k].y;
            if (dis[y] == -1) {
                dis[y] = dis[x] + 1;
                que.push(y);
            }
        }
    }
    int K = 1;
    for (int i = 2; i <= n; ++i)
        if (dis[i] > dis[K]) K = i;
    return K;
}

int px[N], py[N];

int main() {
    freopen("partition.in", "r", stdin);
    freopen("partition.out", "w", stdout);
    scanf("%d", &n);
    memset(first, -1, sizeof(first));
    for (int i = 1; i <= n; ++i) {
        int &x = px[i], &y = py[i];
        scanf("%d%d", &x, &y);
        for (int j = 0; j < 4; ++j) {
            int xx = x + C[j], yy = y + D[j];
            pair<int, int> pr = make_pair(xx, yy);
            if (ext.count(pr)) {
                int tmp = ext[pr];
                addedge(tmp, i);
                addedge(i, tmp);
            }
        }
        ext[make_pair(x, y)] = i;
    }
    int t = get_short();
    vector<int > ans;
    memset(dis, -1, sizeof(dis));
    dis[t] = 1;
    int num = 1, maxnum = (n + 1) / 2;
    queue<int> que;
    que.push(t);
    while (!que.empty()) {
        int x = que.front();
        que.pop();
        for (int k = first[x]; ~k; k = edge[k].nex) {
            int y = edge[k].y;
            if (dis[y] == -1) {
                dis[y] = 1;
                if (maxnum == num) ans.push_back(y);
                else que.push(y), ++num;
            }
        }
    }
    printf("%d\n", (int)ans.size());
    for (int i = 0; i < ans.size(); ++i)
        printf("%d %d\n", px[ans[i]], py[ans[i]]);
    return 0;
}
