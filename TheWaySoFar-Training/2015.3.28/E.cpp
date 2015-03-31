#include <bits/stdc++.h>
using namespace std;
const int N = 4444;
int n , a , b , c , m;
int w[N][N] , f[N][N] , pre[N][N];


void work() {
    int i , j , k;
    scanf("%d%d%d%d",&a,&b,&c,&m);
    for (i = 0 ; i < n ; ++ i)
        for (j = 0 ; j < n ; ++ j) {
            w[i][j] = (a * i + b * j + c * (i ^ j)) % m;
            f[i + 1][j] = 1 << 30;
        }
    for (i = 0 ; i < n ; ++ i)
        f[1][i] = 0;
    for (i = 1 ; i < n ; ++ i) {
        for (j = 0 ; j < n ; ++ j) {
            if (f[i][j] == 1 << 30)
                continue;
            for (k = (i & -i) - 1 ; k >= 0 ; -- k) {
                int y = (j ^ (i & -i) ^ k);
                if (f[i][j] + w[j][y] < f[i + 1][y]) {
                    f[i + 1][y] = f[i][j] + w[j][y];
                    pre[i + 1][y] = j;
                }
            }
        }
    }
    j = min_element(f[n] , f[n] + n) - f[n];
    printf("%d\n" , f[n][j]);
    vector<int> res(n);
    for (i = 0 ; i < n ; ++ i) {
        res[n - i - 1] = j;
        j = pre[n - i][j];
    }
    for (i = 0 ; i < n ; ++ i)
        printf("%d%c" , res[i] , " \n"[i + 1 == n]);        
}

int main() {
    freopen("elegant.in" , "r" , stdin);
    freopen("elegant.out" , "w" , stdout);
    while (scanf("%d",&n) , n)
        work();    
    return 0;
}
