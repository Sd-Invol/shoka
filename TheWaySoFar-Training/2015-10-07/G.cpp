#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
#include <cctype>
#include <queue>
using namespace std;
typedef long long LL;
const int N = 40;
int cnt[1 << 20];
int n , m , n0 , n1 , ca;
bool G[N][N];
LL deg[N];
int f[1 << 20][2] , g[1 << 20][2];
LL A[1 << 20] , B[1 << 20];

void dfs1(int k , int s , int mask , int sum) {
    if (k == n0) {
        ++ f[mask][sum];
    } else {
        dfs1(k + 1 , s , mask , sum);
        dfs1(k + 1 , s | 1 << k , mask ^ (deg[k] >> n0) , sum ^ cnt[deg[k] & s]);
    }
}
void dfs2(int k , int mask , int sum) {
    if (k == n1) {
        ++ g[mask][sum];
    } else {
        dfs2(k + 1 , mask , sum);
        dfs2(k + 1 , mask | 1 << k , sum ^ cnt[deg[k + n0] >> n0 & mask]);
    }
}

void work() {
    scanf("%d%d",  &n , &m);
    n1 = min(19 , n / 2) , n0 = n - n1;
    memset(deg , 0 , sizeof(deg));    
    for (int i = 0 ; i < m ; ++ i) {
        int x , y;
        scanf("%d%d" , &x , &y);        
        -- x , -- y;        
        deg[x] |= 1LL << y;
        deg[y] |= 1LL << x;        
    }
    for (int i = 0 ; i < 1 << n1 ; ++ i) {
        f[i][0] = f[i][1] = 0;
        g[i][0] = g[i][1] = 0;
    }
    dfs1(0 , 0 , 0 , 0);
    dfs2(0 , 0 , 0);
    LL res = 0;
    for (int k = 0 ; k < 2 ; ++ k) {
        for (int l = 0 ; l < 2 ; ++ l) {
            for (int i = 0 ; i < 1 << n1 ; ++ i) {
                A[i] = f[i][k];
                B[i] = g[i][l];
            }
            for (int j = 0 ; j < n1 ; ++ j)
                for (int i = 0 ; i < 1 << n1 ; ++ i)
                    if (~i >> j & 1) {
                        A[i] += A[i ^ (1 << j)];
                        B[i] += B[i ^ (1 << j)];
                    }
            for (int i = 0 ; i < 1 << n1 ; ++ i)
                A[i] *= B[i];
            for (int j = 0 ; j < n1 ; ++ j)
                for (int i = 0 ; i < 1 << n1 ; ++ i)
                    if (~i >> j & 1)
                        A[i] -= A[i ^ (1 << j)];
            for (int i = 0 ; i < 1 << n1 ; ++ i)
                if (cnt[i] ^ k ^ l)
                    res += A[i];
        }        
    }
    printf("Case #%d: %lld\n" , ++ ca , res);
}

int main() {
    for (int i = 1 ; i < 1 << 20 ; ++ i)
        cnt[i] = cnt[i & (i - 1)] ^ 1;
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}