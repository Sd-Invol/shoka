#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 1e6 + 5;
typedef long long LL;

int sum0[N << 1], sum1[N << 1];
int bo1[N << 1], bo2[N << 1];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    LL ans = 0;
    for (int i = 1; i <= m; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        bo1[x + y] = 1;
        bo2[x - y + n] = 1;
    }
    for (int i = 1; i <= 2 * n; ++i)
        if (bo1[i]) {
            int l = max(1, i - n);
            int r = min(n, i - 1);
            ans += r - l + 1;
        }
    for (int i = 1; i <= 2 * n; ++i)
        if (bo2[i]) {
            int l = max(1, 1 - (i - n));
            int r = min(n, n - (i - n));
            ans += r - l + 1;
        }
    // cout << ans << endl;
    for (int i = 0; i <= 2 * n; ++i)
        if ((i - n) % 2 == 0) 
            sum0[i] = bo2[i];
        else sum1[i] = bo2[i];
    for (int i = 1; i <= 2 * n; ++i) {
        sum0[i] += sum0[i - 1];
        sum1[i] += sum1[i - 1];
    }
    for (int i = 1; i <= 2 * n; ++i)
        if (bo1[i]) {
            int l = max(1, i - n);
            int r = min(n, i - 1);
            int x1 = i - l, y1 = l;
            int x2 = i - r, y2 = r;
            l = x1 - y1 + n;
            r = x2 - y2 + n;
            if (l > r) swap(l, r);
            if (i % 2 == 0) ans -= sum0[r] - sum0[l - 1];
            else ans -= sum1[r] - sum1[l - 1];
        }
    cout << (LL)n * n - ans << endl;
    return 0;
}
