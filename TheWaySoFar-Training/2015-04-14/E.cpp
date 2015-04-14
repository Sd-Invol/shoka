#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
pair<int, int> a[N];
int n, b[N], m, ti[N], aa[N], c[N], d[N];

int cmp(pair<int, int> a, pair<int, int> b) {
    if (a.first != b.first) return a.first < b.first;
    return a.second > b.second;
}

int f[N];

void add(int x, int s) {
    while (x <= m) {
        f[x] = max(f[x], s);
        x += x & -x;
    }
}

int find(int x) {
    int ans = 0;
    while (x > 0) {
        ans = max(ans, f[x]);
        x -= x & -x;
    }
    return ans;
}

int max1[N];

int main() {
    m = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        a[i] = make_pair(x, i);
        b[++m] = x;
    }
    sort(b + 1, b + 1 + m);
    m = unique(b + 1, b + 1 + m) - b - 1;
    for (int i = 1; i <= n; ++i)
        a[i].first = lower_bound(b + 1, b + 1 + m, a[i].first) - b;
    sort(a + 1, a + 1 + n, cmp);
    for (int i = 1; i <= n; ++i) {
        ti[a[i].second] = i;
        aa[a[i].second] = a[i].first;
    }
    for (int i = n; i >= 1; --i) {
        d[i] = find(aa[i] - 1);
        max1[aa[i]] = max(max1[aa[i]], min(ti[i], d[i])); 
        add(aa[i], ti[i]);
    }
    for (int i = 1; i <= m; ++i)
        max1[i] = max(max1[i], max1[i - 1]);
    for (int i = 1; i <= n; ++i) {
        d[i] = min(max(d[i], max1[aa[i] - 1]), ti[i]);
        ++c[d[i]];
        //printf("%d %d\n", i, d[i]);
    }
    int ans = 1 << 30;
    for (int i = n, j = 0; i >= 0; --i) {
        ans = min(ans, i + j);
        j += c[i];
    }
    printf("%d\n", ans);
    return 0;
}
