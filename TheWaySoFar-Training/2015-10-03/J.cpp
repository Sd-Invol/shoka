#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <bitset>
#include <stack>
#include <cmath> 
using namespace std;

typedef long long LL;
int n, m;
int a[100];
int LOG[70];
LL S;
const LL LIMIT = 1e18;

LL mul(LL a, LL b) {
    if (LIMIT / a <= b) return LIMIT;
    return a * b;
}

LL dfs(int x, int k, int mask) {
    if (x > m) {
        if (k == 1) return 0;
        LL ans = 0;
        if (k >= 64) ans = 1;
        else {
            LL p = pow(S, 1.0 / k);
            p = max(0LL, p - 5);
            while (1) {
                LL ans = 1, z = p + 1;
                LL n = k;
                while (n > 0) {
                    if (n & 1) ans = mul(ans, z);
                    z = mul(z, z);
                    n >>= 1;
                }
                if (ans > S) break;
                p++;
                //printf("%lld %lld %d\n", p, ans, k);
            }
            ans = p;
        }
        if (mask == 1) return ans;
        return -ans;
    }
    if (k >= 64) return 0;
    return dfs(x + 1, k * a[x] / __gcd(k, a[x]), mask ^ 1) +
        dfs(x + 1, k, mask);
}

LL solve(LL mid) {
    S = mid;
    return dfs(1, 1, 0);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i  = 1; i <= m; ++i)
            scanf("%d", &a[i]);
        sort(a + 1, a + 1 + m);
        int r = 0;
        for (int i = 1; i <= m; ++i) {
            int flag = 0;
            for (int j = 1; j <= r; ++j)
                if (a[i] % a[j] == 0) flag = 1;
            if (!flag) a[++r] = a[i];
        }
        m = r;
        if (a[1] == 1) {
            printf("%d\n", n);
            continue;
        }
        LL head = 1, tail = 1e17;
        while (head < tail - 1) {
            LL mid = (head + tail) >> 1;
            if (solve(mid) >= n) tail = mid;
            else head = mid;
        }
        if (solve(head) >= n) tail = head;
        printf("%lld\n", tail);
    }
    return 0;
}
