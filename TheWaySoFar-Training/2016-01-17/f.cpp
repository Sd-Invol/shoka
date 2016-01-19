#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

const double eps = 1e-10;
typedef long long LL;

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        double a, b, c;
        scanf("%lf%lf%lf", &a, &b, &c);
        LL A = lround(a * 1e5);
        LL B = lround(b * 1e5);
        LL C = lround(c * 1e5);
        LL D = A * B * C - (A * B + A * C + B * C) * 100000;
        if (D > 0) puts("YES");
        else puts("NO");
    }
}
