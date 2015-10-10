#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <set>
typedef long long LL;
using namespace std;
const int N = 100005;

int root , last , nodecnt;
int u[N << 1][26] , val[N << 1] , f[N << 1];
inline int newnode(int _val) {
    ++ nodecnt;
    memset(u[nodecnt] , 0 , sizeof(u[nodecnt]));
    val[nodecnt] = _val , f[nodecnt] = 0;
    return nodecnt;
}
void extend(int c) {
    int p = last , np = newnode(val[p] + 1);
    while (p && u[p][c] == 0)
        u[p][c] = np , p = f[p];
    if (p == 0)
        f[np] = root;
    else {
        int q = u[p][c];
        if (val[p] + 1 == val[q]) {
            f[np] = q;
        } else {
            int nq = newnode(val[p] + 1);
            memcpy(u[nq] , u[q] , sizeof(u[q]));
            f[nq] = f[q];
            f[q] = f[np] = nq;
            while (p && u[p][c] == q)
                u[p][c] = nq , p = f[p];
        }
    }
    last = np;
}
int n , nxt[N] , cost[26] , A , B , ca;
char str[N];
int q[N] , top , bot;
LL F[N];
void work() {
    nodecnt = 0;
    root = last = newnode(0);
    scanf("%s" , str + 1);
    n = strlen(str + 1);
    for (int i = 1 , j = 1 , x = 1 ; i <= n ; ++ i) {        
        extend(str[i] - 'a');
        j = max(j , i + 1);
        while (x > 1 && j - i - 1 < val[f[x]] + 1)
            x = f[x];
        while (j <= n && u[x][str[j] - 'a']) {
            x = u[x][str[j] - 'a'];
            ++ j;
        }
        nxt[i] = j - 1;
    }
    for (int i = 0 ; i < 26 ; ++ i)
        scanf("%d" , &cost[i]);
    scanf("%d%d" , &A , &B);
    F[0] = 0;
    top = 0 , bot = -1;
    for (int i = 1 ; i <= n ; ++ i) {
        F[i] = F[i - 1] + cost[str[i] - 'a'];
        while (top <= bot && nxt[q[top]] < i)
            ++ top;
        if (top <= bot) {
            int j = q[top];
            F[i] = min(F[i] , F[j] + (LL)A * (i - j) + B + B);
        }
        while (top <= bot && F[i] - (LL)A * i <= F[q[bot]] - (LL)A * q[bot])
            -- bot;
        q[++ bot] = i;        
    }
    printf("Case #%d: %lld\n" , ++ ca , F[n]);
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}
