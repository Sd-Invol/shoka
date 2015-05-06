#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 100005;
int n , m , ca;
LL a[N] , b[N];

bool dfs(int k , int x , int y) {
    if (!x) {
        return k;
    }
    if (!y) {
        return !k;
    }
    
    if (!k) {
        if (a[x - 1] > b[y - 1])
            if (!dfs(!k , x , y - 1))
                return 1;
        if (x > 1) {
            a[x - 2] += a[x - 1];
            if (!dfs(!k , x - 1 , y)) {
                a[x - 2] -= a[x - 1];
                return 1;
            }
            a[x - 2] -= a[x - 1];        
        }
        return 0;
    } else {
        if (b[y - 1] > a[x - 1])
            if (!dfs(!k , x - 1 , y))
                return 1;
        if (y > 1) {
            b[y - 2] += b[y - 1];
            if (!dfs(!k , x , y - 1)) {
                b[y - 2] -= b[y - 1];        
                return 1;
            }
            b[y - 2] -= b[y - 1];        
        }
        return 0;
    }
}

void work() {
    int i , j , k , x , y;
    for (int i = 0 ; i < n ; ++ i) {
        scanf("%lld" , &a[i]);
    }
    sort(a , a + n);
    for (int j = 0 ; j < m ; ++ j) {
        scanf("%lld" , &b[j]);
    }
    sort(b , b + m);
    printf("Case %d: %s\n" , ++ ca , dfs(0 , n , m) ? "Takeover Incorporated" : "Buyout Limited");
}

int main() {
    while (~scanf("%d%d",&n,&m))
        work();
    return 0;
}
