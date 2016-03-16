#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long LL;
const int N = 1e6 + 5;

int a[N], b[N];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &b[i]);
    sort(a + 1, a + 1 + n);
    sort(b + 1, b + 1 + n);
    LL ans = 0;
    for (int i = 1; i <= n; ++i)
        ans += abs(a[i] - b[i]);
    cout << ans << endl;
}
