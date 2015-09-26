#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
#include <map>
#include <set>
#include <queue>
using namespace std;
typedef long long LL;
const int N = 5005;
const int M = 200005;
int n , m , cnt , ca;
int cost[256];
int u[N][2] , id[N];

int s , t;
struct arc {
    int x , f , next;
}e[M];
int pre[N] , mcnt;
void addarc(int x ,int y ,int z) {
    e[mcnt] = (arc) {y , z , pre[x]} , pre[x] = mcnt ++;
    e[mcnt] = (arc) {x , 0 , pre[y]} , pre[y] = mcnt ++;
}
int d[N] , cur[N] , q[N];
bool BFS() {
    memset(d , -1 , sizeof(d));
    int top = 0 , bot = -1;
    q[++ bot] = s , d[s] = 1;
    while (top != bot + 1) {
        int x = q[top ++];
        for (int i = pre[x] ; ~i ;i = e[i].next) {
            int y = e[i].x;
            if (!~d[y] && e[i].f) {
                d[y] = d[x] + 1 , q[++ bot] = y;
                if (y == t) return 1;
            }
        }
    }
    return 0;
}
int DFS(int x , int flow = 1 << 29) {
    if (x == t || !flow)
        return flow;           
    int sum = 0 , u;
    for (int& i = cur[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (d[y] == d[x] + 1 && (u = DFS(y , min(flow , e[i].f)))) {
            e[i].f -= u , e[i ^ 1].f += u;
            sum += u , flow -= u;
            if (!flow) break;
        }
    }
    if (!sum) d[x] = -1;
    return sum;
}

void work() {
    printf("Case #%d: " , ++ ca);
    scanf("%d%d" , &n , &m);
    memset(pre , -1 , sizeof(pre));
    mcnt = 0;
    s = 1 , t = 2;
    cnt = 2;
    memset(u , 0 , sizeof(u));
    for (int i = 0 ; i < n ; ++ i) {
        int val;
        scanf("%d" , &val);
        int x = s;
        for (int k = 7 ; k >= 0 ; -- k) {
            int c = val >> k & 1;
            if (!u[x][c]) {
                ++ cnt;
                id[cnt] = mcnt;
                addarc(x , cnt , 1 << 29);
                u[x][c] = cnt;
            }
            x = u[x][c];
        }
        int y = t;
        for (int k = 0 ; k < 8 ; ++ k) {
            int c = val >> k & 1;
            if (!u[y][c]) {
                ++ cnt;                    
                id[cnt] = mcnt;
                addarc(cnt , y , 1 << 29);
                u[y][c] = cnt;
            }
            y = u[y][c];
        }
        addarc(x , y , 1 << 29);
    }
    for (int i = 0 ; i < m ; ++ i) {
        char dir[20];
        char num[20];
        int w;
        scanf("%s%s%d" , dir , num , &w);
        int len = strlen(num);  
        if (*dir == 'P') {
            int x = s;
            for (int j = 0 ; j < len ; ++ j) {
                int c = num[j] - '0';                
                x = u[x][c];
            }
            if (x)
                e[id[x]].f = min(w , e[id[x]].f);
        } else {
            int x = t;
            for (int j = len - 1 ; j >= 0 ; -- j) {
                int c = num[j] - '0';                
                x = u[x][c];
            }
            if (x)
                e[id[x]].f = min(w , e[id[x]].f);        
        }
    }
    int ans = 0;
    while (BFS()) {
        memcpy(cur , pre , sizeof(cur));
        int flow = DFS(s);
        if (flow == 1 << 29) {
            puts("-1");
            return;
        }
        ans += flow;
    }
    printf("%d\n" , ans);
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}

