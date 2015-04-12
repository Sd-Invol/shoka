#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 100005;
int n;
pair<double , int> a[N];
double f[N];

void work() {
    int i , j , cnt = 0;
    for (i = 1 ; i <= n ; ++ i) {
        scanf("%lf" , &a[i].first);
        a[i].first = 1 / a[i].first;
        a[i].second = 1;
        if (a[i].first == 1 && a[i - 1].first == 1) {
            -- i , -- n;
            ++ a[i].second;
        }
    }
    for (i = 1 ; i <= n ; ++ i)
        f[i] = 1e60;
    f[0] = -1;
    double res = 1e60;
    for (i = 0 ; i < n ; ++ i) {
        double x = 0; ++ f[i];
        for (j = i + 1 ; j <= n && j - i <= 50 ; ++ j) {
            x = (x + a[j].second) * a[j].first;
            f[j] = min(f[j] , f[i] + x);
        }
    }
    printf("%.10f\n" , f[n]);
}

int main() {
    while (scanf("%d",&n) , n)
        work();
    return 0;
}
