#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 10;
int n , m , a[N] , b[N];
bool v[512];
int bel[512][N];
int val[5] , f[1 << 9] , p[1 << 9];
bool dfs(int i , int k , int* B) {
    if (k == m)
        return 1;
    if (i >> k & 1) {
        for (int j = 0 ; j < n ; ++ j)
            if (val[j] + b[k] <= a[j]) {
                val[j] += b[k];
                B[k] = j;
                if (dfs(i , k + 1 , B))
                    return 1;
                val[j] -= b[k];
            }
        return 0;
    } else {
        B[k] = -1;
        return dfs(i , k + 1 , B);
    }
}

void work() {
    int i , j , k , x;
    for (i = 0 ; i < n ; ++ i)
        scanf("%d" , &a[i]);
    for (i = 0 ; i < m ; ++ i)
        scanf("%d" , &b[i]);
    memset(v , 0 , sizeof(v));
    for (i = 0 ; i < 1 << m ; ++ i) {
        memset(val , 0 , sizeof(val));
        if (dfs(i , 0 , bel[i])) {
            v[i] = 1;
        }
    }
    memset(f , 63 , sizeof(f));
    f[0] = 0;
    for (i = 0 ; i + 1 < 1 << m ; ++ i) {
        if (f[i] > 100) continue;
        int mask = ((1 << m) - 1) ^ i;
        for (j = mask ; j ; j = (j - 1) & mask) {
            if (!v[j]) continue;
            if (f[i ^ j] > f[i] + 1) {
                f[i ^ j] = f[i] + 1;
                p[i ^ j] = j;
            }
        }
    }
    j = (1 << m) - 1;
    if (f[j] > 100) f[j] = -1;
    printf("%d\n" , f[j]);
    if (~f[j]) {
        while (j != 0) {
            i = p[j];
            printf("%d" , __builtin_popcount(i));
            for (k = 0 ; k < m ; ++ k)
                if (~bel[i][k])
                    printf(" %d %d" , k + 1 , bel[i][k] + 1);
            puts("") , j ^= i;
        }

    }
}

int main() {
    while (~scanf("%d%d",&n,&m))
        work();
    return 0;
}
