#include <bits/stdc++.h>
using namespace std;
const int N = 105;

int grid1[N][N], grid2[N][N];
int f[N][N], n, m, my[N], mx[N];
int vis[N];

int find(int x) {
    for (int i = 1; i <= n; ++i)
        if (!vis[i] && f[x][i]) {
            vis[i] = 1;
            if (my[i] == 0 || find(my[i])) {
                my[i] = x;
                mx[x] = i;
                return 1;
            }
        }
    return 0;
}

int main() {
    freopen("lots.in", "r", stdin);
    freopen("lots.out", "w", stdout);
    while (scanf("%d%d", &n, &m), n || m) {
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) {
                int &ch = grid1[i][j];
                while (ch = getchar(), ch != '.' && ch != 'x' && ch != '?');
        }
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) {
                int &ch = grid2[i][j];
                while (ch = getchar(), ch != '.' && ch != 'x');
        }
        memset(f, 0, sizeof(f));
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j) {
                int flag = 1;
                for (int k = 1; k <= m; ++k)
                    if (grid1[i][k] != '?' && grid2[j][k] != '?' &&
                        grid1[i][k] != grid2[j][k]) flag = 0;
                if (flag) f[i][j] = 1;
            }
        memset(my, 0, sizeof(my));
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            memset(vis, 0, sizeof(vis));
            if (find(i)) ++ans;
        }
        for (int i = 1, p = 1 << 30; i <= n; ++i) {
            int res = 0;
            for (int j = 1; j <= m; ++j)
                res += (grid2[i][j] == 'x');
            if (res > p) {
                ans = 0;
            }
            //printf("%d %d\n", res, p);
            p = res;
        }
        if (ans != n) puts("NO");
        else {
            puts("YES");
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= m; ++j)
                    putchar(grid2[mx[i]][j]);
                puts("");
            }
        }
    }
    return 0;
}
