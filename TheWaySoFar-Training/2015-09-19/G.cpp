#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
#include <cctype>
#include <unordered_map>
#include <queue>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
const int N = 505;
uint n , Q , ca;
uint f[2][N][8];
int match[] = {6 , 2 , 5 , 5 , 4 , 5 , 6 , 3 , 7 , 6};

void add(uint &A , uint B) {
    A += B;
    if (A >= Q)
        A -= Q;
}
void work() {    
    scanf("%u%u" , &n , &Q);
    n -= 3;
    int cur = 0 , nxt = 1;
    memset(f[cur] , 0 , sizeof(f[cur]));
    f[cur][0][3] = 1;
    uint res = 0;
    for (int i = 0 ; i < n / 4 ; ++ i) {
        memset(f[nxt] , 0 , sizeof(f[nxt]));
        for (int j = 0 ; j <= n ; ++ j) {
            for (int k = 0 ; k < 8 ; ++ k) {                
                int aa = k & 1;
                int bb = k >> 1 & 1;
                if (!aa && !bb) continue;
                if (f[cur][j][k]) {
                    for (int a = aa ? 9 : 0 ; a >= 0 ; -- a)
                        for (int b = bb ? 9 : 0 ; b >= 0 ; -- b) {
                            int c = (a + b + (k >> 2 & 1)) % 10;
                            int d = (a + b + (k >> 2 & 1)) / 10;
                            int J = j + (aa ? match[a] : 0) + (bb ? match[b] : 0) + match[c];
                            if (J <= n) {
                                int nxtk = (d << 2) | (k & 3);
                                add(f[nxt][J][nxtk] , f[cur][j][k]);
                                if (J + (d ? 2 : 0) == n && (a || !aa) && (b || !bb)) {
                                    add(res , f[cur][j][k]);
                                }
                                if (aa && a) {
                                    add(f[nxt][J][nxtk & ~1] , f[cur][j][k]);
                                }
                                if (bb && b) {
                                    add(f[nxt][J][nxtk & ~2] , f[cur][j][k]);
                                }                                
                            }
                        }                    
                }
            }
        }
        swap(cur , nxt);
    }
    printf("Case #%u: %u\n" , ++ ca , res);
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();    
    return 0;
}
