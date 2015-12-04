#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <bitset>
#include <stack>
#include <cmath>
#include <set>
#include <map>
using namespace std;

const int N = 1e5 + 5;

struct PEO {
    int s, mask;

    int operator < (const PEO &a) const {
        return s < a.s;
    }
}p[N];

struct query {
    int mask, id, mon, mask1;

    int operator < (const query &a) const {
        if (mask != a.mask) mask < a.mask;
        return mon < a.mon;
    };
}que[N];

int ans[N], num[N];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &p[i].s);
        p[i].s = -p[i].s;
        int y;
        scanf("%d", &y);
        p[i].mask = 0;
        for (int j = 0; j < y; ++j) {
            int q;
            scanf("%d", &q);
            --q;
            p[i].mask |= 1 << q;
        }
    }
    int q;
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i) {
        int a;
        scanf("%d", &a);
        que[i].id = i;  que[i].mon = p[a].s;
        que[i].mask = 0;
        int y;
        scanf("%d", &y);
        for (int j = 0; j < y; ++j) {
            int x;
            scanf("%d", &x);
            --x;
            que[i].mask |= 1 << x;
        }
        que[i].mask1 = p[a].mask & que[i].mask; 
    }
    sort(p + 1, p + 1 + n);
    sort(que + 1, que + 1 + q);
    for (int l = 1; l <= q; ++l) {
        int r = l;
        while (r < q && que[r + 1].mask == que[l].mask)
            ++r;
        for (int i = 0; i < 1 << m; ++i)
            num[i] = 0;
        for (int i = l, j = 1; i <= r; ++i) {
            while (j <= n && p[j].s < que[i].mon) {
                ++num[p[j].mask & que[i].mask];
                ++j;
            }
            ans[que[i].id] = num[que[i].mask1] + 1;
        }
        l = r;
    }
    for (int i = 1; i <= q; ++i)
        printf("%d\n", ans[i]);
    return 0;
}