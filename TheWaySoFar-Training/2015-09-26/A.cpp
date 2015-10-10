#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
using namespace std;
typedef long long LL;
const int N = 100005;
int mu[N];
vector<int> fac[N];
int n , pre[N] , mcnt , a[N] , res[N];
struct edge {
    int x , next;
}e[N << 1];
pair<int , int> q[N << 1];
int L[N] , R[N] , ncnt , w[N] , ca , cnt[N];
void dfs(int x , int fa) {
    L[x] = ++ ncnt;
    w[ncnt] = a[x];
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (y != fa) {
            dfs(y , x);
        }
    }
    R[x] = ncnt;
}

void work() {
    memset(pre , -1 , sizeof(pre));
    mcnt = 0;
    for (int i = 1 ; i < n ; ++ i) {
        int x , y;
        scanf("%d%d" , &x , &y);
        e[mcnt] = (edge) {y , pre[x]} , pre[x] = mcnt ++;
        e[mcnt] = (edge) {x , pre[y]} , pre[y] = mcnt ++;
    }
    for (int i = 1 ; i <= n ; ++ i)
        scanf("%d" , &a[i]);
    ncnt = 0;
    dfs(1 , 0);
    int m = 0;
    for (int i = 1 ; i <= n ; ++ i) {
        q[m ++] = make_pair(L[i] - 1 , -i);
        q[m ++] = make_pair(R[i] , i);        
    }
    sort(q , q + m);
    memset(res , 0 , sizeof(res));
    memset(cnt , 0 , sizeof(cnt));
    for (int i = 0 , j = 1 ; i < m ; ++ i) {
        while (j <= n && j <= q[i].first) {
            int x = w[j];
            for (auto &it : fac[x]) {
                ++ cnt[it];
            }
            ++ j;
        }
        int delta = 0 , k = abs(q[i].second);
        for (auto &it : fac[a[k]]) {
            delta += mu[it] * cnt[it];
        }
        if (q[i].second > 0)
            res[k] += delta;
        else
            res[k] -= delta;
    }
    printf("Case #%d: " , ++ ca);
    for (int i = 1 ; i <= n ; ++ i)
        printf("%d%c" , res[i] , " \n"[i == n]);
}

int main() {
    mu[1] = 1;
    for (int i = 1 ; i < N ; ++ i) {
        if (!mu[i]) continue;
        for (int j = i ; j < N ; j += i) {
            fac[j].push_back(i);
            if (j > i)
                mu[j] -= mu[i];
        }
    }
    while (~scanf("%d" , &n))
        work();
    return 0;
}