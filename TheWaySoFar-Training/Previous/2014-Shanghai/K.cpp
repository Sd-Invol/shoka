#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 100005;
int n , ca , D , a[N] , pre[N] , mcnt;
struct edge {
    int x , next;
}e[N << 1];

bool f[N];
int s[N] , c[N] , res;
vector<int> V;
pair<int , int> Find(int x , int fa , int cnt) {
    s[x] = 1;
    pair<int , int> ret(1 << 30 , -1);
    int m = 0;
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (!f[y] && y != fa) {
            ret = min(ret , Find(y , x , cnt));
            s[x] += s[y];
        }
    }
    return min(ret , make_pair(max(m , cnt - m) , x));
}

void Getdis(int type , int x , int fa , int val , int dist) {
    if (type) {
        V.push_back(val);
        for (int i = val ; i > 0 ; i -= i & -i)
            c[i] = max(c[i] , dist);
    } else {
        for (int i = max(1 , val - D) ; i < N ; i += i & -i)
            res = max(res , c[i] + dist);
    }
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (!f[y] && y != fa) {
            if (type && a[y] <= a[x])
                Getdis(type , y , x , a[y] , dist + 1);
            if (!type && a[y] >= a[x])
                Getdis(type , y , x , a[y] , dist + 1);
        }
    }
}
void Getdis1(int type , int x , int fa , int val , int dist) {
    if (type) {
        V.push_back(val);
        for (int i = val ; i < N ; i += i & -i)
            c[i] = max(c[i] , dist);
    } else {
        for (int i = min(N - 1 , val + D) ; i > 0 ; i -= i & -i)
            res = max(res , c[i] + dist);
    }
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (!f[y] && y != fa) {
            if (type && a[y] >= a[x])
                Getdis(type , y , x , a[y] , dist + 1);
            if (!type && a[y] <= a[x])
                Getdis(type , y , x , a[y] , dist + 1);
        }
    }
}
void divide(int x , int cnt) {
    x = Find(x , 0 , cnt).second;
    f[x] = 1;
    V.push_back(a[x]);
    for (int i = a[x] ; i > 0 ; i -= i & -i)
        c[i] = max(c[i] , 0);
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (!f[y]) {
            if (a[y] >= a[x])
                Getdis(0 , y , x , a[y] , 1);
            if (a[y] <= a[x])
                Getdis(1 , y , x , a[y] , 1);
        }
    }
    while (!V.empty()) {
        for (int i = V.back() ; i > 0 ; i -= i & -i)
            c[i] = c[0];
        V.pop_back();
    }
    V.push_back(a[x]);
    for (int i = a[x] ; i < N ; i += i & -i)
        c[i] = max(c[i] , 0);
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (!f[y]) {
            s[y] = V.size();
            if (a[y] <= a[x])
                Getdis(0 , y , x , a[y] , 1);
            if (a[y] >= a[x])
                Getdis(1 , y , x , a[y] , 1);
            s[y] = V.size() - s[y];
        }
    }
    while (!V.empty()) {
        for (int i = V.back() ; i < N ; i += i & -i)
            c[i] = c[0];
        V.pop_back();
    }
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (!f[y])
            divide(y , s[y]);
    }
}

void work() {
    int i , j , x , y , z;
    scanf("%d%d",&n,&D);
    for (i = 1 ; i <= n ; ++ i)
        scanf("%d" , &a[i]);
    memset(pre , -1 , sizeof(pre));
    mcnt = 0;
    for (i = 1 ; i < n ; ++ i) {
        scanf("%d%d",&x,&y);
        e[mcnt] = (edge) {y , pre[x]} , pre[x] = mcnt ++;
        e[mcnt] = (edge) {x , pre[y]} , pre[y] = mcnt ++;
    }
    memset(f , 0 , sizeof(f));
    memset(c , 0xC0 , sizeof(c));
    res = 0;
    divide(1 , n);
    printf("Case #%d: %d\n" , ++ ca , res + 1);
}

int main() {
    int T;
    scanf("%d",&T);
    while (T --)
        work();
    return 0;
}
