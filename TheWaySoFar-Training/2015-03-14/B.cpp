#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 100005;
int n , m;
int a[N] , b[N];

int main() {
    freopen("ccf.in" , "r" , stdin);
    freopen("ccf.out" , "w" , stdout);
    
    int i , x , y;
    scanf("%d" , &n);
    for (i = 0 ; i <= n ; ++ i)
        scanf("%d" , &a[i]);
    scanf("%d" , &m);
    for (i = 0 ; i <= m ; ++ i)
        scanf("%d" , &b[i]);
    y = max(n , m);
    for (i = n + 1 ; i <= y ; ++ i) a[i] = 1 << 30;
    for (i = m + 1 ; i <= y ; ++ i) b[i] = 1 << 30;

    for (i = 0 , x = 0 ; i <= y ; ++ i , x ^= 1) {
        if (a[i] != b[i]) {
            if (a[i] > b[i])
                putchar("><"[x]);
            else
                putchar("<>"[x]);             
            return 0;
        }
    }
    putchar('=');
    return 0;
}
