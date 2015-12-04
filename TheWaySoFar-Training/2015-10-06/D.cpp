#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <bitset>
#include <map>
#include <queue>
#include <cmath>
typedef long long LL;
using namespace std;
const int N = 105;
const int M = 50005;


double sqr(double x) {
    return x * x;
}

const double pi = acos(-1.0);
double d, l, r, t, h;
double angle, l1;
double q;
double a, b, c;

double geta(double h, double r) {
    double d = sqrt(max(sqr(r) - sqr(r - h), 0.0));
    double angle = acos((r - h) / r ) * 2;
    double ans = angle * sqr(r) / 2 - (r - h) * d;
    return ans;
}

double f(double x) {
    double L, R;
    if (x <= 0) {
        double x1 = q - x;
        double len = sqrt(max(r * r - x1 * x1, 0.0));
        L = d - len;
        R = d + len;
    }
    else if (x >= l) {
        double x1 = q + x - l;
        double len = sqrt(max(r * r - x1 * x1, 0.0));
        L = d - len;
        R = d + len;
    }
    else {
        L = 0;
        R = 2 * d;
    }
    double y = (a * x + c) / -b;
    //cout << x << endl;
    //printf("%.10f %.10f %.10f\n", L, R, y);
    if (y < L) return 0;
    if (y > R) return pi * sqr((R - L) / 2);
    double h1 = R - y, r1 = (R - L) / 2;
    if (fabs(h1 - R + L) < (1e-8)) return 0;
    //printf("%.10f %.10f %.10f\n", h1, r1, geta(h1, r1));
    if (h1 > r1) return geta(2 * r1 - h1, r1);
    else return pi * sqr(r1) - geta(h1, r1);
}

double simpson(double a , double b) {
    double c = (a + b) * 0.5;
    return (f(a) + 4 * f(c) + f(b)) * (b - a) / 6;
}
double asr(double a , double b , double eps , double A) {
    double c = (a + b) * 0.5;
    double L = simpson(a , c) , R = simpson(c , b);
    if (fabs(L + R - A) <= 15 * eps)
        return L + R + (L + R - A) / 15;
    return asr(a , c , eps / 2 , L) + asr(c , b , eps / 2 , R);
}


int main() {
    freopen("damage.in", "r", stdin);
    freopen("damage.out", "w", stdout);
    cin >> d >> l >> r >> t >> h;
    d = d / 100;
    l = l / 100;
    r = r / 100;
    t = t / 100;
    h = h / 100;
    d /= 2;
    l1 = r - sqrt(max(r * r - d * d, 0.0));
    q = r - l1;
    double L, R;
    if (fabs(t - l) < 1e-8) {
        a = 0;
        c = 1e8;
        b = -1;
        L = -l1;
        R = min(h, l + l1);
    }
    else {
        angle = asin(1.0 * t  / l);
        a = -tan(angle), b = -1;
        c = h / cos(angle);
        L = -l1;
        R = l + l1;
    }
    // printf("%.10f\n", l1);
    //printf("%.10f %.10f %.10f %.10f\n", a, b, c, angle);
    //for (int i = -100; i <= 700; ++i)
    //    printf("%.2f %.10f\n", (double)i / 10, f((double)i / 10));
    double delta = (R - L) / 100;
    double ans = 0;
    for (int i = 0; i < 100; ++i) {
        ans += asr(L, L + delta, 1e-4, simpson(L, L + delta));
        L += delta;
    }
    printf("%.10f\n", ans);
    return 0;
}
