#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
int n , a[N];
int f[N][1 << 13];

void print(int i , int j) {
    if (i == 0)
        return;
    int x = a[i] - a[i - 1];
    if (f[i][j] & 1) {
        print(i - 1 , (f[i][j] >> 1) - 1);
        putchar('r');
    } else {
        print(i - 1 , (f[i][j] >> 1) - 1);
        putchar('l');
    }
}

void work() {
    int i , j , k , l , x , y;
    scanf("%d",&n);
    for (i = 1 ; i <= n ; ++ i)
        scanf("%d",&a[i]) , a[i] += a[i - 1];
    x = a[n];
    while (~x & 1)
        x >>= 1;
    if (x != 1) {
        puts("no");
        return;
    }
    for (i = 0 ; i <= n ; ++ i)
        memset(f[i] , 0 , a[n] + 1 << 2);
    f[0][0] = 1;
    for (i = 0 ; i < n ; ++ i) {
        x = a[i + 1] - a[i];
        for (j = 0 ; j <= a[i] ; ++ j) {
            if (!f[i][j]) continue;
            k = a[i] - j;

            // L
            if (!j || x <= (j & -j)) {
                f[i + 1][j + x] = (j + 1) << 1;
            }

            //R
            if ((!k && j) || x <= (k & -k)) {
                l = k + x;
                if (__builtin_popcount(l) == 1 && (l > j || (j & l) && l > j - l))
                    l = a[i + 1];
                else
                    l = j;
                f[i + 1][l] = (j + 1) << 1 | 1;
            }
            
        }
    }
    if (!f[n][a[n]]) {
        puts("no");
    } else {
        print(n , a[n]);
        puts("");
    }
}

int main() {
    int _;
    scanf("%d",&_);
    while (_ --)
        work();
    return 0;
}
