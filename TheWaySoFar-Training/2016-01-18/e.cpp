#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 2e5 + 5;
typedef long long LL;
int L;
pair<LL, LL> val[N];
LL sum[N], num[N];

int main() {
    scanf("%d", &L);
    for (int i = 1; i <= L; ++i) {
        scanf("%lld%lld", &val[i].second, &val[i].first);
    }
    LL m;
    sort(val + 1, val + 1 + L);
    reverse(val + 1, val + 1 + L);
    int flag = -1;
    for (int i = L; i > 0; --i) {
        sum[i] = sum[i + 1] + val[i].first * val[i].second;
        num[i] = num[i + 1] + val[i].second;
        if (val[i].first == 1) continue;
        if (num[i + 1] == 0) continue;
        m = val[i].first - 1;
        if ((sum[i + 1] + 1 + num[i + 1] - 1) / num[i + 1] > m) continue;
        flag = i;
        break;
    }
    //printf("%lld %lld\n" , sum[L], num[L]);
    if (flag == -1) {
        puts("-1");
        return 0;
    }
    vector<pair<LL, LL> > ans;
    for (int i = 1; i <= flag; ++i) {
        if (i == flag) {
            ans.push_back(make_pair(val[i].first, val[i].second - 1));
            ans.push_back(make_pair(val[i].first - 1, 1));
        }
        else ans.push_back(val[i]);
    }
    LL mtot = sum[flag + 1] + 1;
    LL ntot = num[flag + 1];
    mtot -= ntot;
    if (m > 1) {
        LL tmp = mtot / (m - 1);
        ntot -= tmp;
        mtot -= tmp * (m - 1);
        ans.push_back(make_pair(m, tmp));
        if (mtot > 0) {
            ans.push_back(make_pair(1 + mtot, 1));
            ntot--;
        }
        if (ntot > 0) ans.push_back(make_pair(1LL, ntot));
    }
    sort(ans.begin(), ans.end());
    reverse(ans.begin(), ans.end());
    int r = 0;
    for (int i = 0; i < ans.size(); ++i) {
        if (ans[i].second == 0) continue;
        if (r > 0 && ans[i].first == ans[r - 1].first)
            ans[r - 1].second += ans[i].second;
        else ans[r++] = ans[i];
    }
    ans.resize(r);
    printf("%d\n", (int)ans.size());
    for (int i = 0; i < ans.size(); ++i)
        printf("%lld %lld\n", ans[i].second, ans[i].first);
    return 0;
}
