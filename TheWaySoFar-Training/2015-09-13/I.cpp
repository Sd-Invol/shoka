#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <queue>
#include <vector>
#include <bitset>
#include <cctype>
#include <map>
using namespace std;
typedef long long LL;
const int N = 50105;
int n , m , P;
int f[2][N] , g[2][N];
void work() {
    scanf("%d%d%d" , &n , &m , &P);
    P += 100;

    int cur = 0 , nxt = 1;
    memset(f[cur] , 0x3f , sizeof(f[cur]));
    f[cur][0] = 0;
    for (int i = 0 ; i < n ; ++ i) {
        int v , w , c;
        scanf("%d%d%d" , &w , &v , &c);
        for (int l = 0 ; l < w ; ++ l) {
            static int q[N];
            int top = 0 , bot = -1;
            for (int j = l ; j <= P ; j += w) {
                while (top <= bot && f[cur][j] - j / w * v <= f[cur][q[bot]] - q[bot] / w * v)
                    -- bot;
                q[++ bot] = j;
                while (top <= bot && j - q[top] > c * w)
                    ++ top;
                f[nxt][j] = f[cur][q[top]] + (j - q[top]) / w * v;
            }
        }
        swap(cur , nxt);
    }
    memcpy(f[0] , f[cur] , sizeof(f[0]));

    cur = 0 , nxt = 1;
    memset(g[cur] , 0xC0 , sizeof(g[cur]));
    g[cur][0] = 0;
    for (int i = 0 ; i < m ; ++ i) {
        int v , w , c;
        scanf("%d%d%d" , &v , &w , &c);
        for (int l = 0 ; l < w ; ++ l) {
            static int q[N];
            int top = 0 , bot = -1;
            for (int j = l ; j <= 50000 ; j += w) {
                while (top <= bot && g[cur][j] - j / w * v >= g[cur][q[bot]] - q[bot] / w * v)
                    -- bot;
                q[++ bot] = j;
                while (top <= bot && j - q[top] > c * w)
                    ++ top;
                g[nxt][j] = g[cur][q[top]] + (j - q[top]) / w * v;
            }
        }
        swap(cur , nxt);
    }
    int res = 1 << 30;
    P -= 100;
    for (int i = P ; i <= P + 100 ; ++ i) {
        int x = f[0][i];
        for (int j = 0 ; j <= 50000 ; ++ j)
            if (g[cur][j] >= x) {
                res = min(res , j);
            }
    }
    if (res == 1 << 30)
        puts("TAT");
    else
        printf("%d\n" , res);
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}
