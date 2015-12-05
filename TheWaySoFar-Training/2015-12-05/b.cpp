#include <cstdio>
#include <algorithm>
using namespace std;
int n , m;
int a[105][105] , b[105][105];
int main() {
    scanf("%d%d" , &n , &m);
    for (int i = 1 ; i <= n ; ++ i)
        for (int j = 1 ; j <= m ; ++ j)
            scanf("%d" , &a[i][j]);
    for (int i = 1 ; i <= n ; ++ i) {
        for (int j = 1 ; j <= m ; ++ j) {
            int x = a[i][j];
            if (i > 1) x = max(x , a[i - 1][j]);
            if (j > 1) x = max(x , a[i][j - 1]);
            if (i < n) x = max(x , a[i + 1][j]);
            if (j < m) x = max(x , a[i][j + 1]);
            printf("%d%c" , x , " \n"[j == m]);
        }
    }
    return 0;
}
