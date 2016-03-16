#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 2500005;

int n , m;
LL a[N] , b[N];
int cnt[N];
int main() {
    int x , y;
    scanf("%d%d" , &n , &m);
    scanf("%d%d" , &x , &y);
    for (int i = 0 ; i < n ; ++ i) {
        ++ cnt[x];
        x = (x * 58 + y) % (m + 1);
    }
    n = 0;
    for (int i = 0 ; i <= m ; ++ i)
        for (int &j = cnt[i] ; j > 0 ; -- j)
            a[++ n] = i;
    scanf("%d%d" , &x , &y);
    for (int i = 0 ; i < m ; ++ i) {
        ++ cnt[x];
        x = (x * 58 + y) % (n + 1);
    }
    m = 0;
    for (int i = 0 ; i <= n ; ++ i)
        while (cnt[i] --)
            b[++ m] = i;
    for (int i = 1 ; i <= n ; ++ i)
        a[i] += a[i - 1];
    for (int i = 1 ; i <= m ; ++ i)
        b[i] += b[i - 1];
    /*
    for (int i = 0 ; i <= n ; ++ i) {
        int mn = 1 << 30 , p = -1;
        for (int j = 0 ; j <= m ; ++ j) {
            LL sum = a[i] + b[j] + (LL)(n - i) * (m - j);
            if (sum < mn) {
                mn = sum;
                p = j;
            }
        }
        printf("%d: %d %d\n" , i , p , mn);
    }
    */
    LL res = 1LL << 60;
    for (int i = 0 , j = m ; i <= n ; ++ i) {
        while (j > 0 && b[j] > b[j - 1] + n - i)
            -- j;
        res = min(res , a[i] + b[j] + (LL)(n - i) * (m - j));
    }
    printf("%lld\n" , res);
    return 0;
}
