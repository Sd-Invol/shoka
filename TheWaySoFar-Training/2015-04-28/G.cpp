#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 5;

int n , m , K , Q;
char g[N][N] , A[N];
int next[4][N][N][6];
int dx[] = {0 , 1 , 0 , -1} , dy[] = {1 , 0 , -1 , 0};
int dir[N] , step[N];
int main() {
    char com[10];
    int i , j , k , l , x , y , z;
    
    scanf("%d%d",&n,&m);
    for (i = 1 ; i <= n ; ++ i)
        scanf("%s" , g[i] + 1);
    for (i = 1 ; i <= n ; ++ i)
        for (j = 1 ; j <= m ; ++ j)
            if (g[i][j] == '#')
                g[i][j] = '0';
    memset(next , 0x3f , sizeof(next));
    for (i = 1 ; i <= n ; ++ i)
        for (j = 1 ; j <= m ; ++ j) {
            for (k = 0 ; k < 6 ; ++ k) {
                next[2][i][j][k] = next[2][i][j - 1][k] + 1;
                next[3][i][j][k] = next[3][i - 1][j][k] + 1;
            }
            if (isdigit(g[i][j - 1]))
                next[2][i][j][g[i][j - 1] - '0'] = 1;
            if (isdigit(g[i - 1][j]))
                next[3][i][j][g[i - 1][j] - '0'] = 1;
        }
    for (i = n ; i > 0 ; -- i)
        for (j = m ; j > 0 ; -- j) {
            for (k = 0 ; k < 6 ; ++ k) {
                next[0][i][j][k] = next[0][i][j + 1][k] + 1;
                next[1][i][j][k] = next[1][i + 1][j][k] + 1;
            }
            if (isdigit(g[i][j + 1]))
                next[0][i][j][g[i][j + 1] - '0'] = 1;
            if (isdigit(g[i + 1][j]))
                next[1][i][j][g[i + 1][j] - '0'] = 1;
        }
    scanf("%d" , &K);
    for (i = 0 ; i < K ; ++ i) {
        scanf("%s%d" , com , &step[i]);
        if (*com == 'R') dir[i] = 0;
        if (*com == 'D') dir[i] = 1;
        if (*com == 'L') dir[i] = 2;
        if (*com == 'U') dir[i] = 3;
    }
    scanf("%s" , A);
    Q = strlen(A);
    int res = 0;
    for (i = 1 ; i <= n ; ++ i) {
        for (j = 1 ; j <= m ; ++ j) {
            if (g[i][j] == '0')
                continue;
            l = 0 , x = i , y = j;
            while (l < K) {
                int d = dir[l];
                if (next[d][x][y][0] <= step[l])
                    break;
                x += step[l] * dx[d];
                y += step[l] * dy[d];
                if (x < 1 || x > n || y < 1 || y > m)
                    break;                
                ++ l;
            }
            if (l < K)
                continue;
            //printf("?%d %d\n" , i , j);
            k = 0 , l = 0 , x = i , y = j , z = step[l];
            
            if (g[x][y] == A[k])
                ++ k;
            while (k < Q && l < K) {
                int c = A[k] - '0' , d = dir[l];
                //printf("%d %d %d %d %d\n" , x , y , d , c , z);
                if (next[d][x][y][c] <= z) {
                    z -= next[d][x][y][c];
                    x += next[d][x][y][c] * dx[d];
                    y += next[d][x][y][c] * dy[d];
                    ++ k;
                    if (z == 0)
                        z = step[++ l];
                } else {
                    x += z * dx[d];
                    y += z * dy[d];
                    z = step[++ l];
                }
            }
            if (k >= Q) {
                ++ res;
                //printf("+%d %d\n" , i , j);
            }
        }
    }
    cout << res << endl;
    return 0;            
}
