#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
typedef long long LL;
int n , m;
LL a[N] , s[N];
const LL S = 12000000000000LL;
int main() {
    int i , x , y , z;
    scanf("%d",&n);
    for (i = 1 ; i <= n ; ++ i) {
        scanf("%d%d%d",&x,&y,&z);
        a[i] = x * 1000000000000LL + y * 1000000LL + z; 
    }
    sort(a + 1 , a + 1 + n);
    for (i = 1 ; i <= n ; ++ i) {
        a[i + n] = a[i] + S;        
    }
    for (i = 1 ; i <= n + n ; ++ i)
        s[i] = s[i - 1] + a[i];
    LL res = 1LL << 60;
    m = n / 2;
    for (i = n ; i < n + n ; ++ i) {
        LL sum = n * a[i] - (s[i] - s[i - n]);
        res = min(res , sum);
    }
    printf("%lld " , res / 1000000000000LL);
    res %= 1000000000000LL;
    printf("%lld " , res / 1000000);
    printf("%lld\n" , res % 1000000);
    return 0;    
}
