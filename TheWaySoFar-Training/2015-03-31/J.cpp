#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;

vector<int> val[N];
typedef long long LL;

int len[N];

int main() {
    int n, T;
    scanf("%d%d", &n, &T);
    LL ans = 1LL << 50, sum = 0;
    for (int i = 0; i < n; ++i) 
        val[1].push_back(i);
    int p = 1;
    for (int i = 1; i <= n; ++i) {
        while (val[p].empty()) ++p;
        int x = val[p].back(); val[p].pop_back();
        int s = len[x] * (x + 1) + 1;
        sum += s;
        ++len[x];
        s = len[x] * (x + 1) + 1;
        if (s > n) continue;
        val[s].push_back(x);
    }
    ans = min(ans, sum + (LL)(n - 1) * T);
    int num = n - 1;
    for (int i = n - 2; i >= 0; --i) {
        for (int j = 0; j < len[i + 1]; ++j) {
            while (val[p].empty()) ++p;
            int x = val[p].back(); val[p].pop_back();
            if (x >= i + 1) {
                --j;
                continue;
            }
            int s = len[x] * (x + 1) + 1;
            sum += s;
            sum -= 1 + j * (i + 2);
            ++len[x];
            s = len[x] * (x + 1) + 1;
            if (s > n) continue;
            val[s].push_back(x);
        }
        if (sum + (LL)i * T < ans) {
            ans = min(ans, sum + (LL) i * T);
            num = i;
        }
    }
    for (int i = 0; i <= n; ++i) {
        val[i].clear();
        len[i] = 0;
    }
    for (int i = 0; i <= num; ++i)
        val[1].push_back(i);
    p = 1;
    for (int i = 1; i <= n; ++i) {
        while (val[p].empty()) ++p;
        int x = val[p].back(); val[p].pop_back();
        ++len[x];
        int s = len[x] * (x + 1) + 1;
        val[s].push_back(x);
    }
    printf("%lld\n", ans);
    p = 0;
    printf("%d\n", num);
    for (int i = 1; i <= num; ++i) {
        p += len[i - 1];
        printf("%d%c", p, " \n"[i == num]);
    }
    return 0;
}
