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

#define N 1005
int n , m , k;
int ans , a[N];

void dfs(int d)
{
    if (d > n)
    {
        int mn = 1 << 30 , mx = -1 << 30;
        for (int i = 1 ; i <= n ; ++ i)
            mn = min(mn , a[i]) , mx = max(mx , a[i]);
        if (mx - mn == k) ++ ans;
        return;
    }
    for (int i = 1 ; i <= m ; ++ i)
        a[d] = i , dfs(d + 1);
}

void work()
{
    ans = 0;
    dfs(1);
    printf("%7d" , ans);
}

int main()
{
    //freopen("~input.txt" , "r" , stdin);
    //int _; scanf("%d",&_); while (_ --)
    //while (~scanf("%d",&n))
    for (k = 1 ; k <= 7 ; ++ k){
    for (n = 2 ; n <= 7 ; ++ n)
    {
        m = k + 1;
       // for (m = 1 ; m <= 7 ; ++ m)
        {
            work();
        }
      //  printf("\n");
    } printf("\n");
    }
    //while (cin >> n >> m >> k)

    return 0;
}
