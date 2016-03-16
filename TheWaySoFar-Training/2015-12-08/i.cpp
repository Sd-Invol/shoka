#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int N = 2005;
const int M = 1000005;
int n , P , A , B , C;
int a[N] , b[N] , c[N];

int s , t , pre[N] , mcnt;
struct arc {
    int x , f , next;
}e[M];
void addarc(int x , int y , int z) {
    e[mcnt] = (arc) {y , z , pre[x]} , pre[x] = mcnt ++;
    e[mcnt] = (arc) {x , 0 , pre[y]} , pre[y] = mcnt ++;
}
int d[N] , cur[N] , q[N];
bool BFS() {
    memset(d , -1 , sizeof(d));
    int top = 0 , bot = -1;
    q[++ bot] = t , d[t] = 1;
    while (top != bot + 1) {
        int x = q[top ++];
        for (int i = pre[x] ; ~i ;i = e[i].next) {
            int y = e[i].x;
            if (!~d[y] && e[i ^ 1].f) {
                d[y] = d[x] + 1 , q[++ bot] = y;
                if (y == s) return 1;
            }
        }
    }
    return 0;
}
int DFS(int x , int flow = 1 << 30) {
    if (x == t || !flow) return flow;
    int sum = 0 , u;
    for (int& i = cur[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (d[x] == d[y] + 1 && (u = DFS(y , min(flow , e[i].f)))) {
            e[i].f -= u , e[i ^ 1].f += u;
            sum += u , flow -= u;
            if (!flow) break;
        }
    }
    if (!sum) d[x] = -1;
    return sum;
}
int dinic() {
    int ans = 0;
    while (BFS()) {
        memcpy(cur , pre , sizeof(cur));
        ans += DFS(s);
    }
    return ans;
}

int main() {
    scanf("%d%d%d%d%d" , &n , &P , &A , &B , &C);
    s = n + 256 * 3 , t = s + 1;
    for (int i = 0 ; i < n ; ++ i)
        scanf("%d%d%d" , a + i , b + i , c + i);
    memset(pre , -1 , sizeof(pre));
    for (int i = 0 ; i < n ; ++ i) {
        addarc(i , n + a[i] , 1 << 30);
        addarc(i , n + 256 + b[i] , 1 << 30);
        addarc(i , n + 256 + 256 + c[i] , 1 << 30);        
        addarc(s , i , P);
    }
    for (int i = 0 ; i < 256 ; ++ i) {
        addarc(n + i , t , A);
        addarc(n + i + 256 , t , B);
        addarc(n + i + 512 , t , C);        
    }
    printf("%d\n" , P * n - dinic());
    return 0;
}
