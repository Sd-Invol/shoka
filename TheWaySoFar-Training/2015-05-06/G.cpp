#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 505;
const double pi = acos(-1);
int n , ca , a[N];
double f[N][N];
double check(int L , int R , double val) {
    double ret = 0;
    for (int i = L ; i <= R ; ++ i) {
        ret += asin(a[i] / 2.0 / val) * 2;
    }
    return ret;
}

double cal(int L , int R) {
    if (L > R) return 0;
    if (f[L][R] > 0) return f[L][R];
    double l , r , m;
    int mid = max_element(a + L , a + R + 1) - a;
    f[L][R] = cal(L , mid - 1) + cal(mid + 1 , R);
    l = 0.5 * a[mid] , r = 1e6;
    while (r - l > 1e-10) {
        m = (l + r) * 0.5;
        if (check(L , R , m) >= pi + pi)
            l = m;
        else
            r = m;
    }
    double ret = 0;
    //printf("%f %f\n" , l , check(L , R , l));
    if (check(L , R , l) < pi + pi) {
        l = 0.5 * a[mid] , r = 1e6;
        while (r - l > 1e-10) {
            m = (l + r) * 0.5;
            double cnt = check(L , R , m);
            cnt -= asin(a[mid] / 2.0 / m) * 4;
            if (cnt >= 0)
                r = m;
            else
                l = m;
        }
        l = r;
        //printf("%f %f\n" , l , check(L , R , l));
        double cnt = check(L , R , r);
        cnt -= asin(a[mid] / 2.0 / r) * 4;
        if (cnt < 0)
            return f[L][R];
        else {
            ret -= a[mid] * sqrt(r * r - a[mid] * a[mid] / 4.0) * 2;
        }
    }
    for (int i = L ; i <= R ; ++ i) {
        ret += a[i] * sqrt(l * l - a[i] * a[i] / 4.0);
    }
    return f[L][R] = max(ret / 2 , f[L][R]);
}

void work() {
    for (int i = 1 ; i <= n ; ++ i)
        scanf("%d" , &a[i]);
    for (int i = 1 ; i <= n ; ++ i)
        for (int j = i ; j <= n; ++ j)
            f[i][j] = -1;
    printf("Case %d: %.10f\n" , ++ ca , cal(1 , n));
}

int main() {
    while (scanf("%d" , &n) , n)
        work();
    return 0;
}
