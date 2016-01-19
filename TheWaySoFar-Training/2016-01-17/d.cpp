#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

const int N = 1e5 + 5;
const double eps = 1e-10;

struct Wire {
    int s, p, o;

    int operator < (const Wire &a) const {
        if (s * o == a.s * a.o) return p * s < a.p * a.s;
        return s * o < a.s * a.o;
    }
    
} a[N];

int main() {
    double d;
    int n;
    scanf("%lf%d", &d, &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d%d", &a[i].s, &a[i].p, &a[i].o);
    }
    sort(a + 1, a + 1 + n);
    reverse(a + 1, a + 1 + n);
    int m = 0;
    for (int i = 1; i <= n; ++i)
        if (m == 0 || a[i].p * a[i].s < a[m].p * a[m].s) a[++m] = a[i];
    a[m + 1].s = 0;
    double G = a[1].s * a[1].o;
    for (int i = 1; i <= m; ++i) {
        double tmpG = a[i + 1].s * a[i + 1].o;
        double Q = G - tmpG;
        double len = Q / (a[i].s * a[i].p);
        len = min(len, d);
        d -= len;
        Q = len * a[i].s * a[i].p;
        G -= Q;
        if (d < eps) break;
    }
    if (d > eps) G = 0;
    printf("%.10f\n", G);
    return 0; 
}
