#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 2005;
const int Q = 1e9 + 7;
int n , m , r , pre[N] , mcnt;
struct edge {
    int x , next;
}e[N << 1];
bool imp[N];
int dist[N][N] , f[N][N] , c[N] , Rank[N];
pair<int , int> a[N] , b[N];

void add(int& A , const int& B) {
    A += B;
    if (A >= Q)
        A -= Q;
}

void dfs(int x , int fa , int *D) {
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (y != fa) {
            D[y] = D[x] + 1;
            dfs(y , x , D);
        }
    }
}

void DFS(int x , int fa) {
    int i , j , k ,  y;
    for (i = pre[x] ; ~i ; i = e[i].next) {
        y = e[i].x;
        if (y != fa)
            DFS(y , x);
    }
    for (i = 1 ; i <= n ; ++ i)
        if (!imp[x] || dist[x][i] <= r)
            f[x][i] = 1;
    for (i = pre[x] ; ~i ; i = e[i].next) {
        y = e[i].x;        
        if (y != fa) {
            for (j = 1 ; j <= n ; ++ j) {
                a[j] = make_pair(dist[x][j] , j);
                b[j] = make_pair(dist[y][j] , j);                
            }
            memset(c , 0 , sizeof(c));
            /*
            for (j = 1 ; j <= n ; ++ j) {
                for (k = 1 ; k <= n ; ++ k) {
                    if (a[j] <= a[k] && b[k] <= b[j]) {
                        add(c[j] , f[y][k]);
                    }
                }
                }            
            for (j = 1 ; j <= n ; ++ j)
                f[x][j] = (LL)f[x][j] * c[j] % Q;
            */
            sort(a + 1 , a + n + 1);
            sort(b + 1 , b + n + 1);
            for (j = 1 ; j <= n ; ++ j)
                Rank[a[j].second] = j;
            for (j = 1 ; j <= n ; ++ j) {
                int z = b[j].second;
                for (k = Rank[z] ; k > 0 ; k -= k & -k)
                    c[k] += f[y][z] , c[k] %= Q;
                LL sum = 0;
                for (k = Rank[z] ; k <= n ; k += k & -k)
                    sum += c[k] , sum %= Q;
                f[x][z] = f[x][z] * sum % Q;
            }
        }
    }
}

void work() {
    int i , x , y;
    scanf("%d%d%d",&n,&m,&r);
    memset(pre , -1 , sizeof(pre));
    for (i = 1 ; i <= m ; ++ i) {
        scanf("%d" , &x);
        imp[x] = 1;
    }
    for (i = 1 ; i < n ; ++ i) {
        scanf("%d%d",&x,&y);
        e[mcnt] = (edge) {y , pre[x]} , pre[x] = mcnt ++;
        e[mcnt] = (edge) {x , pre[y]} , pre[y] = mcnt ++;        
    }
    for (i = 1 ; i <= n ; ++ i)
        dfs(i , 0 , dist[i]); 
    DFS(1 , 0);
    int res = 0;
    for (i = 1 ; i <= n ; ++ i)
        add(res , f[1][i]);
    if (m == 0)
        add(res , 1);
    cout << res << endl;
}

int main() {
    work();    
    return 0;
}
