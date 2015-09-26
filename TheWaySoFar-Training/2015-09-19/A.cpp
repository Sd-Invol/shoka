#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
#include <map>
#include <set>
#include <queue>
using namespace std;
typedef long long LL;
const int N = 105;
const int Q = 10007;
int power[12];
int f[2][177147];

void init() {
    power[0] = 1;
    for (int i = 1 ; i < 12 ; ++ i)
        power[i] = power[i - 1] * 3;
}
inline void add(int& A , int B) {
    A += B;
    if (A >= Q)
        A -= Q;
}
int n , p , K , ca;
bool used[N];
void work() {
    scanf("%d%d%d", &n , &p , &K);
    memset(used , 0 , sizeof(used));
    for (int i = 0 ; i < K ; ++ i) {
        int x = 0;
        scanf("%d", &x);
        used[x] = 1;
    } // 3^11 = 177147
    int cur = 0 , nxt = 1 , mask = power[p + 2];
    memset(f[cur] , 0 , sizeof(f[cur]));
    f[cur][used[1] * 2] = 1;
    for (int i = 2 ; i <= n ; ++ i) {
        memset(f[nxt] , 0 , sizeof(f[nxt]));
        for (int j = 0 ; j < mask ; ++ j) {
            if (!f[cur][j]) continue;
            if (used[i]) {
                int degP = (j / power[p + 1]) % 3;
                if (i > p + 2 && degP != 2)
                    continue;
                add(f[nxt][(j * 3 + 2) % mask] , f[cur][j]);
            } else {
                int degP = (j / power[p + 1]) % 3;
                int degQ = (j / power[p - 1]) % 3;
                int degR = j % 3;
                if (i > p + 2 && degP == 0)
                    continue;
                if (i > p + 2 && degP == 1) {
                    add(f[nxt][(j * 3 + 1) % mask] , f[cur][j]);
                    if (degQ < 2) {
                        add(f[nxt][((j + power[p - 1]) * 3 + 2) % mask] , f[cur][j]);
                    }
                    if (degR < 2) {
                        add(f[nxt][((j + power[0]) * 3 + 2) % mask] , f[cur][j]);
                    }
                } else {
                    add(f[nxt][(j * 3 + 0) % mask] , f[cur][j]);
                    if (degQ < 2 && i > p) {
                        add(f[nxt][((j + power[p - 1]) * 3 + 1) % mask] , f[cur][j]);
                    }
                    if (degR < 2 && i > 1) {
                        add(f[nxt][((j + power[0]) * 3 + 1) % mask] , f[cur][j]);
                    }
                    if (degQ < 2 && degR < 2 && i > p && i > 1) {
                        add(f[nxt][((j + power[p - 1] + power[0]) * 3 + 2) % mask] , f[cur][j]);
                    }
                }
            }
        }
        swap(nxt , cur);
    }
    printf("Case #%d: %d\n" , ++ ca , f[cur][mask - 1]);
}

int main() {
    int T;
    init();
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}
