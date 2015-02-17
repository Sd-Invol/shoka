#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 1505;
int n , m;
char g[N][N];
int id[N][N] , f[N * N];
int a[N][N] , b[N][N] , c[N][N];
int getf(int x) {
    return f[x] == x ? x : f[x] = getf(f[x]);
}
inline void merge(int x , int y) {
    f[getf(x)] = getf(y);
}
int get(int A[][N] , int x , int y , int k) {
    -- x , -- y;
    return A[x + k][y + k] - A[x][y + k] - A[x + k][y] + A[x][y];
}

void work() {
    int i , j;
    scanf("%d%d",&m,&n);
    for (i = 1 ; i <= n ; ++ i)
        scanf("%s" , g[i] + 1);
    int num = 0;
    for (i = 1 ; i <= n ; ++ i)
        for (j = 1 ; j <= m ; ++ j) {
            id[i][j] = ++ num;
            f[num] = num;
        }
    f[num + 1] = num + 1;
    f[num + 2] = num + 2;
    
    for (i = 1 ; i <= n ; ++ i) {
        for (j = 1 ; j <= m ; ++ j) {
            if (g[i][j] != '#') continue;
            if (i == 1 || j == m) merge(id[i][j] , num + 1);
            if (j == 1 || i == n) merge(id[i][j] , num + 2);
            if (i > 1 && g[i - 1][j] == '#')
                merge(id[i - 1][j] , id[i][j]);
            if (i > 1 && j < m && g[i - 1][j + 1] == '#')
                merge(id[i - 1][j + 1] , id[i][j]);
            if (j > 1 && i > 1 && g[i - 1][j - 1] == '#')
                merge(id[i - 1][j - 1] , id[i][j]);
            if (j > 1 && g[i][j - 1] == '#')
                merge(id[i][j - 1] , id[i][j]);            
        }
    }
    c[1][1] = c[n][m] = 1;
    for (i = 1 ; i <= n ; ++ i)
        for (j = 1 ; j <= m ; ++ j) {
            if (g[i][j] == '#')
                c[i][j] = 1;
            for (int k = 0 ; k < 9 ; ++ k) {
                int x = i + (k / 3) - 1;
                int y = j + (k % 3) - 1;
                if (x < 1 || y > m || getf(id[x][y]) == getf(num + 1))
                    a[i][j] = 1;
                if (y < 1 || x > n || getf(id[x][y]) == getf(num + 2))
                    b[i][j] = 1;                                    
            }
        }
    for (i = 1 ; i <= n ; ++ i)
        for (j = 1 ; j <= m ; ++ j) {
            a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
            b[i][j] += b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1];
            c[i][j] += c[i - 1][j] + c[i][j - 1] - c[i - 1][j - 1];     
        }
    pair<int , int> res(1 << 30 , -1);
    for (i = 1 ; i <= n ; ++ i)
        for (j = 1 ; j <= m ; ++ j) {
            int l = 1 , r = min(n - i + 1 , m - j + 1) + 1 , mid;
            while (l < r) {
                mid = l + r >> 1;
                if (get(a , i , j , mid) && get(b , i , j , mid))
                    r = mid;
                else
                    l = mid + 1;
            }
            if (l == min(n - i + 1 , m - j + 1) + 1)
                continue;
            if (get(c , i , j , l))
                continue;
            res = min(res , make_pair(l , id[i][j]));
        }
    if (res.first == 1 << 30)
        puts("Impossible");
    else {
        printf("%d " , res.first);
        int x = (res.second - 1) / m + 1;
        int y = (res.second - 1) % m + 1;
        printf("%d %d\n" , y , x);
    }
}

int main() {
    freopen("labyrinth.in" , "r" , stdin);
    freopen("labyrinth.out" , "w" , stdout);
    work();
    return 0;
}