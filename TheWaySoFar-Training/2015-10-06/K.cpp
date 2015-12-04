#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
typedef long long LL;
using namespace std;

const int N = 1005;

int n , m , a[N] , b[N] , T[N];

int main() {
    freopen("knockout.in", "r", stdin);
    freopen("knockout.out", "w", stdout);
    scanf("%d%d" , &n , &m);
    for (int i = 0 ; i < n ; ++ i) {
        scanf("%d%d" , &a[i] , &b[i]);
        T[i] = abs(a[i] - b[i]);
    }
    for (int i = 0 ; i < m ; ++ i) {
        int l , r , t;
        scanf("%d%d%d" , &l , &r , &t);
        int res = 0;
        for (int j = 0 ; j < n ; ++ j) {
            int w = t % (T[j] + T[j]);
            int p;
            if (a[j] < b[j]) {
                if (w < T[j])
                    p = a[j] + w;
                else
                    p = b[j] - (w - T[j]);
            } else {
                if (w < T[j])
                    p = b[j] - w;
                else
                    p = a[j] + (w - T[j]);            
            }
            //printf("+%d\n" , p);
            res += (l <= p && p <= r);
        }
        printf("%d\n" , res);
    }
   
    
    return 0;
}
