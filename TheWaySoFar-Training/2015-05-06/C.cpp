#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 205;
int n , m , ca;
int f[N * N] , num[N][N];
char str[N];
bool g[N][N] , v[N][N];
char ch[10] = "?WAKJSD";
char res[N] ;
int ret;
int getf(int x) {
    return x == f[x] ? x : f[x] = getf(f[x]);
}
void merge(int x , int y) {
    f[getf(x)] = getf(y);
}
set<int> Hash;
void dfs(int x , int y) {
    if (x == 0 || x == n + 1 || y == 0 || y == m + 1) {
        Hash.insert(getf(0));
        return;
    }
    if (!g[x][y]) {
        Hash.insert(getf(num[x][y]));
        return;    
    }
    if (v[x][y])
        return;
    v[x][y] = 1;
    dfs(x - 1 , y);
    dfs(x + 1 , y);
    dfs(x , y - 1);
    dfs(x , y + 1);    
}

void work() {
    int i , j , k;
    m <<= 2;
    memset(g , 0 , sizeof(g));
    for (i = 1 ; i <= n ; ++ i) {
        scanf("%s" , str);
        int cnt = 0;
        for (j = 0 ; str[j] ; ++ j) {
            int x = isdigit(str[j]) ? str[j] - '0' : str[j] - 'a' + 10;
            g[i][++ cnt] = x >> 3 & 1;
            g[i][++ cnt] = x >> 2 & 1;
            g[i][++ cnt] = x >> 1 & 1;
            g[i][++ cnt] = x >> 0 & 1;            
        }
    }
    int cnt = 0;
    f[0] = 0;
    for (i = 1 ; i <= n ; ++ i)
        for (j = 1 ; j <= m ; ++ j) {
            ++ cnt;
            f[cnt] = cnt;
            num[i][j] = cnt;
        }
    for (i = 1 ; i <= n ; ++ i) {
        for (j = 1 ; j <= m ; ++ j) {
            if (!g[i][j]) {
                if (i == 1 || i == n || j == 1 || j == m)
                    merge(num[i][j] , 0);
                if (i > 1 && !g[i - 1][j])
                    merge(num[i][j] , num[i - 1][j]);
                if (j > 1 && !g[i][j - 1])
                    merge(num[i][j] , num[i][j - 1]);
            }
        }        
    }
    memset(v , 0 , sizeof(v));
    ret = 0;
    for (i = 1 ; i <= n ; ++ i)
        for (j = 1 ; j <= m ; ++ j) {
            if (g[i][j] && !v[i][j]) {
                Hash.clear();
                dfs(i , j);
                res[ret ++] = ch[Hash.size()];
            }
        }
    res[ret] = 0;
    sort(res , res + ret);
    printf("Case %d: %s\n" , ++ ca , res);
}

int main() {
    while (scanf("%d%d" , &n , &m) , n)
        work();
    return 0;
}
