#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 10005;
int n , K , Lev;
int f[15][N] , size[15] , p[15][N];
int a[15] , m , res[15] , w;
bool vis[N];
bool cmp(int x , int y) {
    char str[5];
    printf("? %d %d\n" , x , y);
    fflush(stdout);
    
    scanf("%s" , str);
    return *str == '<';
}

void insert(int x) {
    //printf("+%d\n" , x);
    //printf("--%d\n" , m);
    int i;
    //for (i = 1 ; i <= m ; ++ i)
    //    printf("%d%c" , a[i] , " \n"[i == m]);
    for (i = m ; i > 0 ; -- i)
        if (cmp(x , a[i])) 
            a[i + 1] = a[i];
        else
            break;
    a[i + 1] = x;
    m = min(m + 1 , w);         
}

int main() {
    int i , j , k , x , y;
    scanf("%d%d" , &n,&K);
    size[0] = n;
    for (i = 1 ; i <= n ; ++ i)
        f[0][i] = i;
    j = 1;
    while (1) {
        for (i = 1 ; i <= size[j - 1] ; i += 2) {
            if (i + 1 > size[j - 1])
                x = f[j - 1][i];
            else {
                k = cmp(f[j - 1][i] , f[j - 1][i + 1]);
                if (k)
                    x = f[j - 1][i];
                else
                    x = f[j - 1][i + 1];
            }
            f[j][++ size[j]] = x;
        }
        if (size[j] == 1)
            break;
        ++ j;
    }
    Lev = j;
    for (i = 0 ; i <= Lev ; ++ i)
        for (j = 1 ; j <= size[i] ; ++ j)
            p[i][f[i][j]] = j;
    //puts("END");
    a[++ m] = f[Lev][1] , vis[0] = 1;
    for (k = 1 ; k <= K ; ++ k) {
        res[k] = x = a[1];
        vis[x] = 1;
        for (i = 2 ; i <= m ; ++ i)
            a[i - 1] = a[i];
        //printf("%d\n" , x);
        -- m;
        w = K - k;
        for (j = 1 ; j <= Lev ; ++ j)
            if (p[j][x]) {
                i = p[j][x];
                if (!vis[f[j - 1][i + i]])
                    insert(f[j - 1][i + i]);
                if (!vis[f[j - 1][i + i - 1]])
                    insert(f[j - 1][i + i - 1]);
            }
    }
    printf("! ");
    for (i = 1 ; i <= K ; ++ i)
        printf("%d%c" , res[i] , " \n"[i == K]);
    fflush(stdout);
    return 0;    
}
