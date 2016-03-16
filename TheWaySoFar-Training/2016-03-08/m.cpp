#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
using namespace std;
typedef long long LL;
const int N = 10;
const LL MAGIC = 1LL << 60;
int n , A , B , Q;
LL f[N + 1][59049] , F[N + 1][59049];
int power[N + 1] , cnt[1 << N] , rev[59049];
int a[N][N];
inline void add(LL &A , LL B) {
    A = min(A + B , MAGIC);
}

int dfs(int k , int i , int j , int l) {
    if (k == n) {
        return l;
    } else {
        int p = j / power[k] % 3;
        if (p == 0) {
            if (~i >> k & 1)
                return dfs(k + 1 , i , j , l + power[k] * 0);
            else
                return dfs(k + 1 , i , j , l + power[k] * 1);
        }
        if (p == 1) {
            if (~i >> k & 1)
                return dfs(k + 1 , i , j , l + power[k] * 2);
            else
                return dfs(k + 1 , i , j , l + power[k] * 1);
        }
        if (p == 2) {
            if (~i >> k & 1)
                return dfs(k + 1 , i , j , l + power[k] * 2);
            else
                return -1;
        }
    }
}

LL G[2][N + 1][59049];

int main() {
    power[0] = 1;
    for (int i = 1 ; i <= N ; ++ i)
        power[i] = power[i - 1] * 3;
    for (int i = 1 ; i < 1 << 10 ; ++ i)
        cnt[i] = cnt[i & (i - 1)] + 1;
    scanf("%d%d%d%d" , &n , &A , &B , &Q);

    for (int i = 0 ; i < power[n] ; ++ i) {       
        rev[i] = power[n] - 1 - i;
    }
    int cur = 0 , nxt = 1;
    f[0][0] = 1 , G[0][0][0] = 1;
    for (int i = 0 ; i < n * n ; ++ i) {
        int x = i / n , y = i % n;        
        memset(G[nxt] , 0 , sizeof(G[nxt]));
        for (int j = 0 ; j <= n ; ++ j) {
            for (int k = 0 ; k < power[n] ; ++ k) {
                if (!G[cur][j][k])
                    continue;
                LL w = G[cur][j][k];
                int p = k / power[y] % 3;                
                int l = k - p * power[y];
                if (p == 0) {
                    add(G[nxt][j][l + power[y] * 0] , w);
                    add(G[nxt][j + 1][l + power[y] * 1] , w);
                }
                if (p == 1) {                    
                    add(G[nxt][j][l + power[y] * 2] , w);
                    add(G[nxt][j + 1][l + power[y] * 1] , w);
                }
                if (p == 2) {                    
                    add(G[nxt][j][l + power[y] * 2] , w);
                }               
            }
        }        
        swap(cur , nxt);
        if (y == n - 1) {
            memset(G[nxt] , 0 , sizeof(G[nxt]));
            for (int j = 0 ; j <= n ; ++ j) {
                if (j < A || j > B) {

                } else {
                    for (int k = 0 ; k < power[n] ; ++ k) {
                        add(f[x + 1][k] , G[cur][j][k]);
                        add(G[nxt][0][k] , G[cur][j][k]);
                    }
                }
            }
            swap(cur , nxt);
        }
    }
    LL res = 0;
    for (int k = 0 ; k < power[n] ; ++ k) {
        bool flag = 1;
        for (int l = 0 ; l < n ; ++ l)
            if (k / power[l] % 3 == 0) {
                flag = 0;
                break;
            }
        if (flag)
            add(res , f[n][k]);
    }
    //cout << res << endl;
    for (int i = 0 ; i <= n ; ++ i) {
        for (int k = 0 ; k < power[n] ; ++ k) {
            F[i][k] = f[i][rev[k]];
        }
        for (int j = 0 ; j < n ; ++ j) {            
            for (int k = 0 ; k < power[n] ; ++ k) {
                int p = k / power[j] % 3;
                if (p == 1) {
                    add(F[i][k - power[j]] , F[i][k]);
                }                
            }
        }
        for (int j = 0 ; j < n ; ++ j) {            
            for (int k = 0 ; k < power[n] ; ++ k) {
                int p = k / power[j] % 3;
                if (p == 2) {
                    add(F[i][k - power[j]] , F[i][k]);
                }                
            }
        }                
    }
    for (int i = 0 ; i <= n ; ++ i) {
        for (int j = 0 ; j < power[n] ; ++ j) {
            printf("%6lld%c" , f[i][j] , " \n"[j + 1 == power[n]]);
        }
        for (int j = 0 ; j < power[n] ; ++ j) {
            printf("%6lld%c" , F[i][j] , " \n"[j + 1 == power[n]]);
        }        
    }
    //cout << res << endl;
    
    for (int q = 0 ; q < Q ; ++ q) {
        if (q) puts("");
        LL K;
        scanf("%lld" , &K);
        if (K > res) {
            puts("No such matrix.");
            continue;
        }
        int now = 0;
        
        for (int i = 0 ; i < n ; ++ i) {
            for (int j = 0 ; j < 1 << n ; ++ j) {
                if (A <= cnt[j] && cnt[j] <= B) {
                    nxt = dfs(0 , j , now , 0);
                    if (!~nxt) continue;
                    LL S = F[n - i - 1][nxt];
                    //cout << i << ' ' << j << ' ' << nxt << ' ' << F[n - i - 1][nxt] << endl;
                    if (S < K) {
                        K -= S;
                    } else {
                        for (int k = 0 ; k < n ; ++ k) {
                            a[i][n - k - 1] = j >> k & 1;
                        }
                        now = nxt;
                        break;
                    }
                }
            }
        }
        for (int i = 0 ; i < n ; ++ i) {
            for (int j = 0 ; j < n ; ++ j)
                printf("%d" , a[i][j]);
            puts("");
        }
        
        
    }
    
}
