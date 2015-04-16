#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1005;
int n , m , w[N][N];
char g[N][N];
int f[N * N * 2];
int getf(int x) {
    return x == f[x] ? x : f[x] = getf(f[x]);
}
struct edge {
    int x , y , w;
    bool operator < (const edge& R) const {
        return w < R.w;
    }
}e[N * N];

int merge(int x , int y) {
    x = getf(x) , y = getf(y);
    f[x] = y;
    return x != y;
}

void work() {
    int i , j , x , y;
    scanf("%d%d",&n,&m);
    for (i = 0 ; i < n ; ++ i)
        scanf("%s" , g[i]);
    for (i = 0 ; i < n ; ++ i)
        for (j = 0 ; j < m ; ++ j)
            scanf("%d" , &w[i][j]);
    int s = n * m * 2;
    for (i = 0 ; i <= s ; ++ i) f[i] = i;
    int num = 0 , size = n * m;
    for (i = 0 ; i < n ; ++ i)
        for (j = 0 ; j < m ; ++ j) {
            if (g[i][j] == '/') {
                if (i == 0)
                    merge(s , num);
                if (i + 1 == n)
                    merge(s , num + size);
                if (j == 0)
                    merge(s , num);
                if (j + 1 == m)
                    merge(s , num + size);
                if (i) {
                    merge(num , num - m + size);
                }
                if (j) {
                    if (g[i][j - 1] == '/')
                        merge(num , num - 1 + size);
                    else
                        merge(num , num - 1);
                }
            } else {
                if (i == 0)
                    merge(s , num);
                if (i + 1 == n)
                    merge(s , num + size);
                if (j == 0)
                    merge(s , num + size);
                if (j + 1 == m)
                    merge(s , num);
                if (i) {
                    merge(num , num - m + size);
                }
                if (j) {
                    if (g[i][j - 1] == '/')
                        merge(num + size , num - 1 + size);
                    else
                        merge(num + size , num - 1);
                }
            }
            e[num] = (edge) {num , num + size , w[i][j]};
            num ++;
        }
    sort(e , e + size);
    int res = 0;
    for (i = 0 ; i < size ; ++ i)
        res += e[i].w * merge(e[i].x , e[i].y);
    cout << res << endl;
}

int main() {
    work();
    return 0;
}
