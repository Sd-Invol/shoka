#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1 << 21;

int n , m , K;
int a[6][N];
LL f[N];
char str[N + 5];

int main() {
    int i , j , k;
    scanf("%d%d%d" ,&n,&m,&K);
    for (i = 0 ; i < m ; ++ i) { 
        scanf("%s" , str);
        for (j = 0 ; str[j] ; ++ j)
            a[i][j] = str[j] - '0';
        for (k = 0 ; k < n ; ++ k)
            for (j = 0 ; j < 1 << n ; ++ j)
                if (j >> k & 1)
                    a[i][j] += a[i][j ^ (1 << k)];
    }
    while (K --) {
        scanf("%d%d",&j,&k);
        for (i = 0 ; i < 1 << n ; ++ i)
            f[i] = (LL) a[j][i] * a[k][i];
        for (k = 0 ; k < n ; ++ k)
            for (j = 0 ; j < 1 << n ; ++ j)
                if (j >> k & 1)
                    f[j] -= f[j ^ (1 << k)];
        for (i = 0 ; i < 1 << n ; ++ i)
            str[i] = !!f[i] + '0';
        str[i] = 0 , puts(str);
    }
    return 0;
}


