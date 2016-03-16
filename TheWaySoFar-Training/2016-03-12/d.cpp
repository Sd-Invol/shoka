#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <bitset>
#include <algorithm>
using namespace std;

bitset<1001> f[2001][2001];
int a[2001];

int main() {
    freopen("decisions.in", "r", stdin);
    freopen("decisions.out", "w", stdout);
    int n;
    while (scanf("%d", &n), n) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
        }
        for (int i = 1; i <= n; ++i) {
            f[i][i - 1].set(0);
            for (int j = i; j <= n; ++j)
                f[i][j] = (f[i][j - 1] << a[j]) | f[i][j - 1];
        }
        int C;
        scanf("%d", &C);
        int q, k = 0;
        scanf("%d", &q);
        while (q --) {
            int l, r;
            scanf("%d%d", &l, &r);
            l = (l + k) % (n - r + 1) + 1, r = l + r - 1;
            int T;
            scanf("%d", &T);
            T = (T + k) % (C + 1);
            if (f[l][r][T]) putchar('Y'), ++k;
            else putchar('N');
        }
        puts("");
    }
}

/*
5
2 3 4 5 9
10
5
0 3 5
0 2 4
0 3 4
0 4 6
2 3 5
0
 */
