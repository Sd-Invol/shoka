#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 3005;

int n , m , pre[N] , mcnt;
struct edge {
    int x , next;
}e[N * 2];

int re[N];
bool f[N];
vector<int> p;

bool find(int x) {
    for (int i = pre[x]; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (!f[y]) {
            f[y] = 1;
            if (!re[y] || find(re[y])) {
                re[y] = x;
                return 1;
            }
        }
    }
    return 0;
}
map< pair<int , int> , int > ha , hb;
int na , nb , id[N][N];
void work() {
    int i , j , x , y , z , u , v;
    scanf("%d",&n);
    memset(pre ,-1 , sizeof(pre));
    mcnt = na = nb = 0;
    ha.clear() , hb.clear() , p.clear();
    int flag = 0;
    for (i = 1 ; i <= n ; ++ i) {
        scanf("%d%d%d",&x,&y,&z);      
        if (y < 0) x = -x , y = -y , z = -z;
        if (!y && !z) {flag = i; continue; }
        j = __gcd(x , y);
        pair<int , int> a(x / j , y / j);
        u = ha.count(a) ? ha[a] : ha[a] = ++ na;
        j = __gcd(y , z); if (!j) j = 1; 
        pair<int , int> b(y / j , z / j);
        v = hb.count(b) ? hb[b] : hb[b] = ++ nb;
        id[u][v] = i;
        e[mcnt] = (edge) {v , pre[u]} , pre[u] = mcnt ++;
    }
    memset(re , 0 , sizeof(re));
    int res = 0;
    for (i = 1 ; i <= na ; ++ i) {
        memset(f , 0 , sizeof(f));
        res += find(i);
    }
    //cout << na << ' ' << nb << endl;
    for (i = 1 ; i <= nb ; ++ i)
        if (re[i])
            p.push_back(id[re[i]][i]);
    if (p.empty()) p.push_back(flag);
    cout << p.size() << endl;
    for (i = 0 ; i < p.size() ; ++ i)
        printf("%d%c" , p[i] , " \n"[i + 1 == p.size()]);
}

int main() {
    int T;
    scanf("%d",&T);
    while (T --)
        work();
    return 0;
}
