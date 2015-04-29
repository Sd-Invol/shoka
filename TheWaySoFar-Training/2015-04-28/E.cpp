#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

double f[2][2];

struct poss {
    double p[2];
    int T;

    int operator < (const poss &a) const {
        return T > a.T;
    }
}a[N];
    
double pow1(double A, int n) {
    double ans = 1, z = A;
    while (n) {
        if (n & 1) ans = ans * z;
        z = z * z; n >>= 1;
    }
    return ans;
}

int main() {
    int n;
    scanf("%d", &n);
    int cur = 0, nex = 1;
    for (int i = 1; i <= n; ++i) {
        int T, ch;
        double p0;
        //T = n - i + 1;
        scanf("%d", &T);
        while (ch = getchar(), ch != 'L' && ch != 'R');
        int mask = (ch == 'R');
        scanf("%lf", &p0);
        p0 = 1 - (1 + pow1(1 - p0 - p0, T)) / 2.0;
        if (mask == 0) a[i] = (poss) {1 - p0, p0, T};
        else a[i] = (poss) {p0, 1 - p0, T};
        //printf("%.10f, %.10f\n", a[i][0], a[i][1]);
    }
    sort(a + 1, a + 1 + n);
    for (int i = n; i >= 1; --i) {
        for (int j = 0; j < 2; ++j) {
            f[nex][j] = a[i].p[j ^ 1] * f[cur][j] + a[i].p[j] * (f[cur][j ^ 1] + 1); 
        }
        swap(cur, nex);
    }
    printf("%.15f\n", f[cur][0]);
}
