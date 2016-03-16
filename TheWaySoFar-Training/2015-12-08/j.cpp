#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 20;

int n , m , t;
double p[N] , q[N] , f[1 << 20][N] , g[N][N];

int main() {
    scanf("%d%d%d" , &n , &m , &t);
    for (int i = 0 ; i < n ; ++ i) {
        scanf("%lf" , &p[i]);
    }
    for (int i = 0 ; i < n ; ++ i)
        for (int j = 0 ; j < n ; ++ j)
            g[i][j] = (i == j) ? 0 : 1e30;   
    for (int i = 0 ; i < m ; ++ i) {
        int x , y;
        scanf("%d%d" , &x , &y);
        -- x , -- y;
        g[x][y] = g[y][x] = 1;
    }
    for (int k = 0 ; k < n ; ++ k)
        for (int i = 0 ; i < n ; ++ i)
            for (int j = 0 ; j < n ; ++ j)
            g[i][j] = min(g[i][j] , g[i][k] + g[k][j]);
    for (int i = (1 << n) - 1 ; i > 0 ; -- i) {
        static pair<double , int> a[N];
        int cnt = 0;
        double sump = 0;
        for (int x = 0 ; x < n ; ++ x)
            if (~i >> x & 1)
                sump += p[x];
        fill(f[i] , f[i] + n , 1e30);
        if (sump < 1e-4)
            continue;
        for (int x = 0 ; x < n ; ++ x)
            if (~i >> x & 1)
                q[x] = (sump - p[x]) / sump;
        for (int x = 0 ; x < n ; ++ x) {
            if (~i >> x & 1)
                continue;
            for (int y = 0 ; y < n ; ++ y) {
                if (~i >> y & 1)
                    f[i][x] = min(f[i][x] , q[y] * f[i | 1 << y][y] + g[x][y]);
            }
            a[cnt ++] = make_pair(f[i][x] , x);            
        }
        sort(a , a + cnt);
        double B = 0;
        for (int y = 0 ; y < n ; ++ y) {
            if (~i >> y & 1)
                B += q[y] * f[i | 1 << y][y];
        }
        B = B / n + t;
        printf("%d:\n" , i);;
        for (int j = 0 ; j <= cnt ; ++ j) {
            double K = 1 , L = 0;
            for (int k = 0 ; k < cnt ; ++ k) {
                if (k < j)
                    L += a[k].first;
                else {
                    K -= 1.0 / n;
                    L += B;
                }
            }
            double T = L / K;
            for (int x = 0 ; x < n ; ++ x) {
                if (i >> x & 1)
                    f[i][x] = min(f[i][x] , T / n + B);
            }
            printf("%.10f\n" , T);
        }
    }
    printf("%.12f\n" , f[1][0]);
    return 0;    
}
