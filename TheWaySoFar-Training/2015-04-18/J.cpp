#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

multiset<int> ext;

pair<int, int> a[N];
typedef long long LL;
const int P = 1e9 + 7;

int I[N], inv[N];

int A(int n, int m) {
    return (LL)I[n] * inv[n - m] % P;
}

void init() {
    I[0] = I[1] = inv[0] = inv[1] = 1;
    for (int i = 2; i < N; ++i) {
        I[i] = i;
        inv[i] = ((LL)P - P / i) * inv[P % i] % P;
    }
    for (int i = 2; i < N; ++i) {
        I[i] = (LL)I[i - 1] * I[i] % P;
        inv[i] = (LL)inv[i] * inv[i - 1] % P;
    }
}

void solve(int &ans, int n, int m) {
    if (n > m) swap(n, m);
    //printf("%d %d\n", m, n);
    ans = (LL)ans * A(m, n) % P;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &a[i].first, &a[i].second);
    }
    init();
    sort(a + 1, a + 1 + n);
    reverse(a + 1, a + 1 + n);
    int ans = 1;
    for (int i = 1, p = 0; i <= n; ++i) {
        while (!ext.empty() && *ext.rbegin() > a[i].first) {
            ++p;
            multiset<int>::iterator it = ext.end();
            --it;
            ext.erase(it);
        }
        int j = i - 1;
        while (j < n && a[j + 1].first == a[i].first) {
            ++j;
            ext.insert(a[j].second);
        }
        solve(ans, p, j - i + 1);
        p = max(0, p - (j - i + 1));
        i = j;
    }
    printf("%d\n", ans);
    return 0;
}
