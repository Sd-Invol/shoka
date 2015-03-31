#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 101;

int n , m , K;
char g[N][N];
void work() {
    int i , j;
    cin >> n >> m >> K;
    int x = 0 , y = 0;
    for (i = 0 ; i < K ; ++ i) {
        cin >> j;
        while (j --) {
            g[x][y] = '1' + i;
            ++ x;
            if (x == n) {
                ++ y;
                x = 0;
            }
        }
    }
    for (i = 0 ; i < n ; ++ i)
        puts(g[i]);
}

int main() {
    freopen("addictive.in" , "r" , stdin);
    freopen("addictive.out" , "w" , stdout);
    work();
    return 0;
}
