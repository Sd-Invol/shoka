#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1000005;
int n , a[N];

void work() {
    int i , j , k , x;
    int res = 0;
    scanf("%d" , &n);
    for (i = 0 ; i < n ; ++ i) {
        scanf("%d" , &x);
        a[x] = 1;
    }
    for (i = 1 ; i <= 1000 ; ++ i)
        for (k = i + 1 ; k <= 1000 ; ++ k) {
            if (__gcd(i , k) > 1) continue;
            for (j = 1 ; k * k * j <= 1000000 ; ++ j)
                if (a[i * i * j] && a[i * k * j] && a[k * k * j])
                    ++ res;
        }
    cout << res << endl;            
}

int main() {
    work();
    return 0;
}
