#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 50;
int n;
int a[N] , b[N];
void work() {
    int i , j , k , l , x , y;
    scanf("%d",&n);
    for (i = 1 ; i <= n ; ++ i)
        a[i] = i;
    for (i = 1 ; i <= n ; ++ i) {
        pair<int , int> mx;
        x = 0;
        for (j = 1 ; j <= n ; ++ j)
            if (a[j] != i)
                b[++ x] = a[j];
        for (j = 1 ; j <= n ; ++ j) {
            for (k = 1 ; k < j ; ++ k)
                printf("%d " , b[k]);
            printf("%d " , i);
            for (k = j ; k < n ; ++ k)
                printf("%d " , b[k]);
            puts(""); fflush(stdout);
            scanf("%d",&x);
            if (x == n) return;
            mx = max(mx , make_pair(x , j));
        }
        x = 0 , j = mx.second;
        for (k = 1 ; k < j ; ++ k)
            a[++ x] = b[k];
        a[++ x] = i;
        for (k = j ; k < n ; ++ k)
            a[++ x] = b[k];
    }
}

int main() {
    //freopen("1" , "r" , stdin);
    work();
    return 0;
}
