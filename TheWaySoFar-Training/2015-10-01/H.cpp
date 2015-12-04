#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <string>
#include <sstream>
typedef long long LL;
using namespace std;
const int N = 55;

int f[N][N], g[N][N];
int ans[N];
int my[N], bo[N];
int n;

int find(int x) {
    for (int i = 1; i <= n; ++i)
        if (!bo[i] && f[x][i]) {
            bo[i] = 1;
            if (my[i] == -1 || find(my[i])) {
                my[i] = x;
                return 1;
            }
        }
    return 0;
}

int solve(int p) {
    memset(my, -1, sizeof(my));
    int ans = 0;
    for (int i = p; i <= n; ++i) {
        memset(bo, 0, sizeof(bo));
        if (find(i)) ++ans;
    }
    return ans;
}

int main() {
    int m1, m2;
    while (scanf("%d%d%d", &n, &m1, &m2) == 3) {
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                f[i][j] = 1;
        for (int i = 1; i <= m1; ++i) {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            for (int j = 1; j <= n; ++j) {
                if (j >= x && j <= y) {
                    for (int k = 1; k < z; ++k)
                        f[j][k] = 0;
                }
                else {
                    f[j][z] = 0;
                }
            }
        }
        for (int i = 1; i <= m2; ++i) {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            for (int j = 1; j <= n; ++j) {
                if (j >= x && j <= y) {
                    for (int k = z + 1; k <= n; ++k)
                        f[j][k] = 0;
                }
                else {
                    f[j][z] = 0;
                }
            }
        }
        if (solve(1) != n) puts("-1");
        else {
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j)
                    if (f[i][j]) {
                        memcpy(g, f, sizeof(g));
                        for (int k = 1; k <= n; ++k)
                            f[k][j] = 0;
                        if (solve(i + 1) == n - i) {
                            ans[i] = j;
                            break;
                        }
                        memcpy(f, g, sizeof(f));
                    }
            }
            for (int i = 1; i <= n; ++i)
                printf("%d%c", ans[i], " \n"[i == n]);
        }
    }
    return 0;
}