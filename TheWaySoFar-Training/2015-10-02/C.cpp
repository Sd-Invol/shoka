#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
using namespace std;

int f[2][17][1 << 16];
char str[1000][20];

void updata(int &x, int y) {
    x = max(x, y);
}

int sett(int mask, int t, int q) {
    int x = mask & (1 << t);
    mask -= x;
    mask += q << t;
    return mask;
}

int main() {
    //cout << sizeof(f) / 1024 / 1024 << endl;
    int n, m;
    while (scanf("%d%d", &n, &m) == 2) {
        for (int i = 1; i <= n; ++i)
            scanf("%s", str[i]);
        memset(f, -1, sizeof(f));
        int cur = 0, nex = 1;
        f[cur][m][0] = 0;
        for (int i = 1; i <= n; ++i) {
            memset(f[nex], -1, sizeof(f[nex]));
            for (int mask = 0; mask < 1 << m; ++mask)
                f[nex][0][mask] = f[cur][m][mask];
            int len = strlen(str[i]);
            int len1 = 0;
            if (i != 1) len1 = strlen(str[i - 1]);
            for (int j = 0; j < m; ++j)
                for (int mask = 0; mask < 1 << m; ++mask)
                    if (f[nex][j][mask] != -1) {
                        int t = __builtin_popcount(mask & ((1 << j) - 1));
                        if (t < len) {
                            int s = 0;
                            int q = __builtin_popcount(mask & (((1 << m) - 1) - ((1 << j) - 1)));
                            q = len1 - q;
                            if (i != 1 && ((mask >> j) & 1) && str[i][t] == str[i - 1][q]) {
                                s = 2;
                            }
                            if (j >= 1 && (mask >> (j - 1) & 1) && str[i][t] == str[i][t - 1])
                                s += 2;
                            // printf("%d %d %d %d\n", i, j, mask, s);
                            updata(f[nex][j + 1][sett(mask, j, 1)], f[nex][j][mask] + s);
                        }
                        //printf("%d %d %d\n", i, j, mask);
                        updata(f[nex][j + 1][sett(mask, j, 0)], f[nex][j][mask]);
                        // printf("%d\n", f[nex][j + 1][mask]);
                    }
            for (int mask = 0; mask < 1 << m; ++mask) {
                if (__builtin_popcount(mask) != len) {
                    f[nex][m][mask] = -1; 
                    
                }
            }
            swap(cur, nex);
        }
        int ans = 0;
        for (int mask = 0; mask < 1 << m; ++mask) {
            ans = max(ans, f[cur][m][mask]);
            //if (f[cur][m][mask] != -1) cout << mask << endl;
        }
        printf("%d\n", ans);
    }
    return 0;
}