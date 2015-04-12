#include <bits/stdc++.h>
using namespace std;
const int N = 105;
const int M = 10005;
int n , m , T , pre[N] , mcnt;
struct edge {
    int x , next;
}e[2005];
pair<int , int> E[1005];
stack<int> S;
vector<int> V[N];
bool F[N];
int dfn[N] , low[N] , ncnt , bel[N] , bcnt;
int v[N] , w[N] , c[N];
int f[N][M];

void dfs(int x) {
    dfn[x] = low[x] = ++ ncnt;
    S.push(x) , F[x] = 1;
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (!dfn[y]) {
            dfs(y);
            low[x] = min(low[x] , low[y]);
        } else if (F[y])
            low[x] = min(low[x] , dfn[y]);
    }
    if (low[x] == dfn[x]) {
        ++ bcnt; int i;
        V[bcnt].clear();
        do {
            i = S.top();
            S.pop(); F[i] = 0;
            bel[i] = bcnt;
            V[bcnt].push_back(i);
        } while (i != x);
    }
}

void work() {
    int i , j , x , y;
    memset(pre , -1 , sizeof(pre)) , mcnt = 0;
    for (i = 1 ; i <= n ; ++ i)
        scanf("%d%d%d",&v[i],&w[i],&c[i]);
    for (i = 0 ; i < m ; ++ i) {
        scanf("%d%d" ,&x,&y);
        E[i] = make_pair(x , y);
        e[mcnt] = (edge) {y , pre[x]} , pre[x] = mcnt ++;
    }
    memset(F, 0, sizeof(F));
    memset(dfn , 0 , sizeof(dfn));
    ncnt = bcnt = 0;
    for (i = 1 ; i <= n ; ++ i) {
        if (!dfn[i])
            dfs(i);
    }
    memset(pre , -1 , sizeof(pre));
    mcnt = 0;
    for (i = 0 ; i < m ; ++ i) {
        x = bel[E[i].first];
        y = bel[E[i].second];
        if (x == y) {
            F[x] = 1;
         
            continue;
        }
        e[mcnt] = (edge) {y , pre[x]} , pre[x] = mcnt ++;
    }
    for (int i = 1; i <= bcnt; ++i) {
        if (V[i].size() == 1 && F[i] == 0) {
            c[V[i][0]] = 1;
        }
        // printf("!%d %d\n", V[i].size(), F[i]);
    }
    //memset(f, 0, sizeof(f));
    for (i = 1 ; i <= bcnt ; ++ i)
        for (j = 0 ; j <= T ; ++ j)
            f[i][j] = 0;
    int ans = 0;
    for (x = bcnt ; x > 0 ; -- x) {        
        /**/
        //V
        for (int i = 0; i < V[x].size(); ++i) {
            int v0 = v[V[x][i]], w0 = w[V[x][i]], c0 = c[V[x][i]];
            swap(v0, w0);
            //printf("%d %d %d\n", v0, w0, c0);
            for (int j = 0; j < v0; ++j) {
                static pair<int, int> que[M];
                int head = 1, tail = 0, sum = 0;
                for (int k = j; k <= T; k += v0) {
                    while (head <= tail && f[x][k] - sum * w0 > que[tail].second)
                        --tail;
                    if (head <= tail && que[head].first < k) ++head;
                    que[++tail] = make_pair(k + c0 * v0, f[x][k] - sum * w0);
                    
                    f[x][k] = que[head].second + sum * w0;
                    //  if (f[x][k] == 16) {
                    //    printf("%d\n", que[head].first);
                    //  }
                    ++sum;
                    ans = max(ans, f[x][k]);
                }
            }
        }
        // for (int i = 0; i <= T; ++i)
        //   printf("%d%c", f[x][i], " \n"[i == T]);
        for (int i = pre[x] ; ~i ; i = e[i].next) {
            y = e[i].x;
            for (j = 0 ; j <= T ; ++ j)
                f[y][j] = max(f[y][j] , f[x][j]);
        }
        
    }
    printf("%d\n", ans);
}

int main() {
    while (scanf("%d%d%d" , &n,&m,&T) , n)
        work();
    return 0;
}
