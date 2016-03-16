#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int N = 1005;
int n , m;
char str[N];
int A[N] , B[N] , C[N];
int cost[N][N];

int S , T , pre[N] , mcnt;
struct arc {
    int x , f , c , next;
} e[N * N * 2];

inline void addarc(int x , int y , int z , int c) {
    e[mcnt] = (arc) {y , z , c , pre[x]} , pre[x] = mcnt ++;
    e[mcnt] = (arc) {x , 0 ,-c , pre[y]} , pre[y] = mcnt ++;
}

int maxflow , ans , d[N];
bool f[N];
bool Bellman_Ford() {
    queue<int> Q;
    memset(f , 0 , sizeof(f));
    for (int i = 0; i <= T ; ++ i)
        d[i] = 1 << 30;
    d[T] = 0 , f[T] = 1 , Q.push(T);
    while (!Q.empty()){
        int x = Q.front() ; Q.pop() ; f[x] = 0;
        for (int i = pre[x] ; ~i ; i = e[i].next) {
            int y = e[i].x;
            if (e[i ^ 1].f && d[y] > d[x] + e[i ^ 1].c){
                d[y] = d[x] + e[i ^ 1].c;
                if (!f[y]) {
                    Q.push(y);
                    f[y] = 1;
                }
            }
        }
    }
    return d[S] != 1 << 30;
}
int dfs(int x , int flow = 1 << 30) {
    if (x == T) {
        maxflow += flow , ans += d[S] * flow;
        return flow;
    }
    f[x] = 1; int cnt = 0 , u;
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        int y = e[i].x , u;
        if (e[i].f && !f[y] && d[y] + e[i].c == d[x]) {
            u = dfs(y , min(flow , e[i].f));
            e[i].f -= u , e[i ^ 1].f += u;
            flow -= u , cnt += u;
            if (!flow) break;
        }
    }
    return cnt;
}
void MincostMaxflow() {
    maxflow = 0 , ans = 0;   
    while (Bellman_Ford()) {
        do {
            memset(f , 0 , sizeof(f));
        } while (dfs(S));
    }
}


int main() {
    freopen("jackpot.in" , "r" , stdin);
    freopen("jackpot.out" , "w" , stdout);

    while (scanf("%d" , &n) , n) {
        scanf("%d" , &n);
        scanf("%s" , str);
        scanf("%d" , &m);
        for (int i = 0 ; i < m ; ++ i) {
            scanf("%d%d%d" , A + i , B + i , C + i);        
        }
        mcnt = 0;
        memset(pre , -1 , sizeof(pre));
        int x = 0 , y = 0 , z = 0;
        S = n + m , T = S + 1;
        for (int i = 0 ; i < n ; ++ i) {
            for (int j = 0 ; j < m ; ++ j) {
                int aa = max(A[j] - x , 0);
                int bb = max(B[j] - y , 0);
                cost[i][j] = max(0 , aa + bb - z);
                addarc(i , n + j , 1 , cost[i][j]);
                //printf("%d %d : %d\n" , i , j , cost[i][j]);
            }
            if (str[i] == 'W') ++ x;
            if (str[i] == 'B') ++ y;
            if (str[i] == '*') ++ z;
            addarc(S , i , 1 , 0);
        }
        for (int i = 0 ; i < m ; ++ i)
            addarc(n + i , T , C[i] , 0);    
        MincostMaxflow();
        cout << ans << endl;
    }
    return 0;
}
