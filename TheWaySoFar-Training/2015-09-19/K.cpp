#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
#include <unordered_map>
using namespace std;
typedef long long LL;
const int N = 8;
int ca , n , Q , a[N];
unordered_map<int , LL> f[1 << N];
void work() {
    scanf("%d%d" , &n , &Q);    
    for (int i = 0 ; i < 1 << n ; ++ i)
        f[i].clear();
    for (int i = 0 ; i < n ; ++ i) {
        scanf("%d" , &a[i]);
        f[1 << i][a[i]] = 1;
    }
    int LIM = 100000000;
    LL res = 0;
    for (int k = 1 ; k < 1 << n ; ++ k) {
        for (int i = (k - 1) & k ; i ; i = (i - 1) & k) {
            int j = k - i;
            if (i < j) {
                for (auto &it : f[i]) {
                    for (auto &ti : f[j]) {
                        if (it.first + ti.first <= LIM) {
                            f[k][it.first + ti.first] += 2 * it.second * ti.second;
                        }
                        if (it.first - ti.first >= 0) {
                            f[k][it.first - ti.first] += it.second * ti.second;
                        }
                        if (ti.first - it.first >= 0) {
                            f[k][ti.first - it.first] += it.second * ti.second;
                        }
                        if ((LL)it.first * ti.first <= LIM) {
                            f[k][it.first * ti.first] += 2 * it.second * ti.second;
                        }
                        if (ti.first && it.first % ti.first == 0) {
                            f[k][it.first / ti.first] += it.second * ti.second;
                        }
                        if (it.first && ti.first % it.first == 0) {
                            f[k][ti.first / it.first] += it.second * ti.second;
                        }                                                
                    }
                }
            }
        }
        int cnt = __builtin_popcount(k);
        if (f[k].count(Q))
            res += f[k][Q] * cnt * cnt;            
    }
    printf("Case #%d: %lld\n" , ++ ca , res);
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();    
    return 0;
}
