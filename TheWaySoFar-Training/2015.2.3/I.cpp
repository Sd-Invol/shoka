#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1000005;
int n , K;
char g[2][N];

void work() {
    int i , j , x , y;
    scanf("%d%d" , &n,&K);
    scanf("%s%s" , g[0] + 1 , g[1] + 1);
    x = 1 , y = 0;
    int res = 1;
    while (x < n) {
        //printf("%d %d\n" , x , y);
        if (g[y ^ 1][x] == '#') {
            ++ x;
            ++ res;            
        } else {
            if (g[y ^ 1][x + 1] == '#' && K) {
                -- K;
                g[y ^ 1][x + 1] = '.';
            }
            if (g[y ^ 1][x + 1] == '#') {
                ++ res;
                ++ x;                
            } else {
                res += 2;
                ++ x , y ^= 1;            
            }
        }
    }
    int cnt = 0;
    for (i = 1 ; i <= n ; ++ i) {
        cnt += (g[0][i] == '#');
        cnt += (g[1][i] == '#');
    }
    if (y == 0)
        ++ res;
    else {
        if (K && cnt && g[0][n] != '#') {
            res += 2;
            -- K;
            -- cnt;
        }
    }
    while (K > 1 && cnt > 1)
        K -= 2 , cnt -= 2 , res += 2;
    cout << res << endl;
    //puts(g[0] + 1);
    //puts(g[1] + 1);    
}
int main() {
    work();
    return 0;
}
