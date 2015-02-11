#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 3005;

int n , a , b;
double f[N][N];

void work() {
    int i , j;
    cin >> n >> a >> b;
    for (i = min(n , a) ; i >= 0 ; -- i) {
        for (j = min(n , b) ; j >= 0 ; -- j) {
            if (i + j + 1 <= n) {
                LL x = (LL)a - i + a - i + b - j + 2;
                f[i][j] += 2.0 / x;
                f[i][j] += f[i + 1][j] * (a - i + a - i) / x;
                f[i][j] += f[i][j + 1] * (b - j) / x;
            }
        }
    }
    printf("%.15f\n" , f[0][0]);
    memset(f , 0 , sizeof(f));
    for (i = min(n , a) ; i >= 0 ; -- i) {
        for (j = min(n , b) ; j >= 0 ; -- j) {
            if (i + j + 1 <= n) {
                LL x = (LL)a - i + a - i + b - j + 1;
                f[i][j] += 1.0 / x;
                f[i][j] += f[i + 1][j] * (a - i + a - i) / x;
                f[i][j] += f[i][j + 1] * (b - j) / x;
            }
        }
    }
    printf("%.15f\n" , f[0][0]);
}
int main() {
    freopen("bonus.in" , "r" , stdin);
    freopen("bonus.out" , "w" , stdout);
    work();
    return 0;
}
