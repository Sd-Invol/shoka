#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;

typedef long long LL;
const int N = 1e5 + 5;

int h[N], n;
LL m;

LL sum[N];
int ll[N], rr[N];

int check(int H) {
    int p = 0;
    int L = 0;
    set<pair<int, int> > ext;
    for (int i = 1; i <= n; ++i) {
        ext.insert(make_pair(h[i] - i, i));
        while (!ext.empty()) {
            pair<int, int> x = *(--ext.end());
            if (x.first >= H - i) {
                L = max(L, x.second);
                ext.erase(x);
            }
            else break;
        }
        ll[i] = L;
    }
    int R = n + 1;
    ext.clear();
    for (int i = n; i >= 1; --i) {
        ext.insert(make_pair(h[i] + i, i));
        while (!ext.empty()) {
            pair<int, int> x = *(--ext.end());
            if (x.first >= H + i) {
                R = min(R, x.second);
                ext.erase(x);
            }
            else break;
        }
        rr[i] = R;
    }
    //for (int i =1; i <= n; ++i)
    //    if (H == 5)
    //        printf("%d %d %d\n", i, ll[i], rr[i]);
    for (int i = 1; i <= n; ++i)
        if (rr[i] <= n && ll[i] >= 1) {
            LL tmp = (LL)H * (H + 1) / 2;
            tmp -= (LL)(H - (i - ll[i])) * (H - (i - ll[i]) + 1) / 2; 
            if (rr[i] > i) {
                tmp += (LL)(H - 1) * (H) / 2;
                tmp -= (LL)(H - (rr[i] - i)) * (H - (rr[i] - i) + 1) / 2;
            }
            if (ll[i] < rr[i])
                tmp -= sum[rr[i] - 1] - sum[ll[i]];
            if (tmp <= m) return 1;
        }
    return 0;
}

int main() {
//    freopen("landscape.in", "r", stdin);
  //  freopen("landscape.out", "w", stdout);
    scanf("%d%lld", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &h[i]);
        sum[i] = sum[i - 1] + h[i];
    }
    int head = 0, tail = 1000000000 + n + 5;
    for (int i = 1; i <= n; ++i) {
        head = max(head, h[i]);
    }
    tail = max(tail, head);
    while (head < tail - 1) {
        int mid = (head + tail) >> 1;
        if (check(mid)) head = mid;
        else tail = mid;
    }
    if (check(tail)) head = tail;
    cout << head << endl;
    //puts("--");
    //cout << check(5) << endl;
    return 0;
}
