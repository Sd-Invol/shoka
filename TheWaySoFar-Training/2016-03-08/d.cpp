#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 100005;

int n , w , a[N];
int f[17][N] , LOG[N];

inline int RMQ(int l , int r) {
    r = min(r , n - 1);
    int j = LOG[r - l + 1];
    return max(f[j][l] , f[j][r - (1 << j) + 1]);
}

int main() {
    scanf("%d%d" , &n , &w);
    for (int i = 0 ; i < n ; ++ i) {
        scanf("%d" , &a[i]);
        f[0][i] = a[i];
    }
    for (int i = 2 ; i <= n ; ++ i) {
        LOG[i] = LOG[i >> 1] + 1;
    }
    for (int j = 1 ; 1 << j <= n ; ++ j)
        for (int i = 0 ; i + (1 << j) <= n ; ++ i)
            f[j][i] = max(f[j - 1][i] , f[j - 1][i + (1 << j - 1)]);
    for (int l = 1 ; l <= n ; ++ l) {
        
        long long s = 0;
        for (int i = 0 ; i < n ; i += l)
            s += RMQ(i , i + l - 1) + 1;
        if (s - 1 <= w) {
            printf("%d\n" , l);
            return 0;
        }
    }
    return 0;
}
