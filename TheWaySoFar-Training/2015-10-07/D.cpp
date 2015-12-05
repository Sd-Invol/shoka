#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
using namespace std;
typedef long long LL;

const int N = 1e5 + 5;
typedef long long LL;

LL sum[N * 2], sum1[N * 2], sum2[N * 2];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        memset(sum, 0, sizeof(sum));
        int mx = 0;
        for (int i = 1; i <= n; ++i) {
            int x, y;
            scanf("%d%d", &x, &y);
            sum[x] += y;
            mx = max(x, mx);
        }
        memset(sum1, 0, sizeof(sum1));
        memset(sum2, 0, sizeof(sum2));
        for (int i = mx; i >= 0; --i) {
            sum1[i] += sum[i] >> 1;
            sum2[i] += sum[i] >> 1;
            sum[i] = sum[i] & 1;
            if (sum[i] > 0) {
                sum1[i]++;
                --sum[i];
                LL x = 1;
                int j = i;
                while (x > 0 && j >= 0) {
                    LL tmp = min(x, (LL)sum[j]);
                    x -= tmp;
                    sum[j] -= tmp;
                    sum2[j] += tmp;
                    x *= 2;
                    --j;
                    if (x > 1e18) x = 1e18;
                }
                if (x > 0) break;
                //i = j + 1;
            }
        }
        for (int i = 0; i <= mx; ++i) {
            sum1[i + 1] += sum1[i] >> 1;
            sum1[i] &= 1;
            sum2[i + 1] += sum2[i] >> 1;
            sum2[i] &= 1;
        }
        int p = mx + 1;
        while (sum1[p] > 0 || sum2[p] > 0) {
            sum1[p + 1] += sum1[p] >> 1;
            sum2[p + 1] += sum2[p] >> 1;
            sum1[p] &= 1;
            sum2[p] &= 1;
            ++ p;
        }        
        vector<int> ver;
        ver.resize(p + 1);
        for (int i = 0, x = 0; i <= p; ++i) {
            int q = sum1[i] - sum2[i];
            if (q < 0) {
                q += 2;
                sum1[i + 1]--;
            }
            ver[i] = q;
        }
        while (ver.size() > 1 && ver.back() == 0)
            ver.pop_back();
        static int ca = 0;
        printf("Case #%d: ", ++ca);
        static char str[N];
        for (int i = (int)ver.size() - 1; i >= 0; --i)
            str[(int)ver.size() - i - 1] = ver[i] + '0';
        str[ver.size()] = 0;
        puts(str);
    }
    return 0;
}