#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 200005;
bool f[N];
int p[N] , m;
void work() {
    int n , res = 0 , i , j , x = 1;
    scanf("%d",&n);
    for (i = 2 ; i <= n ; ++ i)
        if (!f[i]) {
            p[m ++] = i;
            for (j = i * i ; j <= n ; j += i)
                f[j] = 1;
        }
    for (i = m - 1 , j = 0 ; j <= i ; -- i) {
        ++ res;
        if (j < i && p[j] * p[i] <= n) {
            //    cout << p[j] << ' ' << p[i] << endl;
            ++ j;
        } else {
            //    cout << p[i] << endl;
        }
    }
    cout << res << endl;
}

int main() {
    freopen("gcd.in" , "r" , stdin);
    freopen("gcd.out" , "w" , stdout);
    work();
    return 0;
}
