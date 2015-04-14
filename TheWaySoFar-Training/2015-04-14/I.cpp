#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 200005;
LL T;
int n , m , a[N] , b[N];
char str[N];

int main() {
    int i , j , x;
    scanf("%lld%d%s" , &T , &n , str);
    for (i = 0 ; i < n ; ++ i)
        a[i] = str[i] - '0';
    m = n + n + 2 , x = 1;
    for (j = 0 ; j < 60 ; ++ j) {       
        if (T >> j & 1) {
            int s = 0;
            for (i = 0 ; i < n ; ++ i)
                b[s ++] = a[i];
            b[s ++] = 0;
            for (i = 0 ; i < n ; ++ i)
                b[s ++] = a[n - i - 1];
            b[s ++] = 0;
            for (i = 0 ; i < n ; ++ i) {
                a[i] = b[(i + x) % m] ^ b[(i + m - x) % m];
            }
        }
        x <<= 1;
        x %= m;
    }
    for (i = 0 ; i < n ; ++ i)
        printf("%d" , a[i]);
    puts("");        
    return 0;
}
