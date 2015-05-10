#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 25005;
int n , m , K , W , pre[N] , mcnt;
struct edge {
    int x , w , next;
}e[N << 3];
struct Edge {
    int x , y , w;
}E[N << 1];
int dis[N] , S[N];
int P[N] , s , t;
bool f[N];
int d[N] , cur[N];
void addarc(int x , int y , int z) {
    //printf("%d -> %d : %d\n" , x , y , z);
    e[mcnt] = (edge) {y , z , pre[x]} , pre[x] = mcnt ++;
    e[mcnt] = (edge) {x , 0 , pre[y]} , pre[y] = mcnt ++;
}
bool BFS() {
    queue<int> Q;
    memset(d , -1 , sizeof(d));
    d[s] = 1 , Q.push(s);
    while (!Q.empty()) {
        int x = Q.front(); Q.pop();
        for (int i = pre[x] ; ~i ; i = e[i].next) {
            int y = e[i].x;
            if (e[i].w && !~d[y]) {
                d[y] = d[x] + 1;
                Q.push(y);
                if (y == t)
                    return 1;
            }
        }
    }
    return 0;
}
int dfs(int x , int flow = 1 << 30) {
    if (x == t || !flow)
        return flow;
    int sum = 0 , u;
    for (int &i = cur[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (d[y] == d[x] + 1 && (u = dfs(y , min(flow , e[i].w)))) {
            e[i].w -= u , e[i ^ 1].w += u;
            flow -= u , sum += u;
            if (!flow) break;
        }
    }
    if (!sum) d[x] = -1;
    return sum;
}


int cal(int V) {
    //printf("%d\n" , V);
    int i , x , y , z;
    memset(pre , -1 , sizeof(pre));
    mcnt = 0;
    for (i = 0 ; i < m ; ++ i) {
        x = E[i].x , y = E[i].y , z = E[i].w;
        if (dis[x] + z == dis[y])
            addarc(y , x , 1);
        if (dis[y] + z == dis[x])
            addarc(x , y , 1);        
    }
    t = 1 , s = n + 1;
    for (i = 1 ; i <= W ; ++ i)
        if (dis[S[i]] == V)
            addarc(s , S[i] , 1);
    int res = 0;
    while (BFS()) {
        //cout << 233 << endl;
        memcpy(cur , pre , sizeof(cur));
        res += dfs(s);
    }
    return res;
}

int main() {
    int i , j , x , y , z;
    scanf("%d%d%d",&n,&m,&K);
    memset(pre , -1 , sizeof(pre));
    for (i = 0 ; i < m ; ++ i) {
        scanf("%d%d%d" , &x , &y, &z);
        E[i] = (Edge) {x , y , z};
        e[mcnt] = (edge) {y , z , pre[x]} , pre[x] = mcnt ++;
        e[mcnt] = (edge) {x , z , pre[y]} , pre[y] = mcnt ++;
    }
    priority_queue< pair<int , int> , vector< pair<int , int> > , greater<pair<int , int> > > Q;
    for (i = 1 ; i <= n ; ++ i)
        dis[i] = 1 << 30;
    dis[1] = 0;
    Q.push(make_pair(0 , 1));
    while (!Q.empty()) {
        x = Q.top().second , Q.pop();
        if (f[x]) continue; f[x] = 1;
        for (i = pre[x] ; ~i ; i = e[i].next) {
            y = e[i].x;
            if (!f[y] && dis[y] > dis[x] + e[i].w) {
                dis[y] = dis[x] + e[i].w;
                Q.push(make_pair(dis[y] , y));
            }
        }
    }
    for (i = 1 ; i <= K ; ++ i) {
        scanf("%d" , &x);
        S[i] = x;
        P[i] = dis[x]; 
    }
    W = K;
    sort(P + 1 , P + 1 + K);
    K = unique(P + 1 , P + 1 + K) - P - 1;
    int res = 0;
    for (i = 1 ; i <= K ; ++ i)
        res += cal(P[i]);
    printf("%d\n" , res);
    return 0;
}
