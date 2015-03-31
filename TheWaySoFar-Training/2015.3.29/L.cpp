#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 1e5 + 5;
int n;
int a[N];

map<int, int> ext;

void updata(LL &ans) {
    map<int, int>::iterator it = ext.end();
    --it;
    ans = min(ans, (LL)it -> first * it -> second);
}

void add(int x, int s) {
    if ((ext[x] += s) == 0) {
        ext.erase(x);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        ext[a[i]] ++;
    }
    LL ans = 1LL << 60;
    updata(ans);
    for (int i = 1; i < n; ++i)
        if (a[i] > 0) {
            add(a[i], -1);
            add(a[i + 1], -1);
            add(a[i] - 1, 1);
            add(a[i + 1] + 1, 1);
            updata(ans);
            add(a[i], 1);
            add(a[i + 1], 1);
            add(a[i] - 1, -1);
            add(a[i + 1] + 1, -1);
        }
    reverse(a + 1, a + 1 + n);
    for (int i = 1; i < n; ++i)
        if (a[i] > 0) {
            add(a[i], -1);
            add(a[i + 1], -1);
            add(a[i] - 1, 1);
            add(a[i + 1] + 1, 1);
            updata(ans);
            add(a[i], 1);
            add(a[i + 1], 1);
            add(a[i] - 1, -1);
            add(a[i + 1] + 1, -1);
        }
    printf("%lld\n", ans);
    return 0;
}
