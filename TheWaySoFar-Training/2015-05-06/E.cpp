#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int f[2005][2005];
int n, m, a, q;

pair<int, int> get_pos(int x, int y) {
    return make_pair(x + y, x - y + m);
}

int get_sum(int x1, int y1, int x2, int y2) {
    if (x1 < 1) x1 = 1;
    if (y1 < 1) y1 = 1;
    if (x2 > n + m) x2 = n + m;
    if (y2 > n + m) y2 = n + m;
    return f[x2][y2] - f[x1 - 1][y2] - f[x2][y1 - 1] + f[x1 - 1][y1 - 1];
}

int main() {
    while (scanf("%d%d%d%d", &n, &m, &a, &q), n || m || a || q) {
        for (int i = 1; i <= n + m; ++i)
            for (int j = 1; j <= m + n; ++j)
                f[i][j] = 0;
        for (int i = 1; i <= a; ++i) {
            int x, y;
            scanf("%d%d", &x, &y);
            pair<int, int> pos = get_pos(x, y);
            f[pos.first][pos.second]++;
        }
        for (int i = 1; i <= n + m; ++i)
            for (int j = 1; j <= n + m; ++j)
                f[i][j] += f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1];
        static int ca = 0;
        printf("Case %d:\n", ++ca);
        for (int i = 1; i <= q; ++i) {
            int maxdis;
            scanf("%d", &maxdis);
            int maxnum = 0;
            pair<int, int> pos = make_pair(1 << 30, 1 << 30);
            for (int j = 1; j <= n; ++j)
                for (int k = 1; k <= m; ++k) {
                    pair<int, int> pos1 = get_pos(j, k);
                    int ret = get_sum(pos1.first - maxdis,  pos1.second - maxdis, pos1.first + maxdis, pos1.second + maxdis);
                    
                    if (ret > maxnum) {
                        maxnum = ret;
                        pos = make_pair(k, j);
                    }
                    else if (ret == maxnum) {
                        pos = min(pos, make_pair(k, j));
                    }
                }
            printf("%d (%d,%d)\n", maxnum, pos.second, pos.first);
        }
    }
    return 0;
}
