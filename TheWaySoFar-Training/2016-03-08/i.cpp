#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
using namespace std;
const int N = 1 << 20;
int cnt[N];
int a[2][N];

inline int Next(int x) {
    return ((long long)487237 * x + 1011807) % N;
}

int main() {
    for (int i = 1 ; i < 1 << 20 ; ++ i) {
        cnt[i] = cnt[i & (i - 1)] ^ 1;
    }
    int n = 1 << 20;
    int cur = 0 , nxt = 1;
    for (int i = 0 ; i < 1 << 20 ; ++ i)
        a[0][i] = i;
    int m;
    scanf("%d" , &m);
    while (1) {
        bool flag = 1;
        for (int i = 0 ; i < n ; ++ i)
            if (!cnt[a[cur][i]]) {
                flag = 0;
                break;
            }
        if (flag) {
            printf("%d\n" , 200 - m);
            fflush(stdout);
            scanf("%d" , &m);
            if (m == -1) {
                break;
            }
        } else {
            printf("%d\n" , 1);
            fflush(stdout);
            int mm;
            scanf("%d" , &mm);
            int nn = 0;
            if (mm < m) {
                for (int i = 0 ; i < n ; ++ i)
                    if (!cnt[a[cur][i]])
                        a[nxt][nn ++] = Next(a[cur][i]);
            } else {
                for (int i = 0 ; i < n ; ++ i)
                    if (cnt[a[cur][i]])
                        a[nxt][nn ++] = Next(a[cur][i]);
            }
            n = nn , m = mm;
            sort(a[nxt] , a[nxt] + n);
            n = unique(a[nxt] , a[nxt] + n) - a[nxt];
        }
        swap(cur , nxt);
    }        
    return 0;
}
