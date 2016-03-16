#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long LL;
int a[10000][14];
int n , K , m , P;


int main() {    
    scanf("%d%d" , &n , &K);
    /*scanf("%d" , &m);
    for (int i = 0 ; i < m ; ++ i)
        for (int j = 0 ; j < K ; ++ j)
        scanf("%d" , &a[i][j]);*/
    /*int flag = 0;
    if (K > 7) {
        K = 14 - K;
        flag = 1;
        }*/
    /*for (int i = 0 ; i < 1 << n - P ; ++ i) {
        if (__builtin_popcount(i) != K - P)
            continue;
        int s = 0;
        for (int j = 0 ; j < n ; ++ j)
            if (((i >> j & 1) || j + P >= n))
                a[m][s ++] = j;
        ++ m;
    }
    cout << m << endl;*/
    int mark = 0;
    if (K > 7) {
        mark = 1;
        K = 14 - K;
    }
    for (int mask = 0; mask < 1 << n; ++mask) {
        int flag =  0;
        /*for (int i = 0; i < n; i += 2)
            if ((mask >> i & 1) + (mask >> (i + 1) & 1) != 1)
            flag = 1;*/
        if (__builtin_popcount(mask) != K) continue;
        int B = (n + K - 1) / K;
        int C = 0;
        if (K == 6) {
            C = 2;
            B = 2;
        }
        // if (K == 5) {
        //    C = 4;
        //    B = 2;
        // }
        for (int i = 0; i < n - C; i += B) {
            int cnt = 0;
            int R = B;
            if (i == 10) R += C;
            for (int j = 0; j < R; ++j)
                if (mask >> (i + j) & 1) ++ cnt;
            if (cnt != 1) flag = 1;
        }
        if (flag) continue;
        int s = 0;
        for (int j = 0 ; j < n ; ++ j)
            if ((mask >> j & 1))
                a[m][s ++] = j;
        if (s != K) cout << s << endl;//puts("NO");
        ++ m;
        //if (__b)
    }
    if (mark == 1) {
        for (int i = 0; i < m; ++i) {
            int mask = 0;
            for (int j = 0; j < K; ++j)
                mask |= 1 << a[i][j];
            int s = 0;
            for (int j = 0; j < n; ++j)
                if (!(mask >> j & 1)) a[i][s++] = j;  
        }
        K = 14 - K;
    }
    /*cout << m << endl;
    int res = 0;
    for (int mask = 0 ; mask < 1 << n ; ++ mask) {
        
        int mn = 1 << 30 , cnt = 0;
        for (int i = 0 ; i < m ; ++ i) {
            int s = 0;
            for (int j = 0 ; j < K ; ++ j)
                s += (mask >> a[i][j] & 1);
            if (s < mn) mn = s , cnt = 0;
            if (s == mn) ++ cnt;
        }
        if (cnt == 1)
            ++ res;
    }
    printf("%.10f\n" , 1.0 * res / (1 << n));*/
    printf("%d\n", m);
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < K; ++j)
            printf("%d%c", a[i][j] + 1, " \n"[j + 1 == K]);
    return 0;
}
