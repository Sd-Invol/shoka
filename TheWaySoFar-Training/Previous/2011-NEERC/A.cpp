#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 105;
int n , m;
char g[N];

void work() {
    int i , j , res = 0;
    scanf("%d%d",&n,&m);
    for (i = 0 ; i < n ; ++ i) {
        scanf("%s" , g);
        int x = 0;
        for (j = 0 ; j < m ; ++ j) {
            if (g[j] != '.') {
                x ^= 1;
                res ++;
            } else {
                res += x + x;
            }
        }
    }
    printf("%d\n" , res >> 1);
}

int main() {
    freopen("ascii.in" , "r" , stdin);
    freopen("ascii.out" , "w" , stdout);

    work();
    return 0;
}
