#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cctype>
#include <string>
#include <queue>
using namespace std;

const int N = 1e5 + 5;
int a[N];
int b[N], c[N];
int S[N], T[N];

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        int ans = 0;
        // reverse(a + 1, a + 1 + n);
        for (int i = 1; i <= n; ++i)
            if (a[i] == 10000) {
                b[0] = 0;
                int r = 10005;
                memset(T, 0, sizeof(T));
                for (int j = 1; j < n; ++j) {
                    int p = i - j; 
                    if (p <= 0) p += n;
                    if (a[p] == 10000) b[j] = 0;
                    else {
                        int q = a[p] + 1;
                        b[j] = 0;
                        for (int x = q; x <= r; x += x & -x)
                            b[j] = max(b[j], T[x]);
                        b[j] += a[p];
                        for (int x = q; x > 0; x -= x & -x)
                            T[x] = max(T[x], b[j]);
                    }
                    //  printf("%d %d\n", j, b[j]);
                    b[j] = max(b[j], b[j - 1]);
                }
                c[0] = 0;
                memset(T, 0, sizeof(T));
                for (int j = 1; j < n; ++j) {
                    int p = i + j; 
                    if (p > n) p -= n;
                    if (a[p] == 10000) c[j] = 0;
                    else {
                        c[j] = 0;
                        int q = a[p] + 1;
                        for (int x = q; x <= r; x += x & -x)
                            c[j] = max(c[j], T[x]);
                        c[j] += a[p];
                        for (int x = q; x > 0; x -= x & -x)
                            T[x] = max(T[x], c[j]);
                    }
                    c[j] = max(c[j], c[j - 1]);
                }
                for (int i = 0; i <= n - 1; ++i)
                    ans = max(ans, 10000 + c[i] + b[n - 1 - i]);
            }
        printf("%d\n", ans);
    }
    return 0;
}