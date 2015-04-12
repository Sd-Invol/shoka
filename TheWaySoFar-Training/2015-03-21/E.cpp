#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int t[3], n;
int h[505], w[505];

vector<int> son[505];

struct Bed {
    int x, y, z;

    int operator < (const Bed &a) const {
        return x * y * z < a.x * a.y * a.z;
    }
};

int ispath(int hi, int wi) {
    if (hi > h[1] || wi > w[1]) return 0;
    static int vis[505];
    memset(vis, 0, sizeof(vis));
    vis[1] = 1;
    queue<int> que;
    que.push(1);
    while (!que.empty()) {
        int x = que.front(); que.pop();
        for (int i = 0; i < son[x].size(); ++i) {
            int y = son[x][i];
            if (hi > h[y] || wi > w[y]) continue;
            if (!vis[y]) {
                vis[y] = 1;
                que.push(y);
            }
        }
    }
    return vis[n];
}

Bed check(int hi) {
    int head = 0, tail = 301;
    while (head < tail - 1) {
        int mid = head + tail >> 1;
        if (ispath(hi, mid)) head = mid;
        else tail = mid;
    }
    Bed ans = (Bed){0, 0, 0};
    if (!ispath(hi, 0)) return ans;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (i != j) {
                int k = 1 + 2 - i - j;
                ans = max(ans, (Bed) {min(hi, t[i]), min(head, t[j]), t[k]});
            }
    return ans;
}

int main() {
    scanf("%d%d%d", &t[0], &t[1], &t[2]);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        int K;
        scanf("%d%d%d", &h[i], &w[i], &K);
        while (K--) {
            int x;
            scanf("%d", &x);
            son[i].push_back(x);
        }
    }
    Bed ans = (Bed){0, 0, 0};
    for (int i = 1; i <= 300; ++i)
        ans = max(check(i), ans);
    printf("%d %d %d\n", ans.x, ans.y, ans.z);
    return 0;
}
