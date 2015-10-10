#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cassert>
typedef long long LL;
using namespace std;
const int N = 40;
const int Q = 1e9 + 7;
int ca;
int n , m , K , P;
int dx[N] , dy[N] , dw[N], Dx , Dy , Dw;

int power(int x , int y) {
    int res = 1;
    while (y) {
        if (y & 1)
            res = (LL)res * x % Q;
        x = (LL)x * x % Q , y >>= 1;
    }
    return res;
}

struct rect {
    int x1 , y1 , x2 , y2 , w;
    void input() {
        scanf("%d%d%d%d%d" , &x1 , &y1 , &x2 , &y2 , &w);
        -- x1 , -- y1;
    }
    bool operator < (const rect& R) const {
        return w < R.w;
    }
}R[N];
void desc(int *d , int& D) {
    sort(d , d + D);
    D = unique(d , d + D) - d;
}
int mask[N][N] , mx[N][N] , con[N][N];
int f[2][1 << 10];
void work() {
    scanf("%d%d%d%d" , &n , &m , &K , &P);
    Dx = Dy = Dw = 0;
    dx[Dx ++] = 0 , dx[Dx ++] = n;
    dy[Dy ++] = 0 , dy[Dy ++] = m;
    dw[Dw ++] = K , dw[Dw ++] = 0;
    for (int i = 0 ; i < P ; ++ i) {
        R[i].input();
        dx[Dx ++] = R[i].x1 , dx[Dx ++] = R[i].x2;
        dy[Dy ++] = R[i].y1 , dy[Dy ++] = R[i].y2;
        dw[Dw ++] = R[i].w;
        dw[Dw ++] = R[i].w - 1;
    }
    sort(R , R + P);
    desc(dx , Dx);
    desc(dy , Dy);
    desc(dw , Dw);
    memset(mask , 0 , sizeof(mask));    
    for (int i = 0 ; i + 1 < Dx ; ++ i)
        for (int j = 0 ; j + 1 < Dy ; ++ j) {
            mx[i][j] = Dw - 1;
            con[i][j] = 0;
        }
    for (int i = 0 ; i < P ; ++ i) {
        R[i].x1 = lower_bound(dx , dx + Dx , R[i].x1) - dx;
        R[i].x2 = lower_bound(dx , dx + Dx , R[i].x2) - dx;
        R[i].y1 = lower_bound(dy , dy + Dy , R[i].y1) - dy;
        R[i].y2 = lower_bound(dy , dy + Dy , R[i].y2) - dy;    
        int w = lower_bound(dw , dw + Dw , R[i].w) - dw;
        for (int x = R[i].x1 ; x < R[i].x2 ; ++ x)
            for (int y = R[i].y1 ; y < R[i].y2 ; ++ y) {
                mask[x][y] |= 1 << i;
                mx[x][y] = min(mx[x][y] , w); 
            }
        for (int x = 0 ; x + 1 < Dx ; ++ x)
            for (int y = 0 ; y + 1 < Dy ; ++ y)
                if (make_pair(x , y) > make_pair(R[i].x2 , R[i].y2))
                    con[x][y] |= 1 << i;
    }
    memset(f , 0 , sizeof(f));
    int cur = 0 , nxt = 1;
    f[cur][0] = 1;
    for (int i = 0 ; i + 1 < Dx ; ++ i)
        for (int j = 0 ; j + 1 < Dy ; ++ j) {
            int cnt = (dx[i + 1] - dx[i]) * (dy[j + 1] - dy[j]); 
            memset(f[nxt] , 0 , sizeof(f[nxt]));
            for (int k = 0 ; k < 1 << P ; ++ k) {
                if (!f[cur][k]) continue;
                if (~k & con[i][j]) continue;
                for (int l = 1 ; l <= mx[i][j] ; ++ l) {
                    int nxtk = k;
                    for (int p = 0 ; p < P ; ++ p)
                        if ((mask[i][j] >> p & 1) && dw[l] == R[p].w)
                            nxtk |= 1 << p;
                    f[nxt][nxtk] += (LL)f[cur][k] * (power(dw[l] , cnt) - power(dw[l - 1] , cnt) + Q) % Q;
                    f[nxt][nxtk] %= Q;
                }                
            }            
            swap(cur , nxt);
        }
    printf("Case #%d: %d\n" , ++ ca , f[cur][(1 << P) - 1]);
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}