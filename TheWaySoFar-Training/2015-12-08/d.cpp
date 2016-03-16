#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 250005;
int n , m , K , a[N] , b[N];

int main() {
    scanf("%d%d%d" , &n , &m , &K);
    for (int i = 0 ; i < n ; ++ i)
        scanf("%d" , &a[i]);
    sort(a , a + n);
    long long res = 0;
    for (int i = 0 ; i < m ; ++ i) {
        scanf("%d" , &b[i]);
        res += upper_bound(a , a + n , b[i] + K) - lower_bound(a , a + n , b[i] - K);
    }
    printf("%lld\n" , res);
    return 0;
}
