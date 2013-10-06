#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <list>
#define pb push_back
#define mp make_pair
#define fi first
#define se second
//#pragma comment(linker, "/STACK:16777216")
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

#define N 25
int n , m , ans , id[N] , od[N];
char s[N][N];
vector<int> e[N];
int re[N] , f[N];
bool find(int x)
{
    for (int i = 0 ; i < e[x].size() ; ++ i)
    {
        int y = e[x][i];
        if (!f[y])
        {
            f[y] = 1;
            if (!re[y] || find(re[y]))
            {
                re[y] = x;
                return 1;
            }
        }
    }
    return 0;
}

void work()
{
    int i , j , x , y;
    scanf("%d%d",&n,&m);
    for (i = 1 ; i <= n ; ++ i)
        scanf("%s" , s[i] + 1) , e[i].clear();

    for (i = 3 ; i <= n - 2 ; ++ i)
        for (j = 3 ; j <= m - 2 ; ++ j)
        {
            if (s[i][j] == '#' || s[i - 1][j] == '#' || s[i - 2][j] == '#' || s[i + 1][j] == '#' || s[i + 2][j] == '#') continue;
            if (s[i][j - 2] == '#' || s[i][j - 1] == '#' || s[i][j] == '#' || s[i][j + 1] == '#' || s[i][j + 1] == '#') continue;
            e[i].push_back(j);
            printf("%d %d\n" , i , j);
        }
    memset(re , 0 , sizeof(re));
    memset(id , 0 , sizeof(id));
    memset(od , 0 , sizeof(od));
    for (i = 1 ; i <= n ; ++ i)
    {
        memset(f , 0 , sizeof(f));
        ans += find(i);
    }
    for (i = 1 ; i <= n ; ++ i)
    {
        for (j = 0 ; j < e[i].size() ; ++ j)
        {
            x = e[i][j];
            if (re[x] == i)
                ++ od[x];
            else ++ id[x];
        }
    }
    ans = 0;
    for (i = 1 ; i <= m ; ++ i)
    {
        if (!re[i])
            -- ans;
        if (!id[i])
            ++ ans;
    }
    puts(ans & 1 ? "Asuna" : "Kirito");
}


int main()
{
    freopen("~input.txt" , "r" , stdin);
    //freopen("~output.txt" , "w" , stdout);
    int _; scanf("%d",&_); while (_ --)
        work();
    return 0;
}
