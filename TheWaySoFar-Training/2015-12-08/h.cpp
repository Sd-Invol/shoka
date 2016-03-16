#include <cstdio>
#include <queue>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 2005;
typedef long long LL;

LL f[N][N], sum[N];
int a[N];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        sum[i] = sum[i - 1] + a[i];
    }
    //memset(f, 63, sizeof(f));
    for (int i = 1; i <= n; ++i) {
        f[i][i] = a[i];
    }
    for (int i = n - 1; i >= 1; --i) {
        vector<int> P;
        P.push_back(i);
        for (int j = i + 1; j <= n; ++j) {
            P.push_back(j);
            for (int k = P.size() - 1; k > 0; --k)
                if (a[P[k]] < a[P[k - 1]])
                    swap(P[k], P[k - 1]);
                else break;
            if (P.size() > 100) P.pop_back();
            f[i][j] = 1LL << 50;
            int head = i, tail = j;
            while (head < tail - 1) {
                int mid = (head + tail) >> 1;
                if (f[i][mid] > f[mid + 1][j])
                    tail = mid;
                else head = mid;
            }
            /*   int l = max(i, head - 100);
            int r = min(j, head + 100);
            for (int k = l; k <= r; ++k)
            f[i][j] = min(f[i][j], max(f[i][k - 1], f[k + 1][j]) + a[k]);*/
            for (int k = 0; k < P.size(); ++k)
                f[i][j] = min(f[i][j], max(f[i][P[k] - 1], f[P[k] + 1][j]) + a[P[k]]);
        }
    }
    printf("%lld\n", f[1][n]);
    return 0;
}
