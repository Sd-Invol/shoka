#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <bitset>
typedef long long LL;
using namespace std;
const int N = 1005;
int n , m , K , Q , a[N] , b[N];
bitset<N> mess[N] , peo[N];
char str[N];
int cnt[N] , res;
int main() {
    freopen("filter.in", "r", stdin);
    freopen("filter.out", "w", stdout);
    scanf("%d%d" , &n , &m);
    for (int i = 0 ; i < m ; ++ i)
        scanf("%d" , &a[i]);
    scanf("%d" , &K);
    for (int i = 0 ; i < K ; ++ i) {
        scanf("%s" , str);
        int len = strlen(str);       
        for (int j = 0 , k = 0 ; j < len ; ++ j) {
            int x = str[j] >= 'a' ? 10 + str[j] - 'a' : str[j] - '0';
            for (int l = 0 ; l < 4 && k < n ; ++ l) {
                if (x >> l & 1)
                    mess[i].set(k);
                ++ k;
            }
        }
    }
    scanf("%d" , &Q);
    for (int i = 0 ; i < Q ; ++ i) {
        int x;
        scanf("%d" , &x);
        for (int j = 0 ; j < m ; ++ j) {
            int y = (LL)x * a[j] % n;
            peo[i].set(y);
        }
        for (int j = 0 ; j < K ; ++ j) {
            if ((peo[i] & mess[j]) == peo[i]) {
                if (!cnt[j]) {
                    ++ res;
                    cnt[j] = 1;
                }
            }
        }
    }
    printf("%d" , res);
    for (int i = 0 ; i < K ; ++ i)
        if (cnt[i])
            printf(" %d" , i);
    puts("");
    return 0;
}
