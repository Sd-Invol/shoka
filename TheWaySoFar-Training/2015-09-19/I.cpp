#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
#include <map>
using namespace std;
typedef long long LL;
const int N = 100005;
int n , m , q , ca , pre[N] , mcnt;
pair<int , int> E[N];
struct edge {
    int x , next;
}e[N <<  1];
map< pair<int , int> , vector<int> > Hash;
int T[N] , X[N] , Y[N];
bool del[N];
int F[N] , L[N] , R[N] , c[N] , ncnt , f[15][N] , dep[N];
int getf(int x) {
    return F[x] == x ? x : F[x] = getf(F[x]);
}
void dfs(int x , int fa) {   
    L[x] = ++ ncnt;
    f[0][x] = fa , dep[x] = dep[fa] + 1;
    for (int j = L[x] ; j <= n ; j += j & -j)
        ++ c[j];
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (y != fa) {
            dfs(y , x);
        }
    }
    R[x] = ncnt;
    for (int j = R[x] + 1 ; j <= n ; j += j & -j)
        -- c[j];
}
int LCA(int x , int y) {
    if (dep[x] < dep[y])
        swap(y , x);
    for (int i = 14 ; i >= 0 ; -- i)
        if (dep[x] - dep[y] >> i & 1)
            x = f[i][x];
    if (x == y) return x;
    for (int i = 14 ; i >= 0 ; -- i)
        if (f[i][x] != f[i][y]) {
            x = f[i][x];
            y = f[i][y];
        }
    return f[0][x];
}
void erase(int x , int y) {
    int z = LCA(x , y);
    x = getf(x);
    while (x && dep[x] > dep[z]) {
        F[x] = getf(f[0][x]);
        for (int i = L[x] ; i <= n ; i += i & -i)
            -- c[i];
        for (int i = R[x] + 1 ; i <= n ; i += i & -i)
            ++ c[i];        
        x = getf(x);
    }
    x = getf(y);
    while (x && dep[x] > dep[z]) {
        F[x] = getf(f[0][x]);
        for (int i = L[x] ; i <= n ; i += i & -i)
            -- c[i];
        for (int i = R[x] + 1 ; i <= n ; i += i & -i)
            ++ c[i];        
        x = getf(x);
    }
}
int query(int x , int y) {
    int z = LCA(x , y) , res = 0;
    for (int i = L[x] ; i > 0 ; i -= i & -i)
        res += c[i];
    for (int i = L[y] ; i > 0 ; i -= i & -i)
        res += c[i];
    for (int i = L[z] ; i > 0 ; i -= i & -i)
        res -= c[i] + c[i];
    return res;
}


void work() {
    printf("Case #%d:\n" , ++ ca);
    scanf("%d%d%d" ,&n , &m , &q);
    Hash.clear();
    for (int i = 0 ; i < m ; ++ i) {
        int x , y;
        scanf("%d%d" , &x , &y);
        if (x == y) {
            -- i;
            -- m;
        } else {
            if (x > y)
                swap(x , y);
            E[i] = make_pair(x , y);
            Hash[E[i]].push_back(i);
            del[i] = 0;
        }
    }    
    for (int i = 0 ; i < q ; ++ i) {
        scanf("%d%d%d" , &T[i] , &X[i] , &Y[i]);
        if (T[i] == 1 && X[i] == Y[i]) {
            -- i;
            -- q;
            continue;
        }
        if (X[i] > Y[i])
            swap(X[i] , Y[i]);
        if (T[i] == 1) {
            vector<int> &V = Hash[make_pair(X[i] , Y[i])];
            X[i] = V.back();
            del[X[i]] = 1;
            V.pop_back();
        }
    }
    for (int i = 1 ; i <= n ; ++ i)
        F[i] = i;
    memset(pre , -1 , sizeof(pre)) , mcnt = 0;
    for (int i = 0 ; i < m ; ++ i) {
        if (del[i]) continue;
        int x = E[i].first , y = E[i].second;
        if (getf(x) != getf(y)) {
            F[getf(x)] = getf(y);
            e[mcnt] = (edge) {y , pre[x]} , pre[x] = mcnt ++;
            e[mcnt] = (edge) {x , pre[y]} , pre[y] = mcnt ++;
        } else
            E[i].first *= -1;
    }
    memset(c , 0 , sizeof(c)) , ncnt = 0;
    dfs(1 , 0);
    for (int j = 1 ; j < 15 ; ++ j)
        for (int i = 1 ; i <= n ; ++ i)
            f[j][i] = f[j - 1][f[j - 1][i]];
    for (int i = 1 ; i <= n ; ++ i)
        F[i] = i;
    for (int i = 0 ; i < m ; ++ i)
        if (E[i].first < 0)
            erase(-E[i].first , E[i].second);        
    static int res[N]; int K = 0;
    for (int i = q - 1 ; i >= 0 ; -- i) {
        if (T[i] == 1) {
            int x = E[X[i]].first , y = E[X[i]].second;
            erase(x , y);
        } else {           
            res[K ++] = query(X[i] , Y[i]);
        }        
    }
    reverse(res , res + K);
    for (int i = 0 ; i < K ; ++ i)
        printf("%d\n" , res[i]);
}

int main() {
    int TT;
    scanf("%d" , &TT);
    while (TT --)
        work();
    return 0;
}
