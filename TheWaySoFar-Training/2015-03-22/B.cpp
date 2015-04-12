#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 200005;

int n , m , s , q;
int pre[N] , mcnt;
struct edge {
    int x , w , next;
}e[N << 1];
int stat[N];
int d[N] , bel[N];
bool f[N];
vector<int> node[N];
int F[N];
int getf(int x) {
    return F[x] == x ? x : F[x] = getf(F[x]);
}
priority_queue< pair<int , int> > PQ;
struct Edge {
    int x , y , w;
    bool operator < (const Edge& R) const {
        return w < R.w;
    }
}E[N << 1];
struct Query {
    int x , y , w , id;
    bool operator < (const Query& R) const {
        return w < R.w;
    }
}Q[N];
bool res[N];
int main() {
    int i , j , x , y , z;
    scanf("%d%d%d",&n,&s,&m);
    for (i = 1 ; i <= s ; ++ i) {
        scanf("%d" , &x);
        stat[i] = x;
    }
    memset(pre , -1 , sizeof(pre));
    for (i = 1 ; i <= m ; ++ i) {
        scanf("%d%d%d",&x,&y,&z);
        e[mcnt] = (edge) {y , z , pre[x]} , pre[x] = mcnt ++;
        e[mcnt] = (edge) {x , z , pre[y]} , pre[y] = mcnt ++;
    }
    memset(d , 63 , sizeof(d));
    for (i = 1 ; i <= s ; ++ i) {
        x = stat[i];
        bel[x] = x , d[x] = 0;
        PQ.push(make_pair(0 , x));
    }
    while (!PQ.empty()) {
        x = PQ.top().second , PQ.pop();
        if (f[x]) continue; f[x] = 1;
        for (i = pre[x] ; ~i ; i = e[i].next) {
            y = e[i].x , z = e[i].w;
            if (!f[y] && d[x] + z < d[y]) {
                d[y] = d[x] + z , bel[y] = bel[x];
                PQ.push(make_pair(-d[y] , y));
            }
        }
    }
    
    for (i = 1 ; i <= n ; ++ i)
        node[bel[i]].push_back(i);
    m = 0;
    for (i = 1 ; i <= s ; ++ i) {
        x = stat[i];
        for (auto y : node[x]) {
            for (j = pre[y] ; ~j ; j = e[j].next) {
                z = e[j].x;
                if (x < bel[z]) {
                    E[m ++] = (Edge) {x , bel[z] , d[y] + d[z] + e[j].w};
                }
            }
        }
    }
    sort(E , E + m);

    scanf("%d" , &q);
    for (i = 0 ; i < q ; ++ i) {
        scanf("%d%d%d",&Q[i].x,&Q[i].y,&Q[i].w);
        Q[i].id = i;
    }
    sort(Q , Q + q);
    for (i = 1 ; i <= s ; ++ i)
        F[stat[i]] = stat[i];
    for (i = 0 , j = 0 ; i < q ; ++ i) {
        z = Q[i].w;
        while (j < m && E[j].w <= z) {
            F[getf(E[j].x)] = getf(E[j].y);
            ++ j;
        }
        x = Q[i].x , y = Q[i].y;
        if (d[x] <= z && d[y] <= z && getf(x) == getf(y))
            res[Q[i].id] = 1;
    }
    for (i = 0 ; i < q ; ++ i)
        puts(res[i] ? "TAK" : "NIE");
    return 0;
}
