#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 30;
char g[N][N];
int a[N][N];
int type[N];
int s[5][5][5];

inline bool check(int x , int y , int z) {
    if (s[x][y][z]) return 0;
    if (x < 1 || x > 3) return 0;
    if (y < 1 || y > 3) return 0;
    if (z < 1 || z > 3) return 0;
    return 1;
}

bool dfs(int k , int x , int y , int z , int dx , int dy , int dz) {
    if (k > 27)
        return 1;

    if (type[k]) {
        if (check(x + dx , y + dy , z + dz)) {
            s[x + dx][y + dy][z + dz] = k;
            if (dfs(k + 1 , x + dx , y + dy , z + dz , dx , dy , dz))
                return 1;
            s[x + dx][y + dy][z + dz] = 0;
        }
    } else {
        if (!dx) {
            if (check(x + 1 , y , z)) {
                s[x + 1][y][z] = k;
                if (dfs(k + 1 , x + 1 , y , z , 1 , 0 , 0))
                    return 1;
                s[x + 1][y][z] = 0;
            }
            if (check(x - 1 , y , z)) {
                s[x - 1][y][z] = k;
                if (dfs(k + 1 , x - 1 , y , z , -1 , 0 , 0))
                    return 1;
                s[x - 1][y][z] = 0;
            }
        }
        if (!dy) {
            if (check(x , y + 1 , z)) {
                s[x][y + 1][z] = k;
                if (dfs(k + 1 , x , y + 1 , z , 0 , 1 , 0))
                    return 1;
                s[x][y + 1][z] = 0;
            }
            if (check(x , y - 1 , z)) {
                s[x][y - 1][z] = k;
                if (dfs(k + 1 , x , y - 1 , z , 0 , -1 , 0))
                    return 1;
                s[x][y - 1][z] = 0;
            }
        }
        if (!dz) {
            if (check(x , y , z + 1)) {
                s[x][y][z + 1] = k;
                if (dfs(k + 1 , x , y , z + 1 , 0 , 0 , 1))
                    return 1;
                s[x][y][z + 1] = 0;
            }
            if (check(x , y , z - 1)) {
                s[x][y][z - 1] = k;
                if (dfs(k + 1 , x , y , z - 1 , 0 , 0 , -1))
                    return 1;
                s[x][y][z - 1] = 0;
            }
        }
    }
    return 0;
}

void work() {
    int i , j , k , x , y , dx , dy;
    for (i = 1 ; i <= 15 ; ++ i)
        scanf("%s" , g[i] + 1);
    for (i = 1 ; i <= 15 ; ++ i)
        for (j = 1 ; j <= 15 ; ++ j) {
            if (g[i][j] == 'A')
                x = i , y = j;
            if (isupper(g[i][j]))
                a[i][j] = 2 * (g[i][j] - 'A') + 1;
            if (islower(g[i][j]))
                a[i][j] = 2 * (g[i][j] - 'a' + 1);
        }
    type[1] = 1;
    for (i = -1 ; i <= 1 ; ++ i)
        for (j = -1 ; j <= 1 ; ++ j)
            if (a[x + i][y + j] == 2) {
                dx = i;
                dy = j;
            }
    for (k = 2 ; k <= 27 ; ++ k) {
        if (a[x + dx][y + dy] == k) {
            type[k] = 1;
        } else {
            type[k] = 0;
            for (i = -1 ; i <= 1 ; ++ i)
                for (j = -1 ; j <= 1 ; ++ j)
                    if (a[x + i][y + j] == k) {
                        dx = i;
                        dy = j;
                    }
        }
        x += dx , y += dy;
    }

    assert(dfs(1 , 1 , 1 , 0 , 0 , 0 , 1) ||
           dfs(1 , 1 , 2 , 1 , 0 , 0 , 1) ||
           dfs(1 , 2 , 1 , 1 , 0 , 0 , 1) ||
           dfs(1 , 2 , 0 , 2 , 0 , 1 , 0));
    for (i = 1 ; i <= 3 ; ++ i) {
        for (j = 1 ; j <= 3 ; ++ j) {
            for (k = 1 ; k <= 3 ; ++ k) {
                if (s[i][j][k] & 1) {
                    printf("%c" , 'A' + (s[i][j][k] >> 1));
                } else {
                    printf("%c" , 'a' + (s[i][j][k] >> 1) - 1);
                }
            }
            putchar(" \n"[j == 3]);
        }
    }


}

int main() {
    freopen("folding.in" , "r" , stdin);
    freopen("folding.out" , "w" , stdout);

    work();
    return 0;
}
