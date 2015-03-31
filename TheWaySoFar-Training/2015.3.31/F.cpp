#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;

pair<int, int> a[N];

int cmp(pair<int, int> a, pair<int, int> b) {
    if (a.first == b.first) return a.second > b.second;
    return a.first < b.first;
}

int work(int n) {
    sort(a + 1, a + 1 + n, cmp);
    static pair<int, int> que1[N], que2[N];
    int p = 0, q = 0;
    for (int i = 1; i <= n; ++i) {
        int s1 = 1 << 30, s2 = 1 << 30;
        if (p) s1 = que1[p].second;
        if (q) s2 = que2[q].second;
        if (s1 < a[i].second && s2 < a[i].second) return 0;
        if (s1 < a[i].second) {
            que2[++q] = a[i]; 
        }
        else if (s2 < a[i].second) {
            que1[++p] = a[i];
        }
        else {
            if (s1 > s2) que2[++q] = a[i];
            else que1[++p] = a[i];
        }
    }
    puts("yes");
    for (int i = 1; i <= p; ++i)
        printf("%d %d\n", que1[i].first, que1[i].second);
    for (int i = q; i > 0; --i)
        printf("%d %d\n", que2[i].second, que2[i].first);
    return 1;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        int l = -1, r = 1 << 30;
        for (int i = 1; i <= n; ++i) {
            scanf("%d%d", &a[i].first, &a[i].second);
            if (a[i].first > a[i].second)
                swap(a[i].first, a[i].second);
            l = max(a[i].first, l);
            r = min(a[i].second, r);
        }
        if (l > r) puts("no");
        else {
            if (work(n) == 0) puts("no");
        }
    }
    return 0;
}
