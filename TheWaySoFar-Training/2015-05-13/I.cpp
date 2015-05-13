#include <bits/stdc++.h>
using namespace std;
const int N = 105;
typedef pair<int , int> Point;
Point operator - (const Point& A , const Point& B) {
    return Point(A.first - B.first , A.second - B.second);
}
int operator ^ (const Point& A , const Point& B) {
    return A.first * B.second - A.second * B.first;
}
int n , D ;
pair<int , int> a[N];
int m , id[N], dis[N][N];
int pre[N] , mcnt;
struct edge {
    int x , f , next;
}e[N * N * 2];
bool mark[N] , f[N];
int s , t , cur[N] , q[N] , d[N] , re[N];
void addarc(int x , int y , int z) {
    e[mcnt] = (edge) {y , z , pre[x]} , pre[x] = mcnt ++;
    e[mcnt] = (edge) {x , 0 , pre[y]} , pre[y] = mcnt ++;
}
bool BFS() {
    int top = 0 , bot = -1;
    memset(d , -1 , sizeof(d));
    d[s] = 1 , q[++ bot] = s;
    while (top <= bot) {
        int x = q[top ++];
        for (int i = pre[x] ; ~i ; i = e[i].next) {
            int y = e[i].x;
            if (e[i].f && !~d[y]) {
                d[y] = d[x] + 1;
                if (y == t)
                    return 1;
                q[++ bot] = y;
            }
        }
    }
    return 0;
}
int dfs(int x , int flow = 1 << 30) {
    if (x == t || !flow)
        return flow;
    int u , sum = 0;
    for (int &i = cur[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (d[y] == d[x] + 1 && (u = dfs(y , min(e[i].f , flow)))) {
            e[i].f -= u , e[i ^ 1].f += u;
            flow -= u , sum += u;
            if (!flow) break;
        }
    }
    if (!sum) d[x] = -1;
    return sum;
}
void DFS(int x) {
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (mark[x] && mark[y]) {
            mark[re[y]] = 1;
            mark[y] = 0;
            DFS(re[y]);
        }
    }
}
int main() {
    int i, j, k, l;
    scanf("%d%d" , &n , &D);
    //srand(time(NULL));
    for (i = 0 ; i < n ; ++ i) {
        scanf("%d%d" , &a[i].first , &a[i].second);
        //a[i].first = rand() % 1000;
        //a[i].second = rand() % 1000;
    }
    for (i = 0 ; i < n ; ++ i)
        for (j = i + 1 ; j < n ; ++ j) {
            int dx = a[i].first - a[j].first;
            int dy = a[i].second - a[j].second;
            dis[i][j] = dis[j][i] = dx * dx + dy * dy;
        }
    D *= D;
    int ans = 1;
    vector<int> ver;
    ver.push_back(0);
    for (i = 0 ; i < n ; ++ i)
        for (j = i + 1 ; j < n ; ++ j) {
            if (dis[i][j] > D)
                continue;
            int L = dis[i][j];
            memset(pre , -1 , sizeof(pre));
            s = i , t = j;
            mcnt = 0; int cnt = 2;
            vector<int> S , T , res;
            res.push_back(i);
            res.push_back(j);            
            for (k = 0 ; k < n ; ++ k) {
                if (k == i || k == j)
                    continue;
                if (dis[i][k] > L || dis[j][k] > L)
                    continue;
                int x = (a[k] - a[i]) ^ (a[j] - a[i]);
                if (x > 0) {
                    S.push_back(k);
                    addarc(s , k , 1);
                }
                if (x < 0) {
                    T.push_back(k);
                    addarc(k , t , 1);
                }
                if (x == 0) {
                    ++ cnt;
                    res.push_back(k);
                }
            }
            for (k = 0 ; k < S.size() ; ++ k)
                for (l = 0 ; l < T.size() ; ++ l)
                    if (dis[S[k]][T[l]] > D)
                        addarc(S[k] , T[l] , 1);
            if (cnt + S.size() + T.size() <= ans)
                continue;
            int flow = 0;
            while (BFS()) {
                memcpy(cur , pre , sizeof(pre));
                flow += dfs(s);
            }            
            cnt += S.size() + T.size() - flow;
            if (cnt > ans) {
                ans = cnt;
                memset(re , -1 , sizeof(re));
                for (k = 0 ; k < S.size() ; ++ k) {
                    int x = S[k];
                    for (l = pre[x] ; ~l ; l = e[l].next) {
                        int y = e[l].x;
                        if (y != s && !e[l].f) {
                            re[x] = y;
                            re[y] = x;
                        }
                    }
                }
                memset(mark, 0, sizeof(mark));
                for (k = 0 ; k < S.size() ; ++ k) {
                    int x = S[k];
                    if (re[x] == -1) {
                        mark[x] = 1;
                    }
                }
                for (k = 0 ; k < T.size() ; ++ k) {
                    int x = T[k];
                    if (re[x] == -1 || !mark[re[x]]) {
                        mark[x] = 1;
                    }
                }
                for (k = 0; k < S.size(); ++ k) {
                    memset(f, 0, sizeof(f));
                    DFS(S[k]);
                }
                for (k = 0; k < n; ++ k)
                    if (mark[k])
                        res.push_back(k);
                ver = res;
            }
           
            
        }
    printf("%d\n", ans);
    for (i = 0; i < ver.size(); ++i)
        printf("%d%c", ver[i] + 1, " \n"[i + 1 == ver.size()]);
    return 0;
}
