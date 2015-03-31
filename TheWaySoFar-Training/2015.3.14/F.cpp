#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 6;

const int n = 5;
int X[N] , Y[N];
int f[N][N];
void work() {
    int i , j , k , l;
    int area = 0;
    for (i = 0 ; i < n ; ++ i)
        scanf("%d%d" , &X[i] , &Y[i]);
    for (i = 0 ; i < n ; ++ i)
        area += X[i] * Y[(i + 1) % n] - Y[i] * X[(i + 1) % n];
    memset(f , 0 , sizeof(f));
    if (area < 0) {
        area = -area;
        reverse(X , X + n);
        reverse(Y , Y + n);
    }
    for (l = 1 ; l < n ; ++ l) {
        for (i = 0 ; i + l < n ; ++ i) {
            j = i + l;
            if (l == 1) {
                f[i][j] = 1;
            } else {
                for (k = i + 1 ; k < j ; ++ k) {
                    if ((X[k] - X[i]) * (Y[k] - Y[j]) - (Y[k] - Y[i]) * (X[k] - X[j]) < 0) {
                        f[i][j] += f[i][k] * f[k][j];
                    }
                }
            }
        }
    }
    printf("%d\n" , f[0][n - 1]);
}

int main() {
    freopen("pentagon.in" , "r" , stdin);
    freopen("pentagon.out" , "w" , stdout);

    int _;
    scanf("%d",&_);
    while (_ --)
        work();            
    
    return 0;
}
