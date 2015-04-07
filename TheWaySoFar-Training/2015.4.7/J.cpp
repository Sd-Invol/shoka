#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int n, m;
const int N = 1005;
int a[N][N], mark[N][N];
int f[N * N];
const int C[4] = {1, -1, 0, 0};
const int D[4] = {0, 0, 1, -1};

int gett(int x, int y) {
    return ((x - 1) * m + y);
}

int find(int x) {
    if (f[x] != x) f[x] = find(f[x]);
    return f[x];
}

int r;

void union_f(int x, int y) {
    f[find(x)] = find(y);
}

int check(int x) {
    for (int i = 0; i <= n * m + 1; ++i) f[i] = i;
    for (int i = 1; i <= m; ++i) {
        if (a[1][i] < x) union_f(mark[1][i], 0);
        if (a[n][i] < x) union_f(mark[n][i], r + 1);
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (a[i][j] < x) {
                for (int k = 0; k < 4; ++k) {
                    int xx = i + C[k], yy = j + D[k];
                    if (xx > 0 && xx <= n && yy > 0 && yy <= m && a[xx][yy] < x)
                        union_f(mark[i][j], mark[xx][yy]);
                }
            }
    if (find(0) == find(r + 1)) return 1;
    else return 0;
}

int main() {
    scanf("%d%d", &n, &m);
    int mx = 0, mn = 1 << 30;
    r = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            int &x = a[i][j];
            scanf("%d", &x);
            mx = max(mx, x);
            mn = min(mn, x);
            mark[i][j] = ++r;
        }
    int head = 0, tail = mx - mn + 1;
    while (head < tail - 1) {
        int mid = head + tail >> 1;
        if (check(mid + mn)) tail = mid;
        else head = mid;
    }
    printf("%d\n", tail);
    return 0;
}
