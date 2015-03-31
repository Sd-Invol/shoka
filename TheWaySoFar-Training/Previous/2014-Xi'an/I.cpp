#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 1000005;
int ca;

int n;
unsigned int w[30000];
int len[30000];

int u[N][2];
int cnt;
bool vis[N];

vector< pair<unsigned int , int> > res;

void dfs(int x , int d , unsigned int mask) {
    if (vis[x]) return;
    for (unsigned int i = 0 ; i < 2 ; ++ i) {
        int y = u[x][i];
        if (y) {
            dfs(y , d + 1 , mask | i << 31 - d);
        } else {
            res.push_back(make_pair(mask | i << 31 - d , d + 1));
        }
    }
}


void work() {
    int i , j , x;
    printf("Case #%d:\n" , ++ ca);
    scanf("%d",&n);
    if (n == 0) {
        puts("1\n0.0.0.0/0");
        return;
    }
    for (i = 0 ; i < n ; ++ i) {
        unsigned int a[4];
        scanf("%u.%u.%u.%u/%d" , &a[3] , &a[2] , &a[1] , &a[0] , &len[i]);
        w[i] = a[3] << 24 | a[2] << 16 | a[1] << 8 | a[0];
    }
    cnt = 1;
    vis[cnt] = u[cnt][0] = u[cnt][1] = 0;
    for (i = 0 ; i < n ; ++ i) {
        x = 1;
        for (j = 31 ; j >= 32 - len[i] ; -- j) {
            int c = w[i] >> j & 1;
            if (!u[x][c]) {
                u[x][c] = ++ cnt;
                vis[cnt] = u[cnt][0] = u[cnt][1] = 0;
            }
            x = u[x][c];
        }
        vis[x] = 1;
    }
    res.clear();
    dfs(1 , 0 , 0);
    printf("%d\n" , (int)res.size());
    for (auto it : res) {
        unsigned int q = it.first;
        printf("%u.%u.%u.%u/%d\n" , q >> 24 & 255 , q >> 16 & 255 , q >> 8 & 255 , q & 255 , it.second);
    }


}

int main() {
    int _; scanf("%d",&_); while (_ --)
        work();
    return 0;
}
