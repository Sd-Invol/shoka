#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

int tx[20], tmask[1 << 20];
int LOG[1 << 20], f[1 << 20];
pair<int, int> pre[1 << 20];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        --x;
        --y;
        tx[x] |= 1 << y;
    }
    for (int i = 0; i < n; ++i)
        LOG[1 << i] = i;
    for (int mask = 1; mask < 1 << n; ++mask) {
        int t = mask & (-mask);
        tmask[mask] = tmask[mask ^ t] | tx[LOG[t]];
    }
    memset(f, -1, sizeof(f));
    f[(1 << n) - 1] = 0;
    queue<int> que;
    que.push((1 << n) - 1);
    while (!que.empty()) {
        int x = que.front();
        que.pop();
        for (int y = x; y != 0; y -= y & (-y)) {
            int t = y & -y;
            int mask = tmask[x ^ t];
            //cout << x << " " << t << " " << mask << endl;
            if (f[mask] == -1) {
                f[mask] = f[x] + 1;
                pre[mask] = make_pair(x, LOG[t]);
                que.push(mask);
            }
        }
    }
    if (f[0] == -1) {
        puts("No solution");
    }
    else {
        vector<int> ans;
        for (int x = 0; f[x] != 0; x = pre[x].first) {
            ans.push_back(pre[x].second + 1);
        }
        reverse(ans.begin(), ans.end());
        cout << ans.size() << endl;
        for (int i = 0; i < ans.size(); ++i) {
            printf("%d%c", ans[i], " \n"[i + 1 == (int)ans.size()]);
        }
    }
    return 0;
}
