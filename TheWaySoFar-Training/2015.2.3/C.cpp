#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 200005;

int n , m , pre[N] , mcnt;
struct edge {
    int x , w , next;
}e[N << 1];
int K , a[N];
pair<int , int> d[N];
bool f[N];
pair<int , int> res[N];
struct opt {
    pair<int , int> w;
    int x;
    bool operator < (const opt& R) const {
        return w > R.w;
    }
};

void work() {
    int i , j , x , y , z;
    scanf("%d%d%d",&n,&m,&K);
    memset(pre , -1 , sizeof(pre));
    for (i = 0 ; i < m ; ++ i) {
        scanf("%d%d%d" ,&x,&y,&z);
        e[mcnt] = (edge) {y , z , pre[x]} , pre[x] = mcnt ++;
        e[mcnt] = (edge) {x , z , pre[y]} , pre[y] = mcnt ++;
    }
    priority_queue< opt > Q;
    for (i = 1 ; i <= n ; ++ i)
        d[i] = make_pair(0x7FFFFFFF , -1);
    for (i = 1 ; i <= K ; ++ i) {
        scanf("%d" , &x) , a[i] = x;
        d[x] = make_pair(0 , x) , Q.push((opt) {d[x] , x});
    }
    while (!Q.empty()) {
        opt T = Q.top() ; Q.pop(); x = T.x;
        if (f[x]) continue; f[x] = 1;
        for (i = pre[x] ; ~i ; i = e[i].next) {
            y = e[i].x;
            pair<int , int> w = d[x];
            w.first += e[i].w;
            if (!f[y] && w < d[y]) {
                d[y] = w;
                Q.push((opt) {d[y] , y});
            }
        }
    }
    for (i = 1 ; i <= n ; ++ i)
        res[i] = make_pair(0x7FFFFFFF , -1);
    for (i = 0 ; i < mcnt ; i += 2) {
        x = e[i ^ 1].x , y = e[i].x , z = e[i].w;
        if (d[x].second == d[y].second)
            continue;
        res[d[x].second] = min(res[d[x].second] , make_pair(d[x].first + d[y].first + z , d[y].second));
        res[d[y].second] = min(res[d[y].second] , make_pair(d[x].first + d[y].first + z , d[x].second));        
    }
    for (i = 1 ; i <= K ; ++ i)
        printf("%d\n" , res[a[i]].second);
}

int main() {
    work();
    return 0;
}
