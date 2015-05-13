#include <bits/stdc++.h>
using namespace std;
const int N = 2005;
int n , m , K , ca;
int dx[N] , dy[N] , Dx , Dy; 
int x1[N] , x2[N] , Y[N];
bool f[N][N] , w[N][N];
void work() {
    int i , j , k , x , y;
    Dx = Dy = 0;
    dx[Dx ++] = 0 , dx[Dx ++] = n;
    dy[Dy ++] = 0 , dy[Dy ++] = m;
    for (i = 0 ; i < K ; ++ i) {
        scanf("%d%d%d%d" , &j , &k , &x , &y);
        ++ x;
        x1[i] = j , x2[i] = x , Y[i] = y;
        dx[Dx ++] = j , dx[Dx ++] = x;
        dy[Dy ++] = y , dy[Dy ++] = y + 1;     
    }
    sort(dx , dx + Dx);
    Dx = unique(dx , dx + Dx) - dx;
    sort(dy , dy + Dy);
    Dy = unique(dy , dy + Dy) - dy;
    
    for (i = 0 ; i + 1 < Dx ; ++ i)
        for (j = 0 ; j + 1 < Dy ; ++ j) {
            f[i][j] = 0;
            w[i][j] = 0;
        }
    for (i = 0 ; i < K ; ++ i) {
        y = lower_bound(dy , dy + Dy , Y[i]) - dy;
        j = lower_bound(dx , dx + Dx , x1[i]) - dx;
        x = lower_bound(dx , dx + Dx , x2[i]) - dx;
        for (k = j ; k < x ; ++ k)
            w[k][y] = 1;
    }
    queue<int> Q;
    if (!w[Dx - 2][Dy - 2]) {
        f[Dx - 2][Dy - 2] = 1; 
        Q.push(Dx - 2) , Q.push(Dy - 2);
        while (!Q.empty()) {       
            x = Q.front(); Q.pop();
            y = Q.front(); Q.pop();
            if (x > 0 && !w[x - 1][y] && !f[x - 1][y]) {
                f[x - 1][y] = 1;
                Q.push(x - 1);
                Q.push(y);            
            }
            if (y > 0 && !w[x][y - 1] && !f[x][y - 1]) {
                f[x][y - 1] = 1;
                Q.push(x);
                Q.push(y - 1);            
            }
        }
    }
    long long res = 0;
    for (i = 0 ; i + 1 < Dx ; ++ i)
        for (j = 0 ; j + 1 < Dy ; ++ j)
            if (!w[i][j] && !f[i][j])
                res += (long long)(dx[i + 1] - dx[i]) * (dy[j + 1] - dy[j]);
    printf("Case %d: %lld\n" , ++ ca , res);
}

int main() {
    while (scanf("%d%d%d" , &m ,&n, &K) , n)
        work();
    return 0;
}
