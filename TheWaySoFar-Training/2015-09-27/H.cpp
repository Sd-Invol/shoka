#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

typedef long long LL;

int a[100];
LL f[2][35][2];

int main() {
    int D, S1, S2;
    int T;
    scanf("%d", &T);
    while (T --) {
        scanf("%d%d%d", &D, &S1, &S2);
        /*if (n == 0) a[n++] = 0;
        a[n++] = 0;
        memset(f, 63, sizeof(f));
        int cur = 0, nex = 1;
        f[cur][0][0] = 0;
        for (int i = 0; i < n; ++i) {
            memset(f[nex], 63, sizeof(f[nex]));
            for (int j = 0; j <= i; ++j)
                for (int k = 0; k < 2; ++k) {
                    //if (f[cur][j][k] == -1) continue;
                    for (int l = 0; l < 2; ++l) {
                        int k1 = k;
                        if (l < a[i]) k1 = 0;
                        if (l > a[i]) k1 = 1;
                        f[nex][j + l][k1] = min(f[nex][j + l][k1], f[cur][j][k] + (1LL << i) * l);
                    }
                }
            swap(cur, nex);
        }
        LL ans = 1LL << 60;
        for (int i = S1; i <= min(S2, n); ++i)
        ans = min(ans, f[cur][i][1]);*/
        LL x = (LL)D + 1;
        while (1) {
            LL T = __builtin_popcount(x);
            if (T >= S1 && T <= S2) break;
            if (T < S1) {
                LL p = (1LL << (S1 - T)) - 1;
                x = x + p;
            }
            else {
                LL T = x & (-x);
                x = x + T;
            }
        }
        static int ca = 0;
        printf("Case #%d: %lld\n", ++ca, x);
    }
    
    return 0;
}
