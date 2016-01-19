#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1e5 + 5;

int a[N];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    memset(a, 63, sizeof(a));
    for (int i = 1; i <= n; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        a[x] = min(a[x], y);
    }
    sort(a + 1, a + 1 + n);
    for (int i = 1; ; ++i)
        if (a[i] > m) {
            printf("%d\n", i - 1);
            break;
        }
        else {
            m -= a[i];
        }
    return 0;
}
