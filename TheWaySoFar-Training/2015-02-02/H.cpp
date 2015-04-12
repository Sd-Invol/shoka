#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 100005;

int n , a[N] , LOG[N];
int f[17][N];

inline int OR(int l , int r) {
    int j = LOG[r - l + 1];
    return f[j][l] | f[j][r - (1 << j) + 1];
}
vector<int> L[N] , R[N];
int res[N];

void work() {
    int i , j , k , x , y;
    scanf("%d",&n);
    for (i = 1 ; i <= n ; ++ i) {
        scanf("%d" , &a[i]);
       f[0][i] = a[i];
    }
    for (i = 0 ; 1 << i <= n ; ++ i)
        LOG[1 << i] = i;
    for (i = 2 ; i <= n ; ++ i)
        if (!LOG[i])
            LOG[i] = LOG[i - 1];    
    for (j = 1 ; 1 << j <= n ; ++ j)
        for (i = 1 ; i + (1 << j) - 1 <= n ; ++ i)
            f[j][i] = f[j - 1][i] | f[j - 1][i + (1 << j - 1)];
    for (i = 1 ; i <= n ; ++ i) {
        x = i;
        while (x <= n) {
            y = OR(i , x);
            int l = x , r = n , m;
            while (l < r) {
                m = l + r + 1 >> 1;
                if (OR(i , m) == y)
                    l = m;
                else
                    r = m - 1;
            }
            R[i].push_back(l);
            x = l + 1;
        }        
        x = i;
        while (x > 0) {
            y = OR(x , i);
            int l = 1 , r = x , m;
            while (l < r) {
                m = l + r >> 1;
                if (OR(m , i) == y)
                    r = m;
                else
                    l = m + 1;
            }
            L[i].push_back(l);
            x = l - 1;
        }
    }
    for (i = 1 ; i <= n ; ++ i) {
        for (j = 0 ; j < L[i].size() ; ++ j)
            for (k = 0 ; k < R[i].size() ; ++ k) {
                int l = L[i][j] , r = R[i][k];
                int len = (k ? R[i][k - 1] + 1 : i) - (j ? L[i][j - 1] - 1 : i) + 1;
                res[len] = max(res[len] , a[i] + OR(l , r));
            }
    }
    for (i = 1 ; i <= n ; ++ i) {
        res[i] = max(res[i] , res[i - 1]);
        printf("%d\n" , res[i]);
    }
}

int main() {
    work();    
    return 0;
}
