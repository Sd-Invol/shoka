#include <cstdio>
using namespace std;
typedef long long LL;
const int N = 1000005;
int n , q , x;
char str[10];
bool r[N] , c[N];
int main() {
    freopen("adjustment.in" , "r" , stdin);
    freopen("adjustment.out" , "w" , stdout);
    
    scanf("%d%d" , &n , &q);
    LL kr = 0 , br = 0 , kc = 0 , bc = 0 , res;
    while (q --) {
        scanf("%s%d" , str , &x);

        if (*str == 'R') {
            if (r[x]) {
                res = 0;
            } else {
                r[x] = 1;
                res = (LL)x * n + (LL)(n + 1) * n / 2;
                res -= kr * x;
                res -= br;
                ++ kc;
                bc += x;
            }
        } else {
            if (c[x]) {
                res = 0;
            } else {
                c[x] = 1;
                res = (LL)x * n + (LL)(n + 1) * n / 2;
                res -= kc * x;
                res -= bc;
                ++ kr;
                br += x;
            }
        }        
        printf("%lld\n" , res);
    }
    return 0;
}

