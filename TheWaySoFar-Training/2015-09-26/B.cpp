#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
typedef long long LL;
using namespace std;
const int N = 10005;
const int Q = 1e9 + 7;
const int MAGIC = 61;
int power[N] , L[N] , R[N];

int n , m , ca,  pre[N] , mcnt;
struct edge {
    int x , next;
}e[N << 1];
char str[N] , a[N];
bool f[N];
int s[N];

pair<int , int> Find(int x , int fa , int size) {
    pair<int , int> res(1 << 30 , -1);
    int mx = 0;
    s[x] = 1;
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (!f[y] && y != fa) {
            res = min(res , Find(y , x , size));
            mx = max(mx , s[y]);
            s[x] += s[y];
        }
    }
    return min(make_pair(max(mx , size - s[x]) , x) , res);
}
int S;
bool cntL[N] , cntR[N];

void getdis(int x , int fa , int len , int h1 , int h2 , vector< pair<int , bool> >& V) {
    //printf("%d %d %d %d\n" , x , len , h1 , h2);
    if (h1 == L[len]) {
        V.push_back({len , 0});
        //  printf("%d %dL\n" , x , len);
    }
    if (h2 == R[len]) {
        V.push_back({len , 1});
        //  printf("%d %dR\n" , x , len);
    }
    ++ S;
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (!f[y] && y != fa) {
            getdis(y , x , len + 1 , (h1 + (LL)a[y] * power[len]) % Q , ((LL)h2 * MAGIC + a[y]) % Q , V);
        }
    }
}

bool divide(int x , int size) {
    x = Find(x , 0 , size).second;
    f[x] = 1;
    vector< pair<int , bool> > V;
    if (m == 1 && a[x] == str[1])
        return 1;
    cntL[0] = cntR[0] = 1;   
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (f[y]) continue;
        S = 0;
        vector< pair<int , bool> > v;   
        getdis(y , x , 1 , a[y] , a[y] , v);
        s[y] = S;
        for (auto &it : v) {
            if (!it.second) {
                if (str[it.first + 1] == a[x] && cntR[m - it.first - 1])
                    return 1;
            } else {
                if (str[m - it.first] == a[x] && cntL[m - it.first - 1])
                    return 1;
            }
        }
        for (auto &it : v) {
            if (it.second)
                cntR[it.first] = 1;
            else
                cntL[it.first] = 1;
            V.push_back(it);
        }
    }
    for (auto &it : V) {       
        if (it.second)
            cntR[it.first] = 0;
        else
            cntL[it.first] = 0;
    }
    cntL[0] = cntR[0] = 0;
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (!f[y] && divide(y , s[y]))
            return 1;
    }
    return 0;
}

void work() {
    scanf("%d" , &n);
    memset(pre , -1 , sizeof(pre));
    mcnt = 0;
    for (int i = 1 ; i < n ; ++ i) {
        int x , y;
        scanf("%d%d" , &x , &y);
        e[mcnt] = (edge) {y , pre[x]} , pre[x] = mcnt ++;
        e[mcnt] = (edge) {x , pre[y]} , pre[y] = mcnt ++;        
    }
    scanf("%s" , a + 1);
    for (int i = 1 ; i <= n ; ++ i)
        a[i] -= 'a' - 1;
    scanf("%s" , str + 1);
    m = strlen(str + 1);
    for (int i = 1 ; i <= m ; ++ i)
        str[i] -= 'a' - 1;
    L[0] = 0;
    for (int i = 1 ; i <= m ; ++ i)
        L[i] = ((LL)L[i - 1] * MAGIC + str[i]) % Q;
    R[m + 1] = 0;
    for (int i = 1 ; i <= m ; ++ i)
        R[i] = (R[i - 1] + (LL)str[m - i + 1] * power[i - 1]) % Q;
    printf("Case #%d: " , ++ ca);
    memset(f , 0 , sizeof(f));
    memset(cntL , 0 , sizeof(cntL));
    memset(cntR , 0 , sizeof(cntR));
    if (m <= n && divide(1 , n))
        puts("Find");
    else
        puts("Impossible");
}

int main() {
    power[0] = 1;
    for (int i = 1 ; i < N ; ++ i)
        power[i] = (LL)power[i - 1] * MAGIC % Q;    
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}