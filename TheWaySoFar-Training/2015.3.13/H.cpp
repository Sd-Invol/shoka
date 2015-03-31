#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 2e5 + 5;

pair<int, int> item[N];

int n, m;
int f[N][11], Gmax[N];

int check(int x) {
    //memset(f, 63, sizeof(f));
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= m; ++j)
            f[i][j] = 1 << 29;
    f[0][0] = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j <= m; ++j) {
            f[i + 1][j] = min(f[i + 1][j], f[i][j]);
            if (item[i + 1].first - item[i + 1].second - f[i][j] >= x)
                f[i + 1][j + 1] = min(f[i + 1][j + 1], f[i][j] + item[i + 1].second);
        }
    for (int i = 1; i <= n; ++i)
        if (Gmax[i] - f[i - 1][m] >= x) return true;
    return false;
}

int main() {
    //freopen("1.txt", "r", stdin);
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i) {
            scanf("%d%d", &item[i].first, &item[i].second);
        }
        sort(item + 1, item + n + 1);
        for (int i = n; i > 0; --i) {
            Gmax[i] = item[i].first - item[i].second;
            if (i != n)
                Gmax[i] = max(Gmax[i + 1], Gmax[i]);
        }
        int l = 0, r = 1000001;
        while (l < r - 1) {
            int mid = l + r >> 1;
            if (check(mid)) l = mid;
            else r = mid;
        }
        printf("%d\n", l);
    }
    return 0;
}
