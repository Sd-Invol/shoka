#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
typedef long long LL;
using namespace std;

const int N = 22;

int main() {
    freopen("alter.in", "r", stdin);
    freopen("alter.out", "w", stdout);
    int n, m;
    scanf("%d%d", &n, &m);
    printf("%d\n", n / 2 +  m / 2);
    for (int i = 2; i <= n; i += 2)
        printf("%d %d %d %d\n", i, 1, i, m);
    for (int i = 2; i <= m; i += 2)
        printf("%d %d %d %d\n", 1, i, n, i);
    return 0;
}
