#include <bits/stdc++.h>
using namespace std;
const int N = 300005;

int n;
vector<int> e[N];
bool f[N][3];

void dfs(int x) {
    if (e[x].empty())
        return;
    assert(e[x].size() == 2);
    int y = e[x][0] , z = e[x][1];
    dfs(y) , dfs(z);
    for (int i = 0 ; i < 3 ; ++ i)
        for (int j = 0 ; j < 3 ; ++ j) {
            if (!f[y][i]) continue;
            if (!f[z][j]) continue;
            for (int k = 0 ; k < 3 ; ++ k)
                if (k != i && k != j)
                    f[x][k] = 1;
        }
}
int c[N];
void DFS(int x , int w) {
    c[x] = w;
    if (e[x].empty())
        return;
    assert(e[x].size() == 2);
    int y = e[x][0] , z = e[x][1];
    for (int i = 0 ; i < 3 ; ++ i)
        for (int j = 0 ; j < 3 ; ++ j) {
            if (!f[y][i]) continue;
            if (!f[z][j]) continue;
            for (int k = 0 ; k < 3 ; ++ k)
                if (k != i && k != j && k == w) {
                    DFS(y , i);
                    DFS(z , j);
                    return;
                }
        }
}


void work() {
    int i , j , k , x , y , z , p;
    for (i = 1 ; i <= n ; ++ i) {
        e[i].clear();
        f[i][0] = f[i][1] = f[i][2] = 0;
    }
    for (i = 2 ; i <= n ; ++ i) {
        scanf("%d" , &x);
        e[x].push_back(i);           
    }
    scanf("%d" , &j);
    while (j --) {
        scanf("%d%d",&x,&i);
        f[x][i - 1] = 1;
    }
    assert(e[1].size() == 3);
    x = e[1][0] , y = e[1][1] , z = e[1][2];
    dfs(x) , dfs(y) , dfs(z);
    for (i = 0 ; i < 3 ; ++ i)
        for (j = 0 ; j < 3 ; ++ j)
            for (k = 0 ; k < 3 ; ++ k) {
                if (!f[x][i]) continue;
                if (!f[y][j]) continue;
                if (!f[z][k]) continue;               
                int a[3] = {i , j , k};
                sort(a , a + 3);
                int m = unique(a , a + 3) - a;
                if (m > 2) continue;
                puts("YES");
                DFS(x , i);
                DFS(y , j);
                DFS(z , k);            
                if (m == 1) {
                    c[1] = (a[0] == 0) ? 1 : 0;
                } else {
                    c[1] = 3 - a[0] - a[1];                
                }
                for (i = 1 ; i <= n ; ++ i)
                    printf("%d%c" , c[i] + 1 , " \n"[i == n]);
                return;
            }
    puts("NO");
}

int main() {
    freopen("coloring.in" , "r" , stdin);
    freopen("coloring.out" , "w" , stdout);
    
    while (scanf("%d" , &n) , n)
        work();
    return 0;
}
