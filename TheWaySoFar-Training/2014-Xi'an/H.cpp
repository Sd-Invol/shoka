#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 105;
int ca;

int n , m;
bool g[N][N] , f[N][N][2];
int deg[N] , cnt[N][N];

void work() {
    int i , j , x , y;
    printf("Case #%d: " , ++ ca);
    scanf("%d%d",&n,&m);
    for (i = 0 ; i < n ; ++ i) {
        for (j = 0 ; j < n ; ++ j)
            g[i][j] = cnt[i][j] = f[i][j][0] = f[i][j][1] = 0;
        deg[i] = 0;
    }
    for (i = 0 ; i < m ; ++ i) {
        scanf("%d%d",&x,&y);
        -- x , -- y;
        g[x][y] = 1;
        ++ deg[x];
    }
    queue<int> Q;
    for (i = 0 ; i < n ; ++ i) {
        f[i][i][0] = 1;
        Q.push(i * n + i);
        f[i][i][1] = 1;
        Q.push(n * n + i * n + i);
    }

    for (i = 0 ; i < n ; ++ i) {
        if (!deg[i]) {
            for (j = 0 ; j < n ; ++ j) {
                if (i != j) {
                    f[i][j][0] = 1;
                    Q.push(i * n + j);
                }
            }
        }
    }

    while (!Q.empty()) {
        int z = Q.front(); Q.pop();
        i = z / (n * n) , z %= (n * n);
        x = z / n , y = z % n;
        if (i) {
            for (j = 0 ; j < n ; ++ j) {
                if (!g[j][x]) continue;
                ++ cnt[j][y];
                if (cnt[j][y] == deg[j] && !f[j][y][0]) {
                    f[j][y][0] = 1;
                    Q.push(j * n + y);
                }
            }
        } else {
            for (j = 0 ; j < n ; ++ j) {
                if (!g[j][y]) continue;
                if (!f[x][j][1]) {
                    f[x][j][1] = 1;
                    Q.push(n * n + x * n + j);
                }
            }
        }
    }
    scanf("%d%d",&x,&y);
    -- x , -- y;
    puts(f[x][y][0] ? "No" : "Yes");    
}

int main() {
    int _; scanf("%d",&_); while (_ --)
        work();
    return 0;
}



