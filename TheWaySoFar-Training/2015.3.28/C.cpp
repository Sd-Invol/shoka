#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

map<int, LL> f[2][33][33][33]; 

int main() {
    freopen("catalian.in", "r", stdin);
    freopen("catalian.out", "w", stdout);
    int n, T = 0;
    while (scanf("%d", &n), n) {
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j <= n; ++j)
                for (int k = 0; k <= n; ++k)
                    for (int l = 0; l <= n; ++l)
                        f[i][j][k][l].clear();
        int cur = 0, nex = 1;
        f[cur][0][0][0][1] = 1;
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j <= n; ++j)
                for (int k = 0; k <= n; ++k)
                    for (int l = 0; l <= n; ++l)
                        f[nex][j][k][l].clear();
            for (int j = 0; j <= n; ++j)
                for (int k = 0; k <= n; ++k)
                    for (int l = 0; l <= n; ++l) {
                        map<int, LL> &ma = f[cur][j][k][l];
                        for (map<int, LL>::iterator it = ma.begin(); it != ma.end(); ++it) {
                            int mask = it -> first;
                            //printf("%d %d %d %d %d : %lld\n", i, j, k, l, mask, it -> second);
                            LL ans = it -> second;
                            int l1 = l, mask1 = mask;
                            for (int k1 = l; k1 <= j + 1; ++k1) {
                                int j1 = j + (k < k1);
                                if (k1 - 1 > l && (mask >> ((k1 - 1) - l) & 1))
                                    l1 = k1 - 1;
                                mask1 = mask >> (l1 - l);
                                mask1 |= 1 << (k1 - l1);
                                // if (i == 2 && k1 == l1)
                                //   printf("%d %d\n", k1, l);
                                f[nex][j1][k1][l1][mask1] += ans;
                            }
                            
                        }
                    }
            swap(cur, nex);
        }
        LL ans = 0;
        for (int j = 0; j <= n; ++j)
            for (int k = 0; k <= n; ++k)
                for (int l = 0; l <= n; ++l)
                    for (auto it : f[cur][j][k][l]) {
                        ans += it.second;
                        //printf("%d %d %d %d : %lld\n", j, k, l, it.first, it.second);
                    }
        printf("Case #%d: %lld\n", ++T, ans);
    }
    return 0;
}
