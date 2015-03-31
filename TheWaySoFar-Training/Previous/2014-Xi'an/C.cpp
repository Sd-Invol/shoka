#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 105;
const double eps = 1e-8;
int n , m , a[100] , deg[100] , ca;
vector< pair<int , int> > E;

int s , t , pre[N] , mcnt;
struct edge {
    int x ; double f ; int next;
}e[N * N * 4];
inline void addarc(int x , int y , double z) {
    e[mcnt] = (edge) {y , z , pre[x]} , pre[x] = mcnt ++;
    e[mcnt] = (edge) {x , 0 , pre[y]} , pre[y] = mcnt ++;
}
int d[N] , cur[N];
bool BFS() {
    queue<int> Q;
    memset(d , -1 , t + 1 << 2);
    Q.push(s) , d[s] = 1;
    while (!Q.empty()) {
        int x = Q.front(); Q.pop();
        for (int i = pre[x] ; ~i ; i = e[i].next) {
            int y = e[i].x;
            if (e[i].f > eps && !~d[y]) {
                d[y] = d[x] + 1;
                Q.push(y);
                if (y == t)
                    return 1;
            }
        }
    }
    return 0;
}

double dfs(int x , double flow = 1e20) {
    if (x == t || flow < eps)
        return flow;
    double sum = 0 , u;
    for (int& i = cur[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (d[y] == d[x] + 1 && (u = dfs(y , min(flow , e[i].f))) > eps) {
            e[i].f -= u , e[i ^ 1].f += u;
            flow -= u , sum += u;
            if (flow < eps)
                break;
        }
    }
    if (sum < eps) d[x] = -1;
    return sum;
}

double cal(double val) {
    s = n + 1 , t = s + 1;
    memset(pre , -1 , t + 1 << 2);
    mcnt = 0;

    for (int i = 0 ; i < n ; ++ i) {
        addarc(s , i , m);
        addarc(i , t , m + val + val - deg[i]);
    }
    double res = -n * m;
    for (int i = 0 ; i < m ; ++ i) {
        addarc(E[i].second , E[i].first , 1);
        addarc(E[i].first , E[i].second , 1);
    }
    while (BFS()) {
        memcpy(cur , pre , t + 1 << 2);
        res += dfs(s);
    }
    return res;
}

void work() {
    int i , j;
    scanf("%d",&n);
    for (i = 0 ; i < n ; ++ i) {
        scanf("%d",&a[i]);
        deg[i] = 0;
    }
    E.clear();
    for (i = 0 ; i < n ; ++ i)
        for (j = i + 1 ; j < n ; ++ j)
            if (a[i] > a[j]) {
                E.push_back(make_pair(i , j));
                ++ deg[i] , ++ deg[j];
            }
    m = E.size();
    double l = 0 , r = n , m;
    while (r - l > eps) {
        m = (l + r) * 0.5;
        if (cal(m) > -eps)
            r = m;
        else
            l = m;
    }
    printf("Case #%d: %.10f\n" , ++ ca , (l + r) / 2);
}

int main() {
    int _; scanf("%d",&_); while (_ --)
        work();
    return 0;
}

