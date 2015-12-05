#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 1005;

int n , m , a[N][N];

int id[N][N];
int cnt , type[N * N] , X[N * N] , Y[N * N] , num;
int res[N][N];

void paint(int x , int y , int t) {
    ++ num;
    type[num] = t;
    X[num] = x , Y[num] = y;
    if (t == 0) {
        for (int i = 0 ; i < 2 ; ++ i)
            for (int j = 0 ; j < 3 ; ++ j)
                id[x + i][y + j] = num;        
        ++ cnt;
        res[x][y] = res[x + 1][y] = res[x][y + 1] = cnt;
        ++ cnt;
        res[x + 1][y + 2] = res[x + 1][y + 1] = res[x][y + 2] = cnt;
    } else {        
        for (int i = 0 ; i < 3 ; ++ i)
            for (int j = 0 ; j < 2 ; ++ j)
                id[x + i][y + j] = num;
        ++ cnt;
        res[x][y] = res[x + 1][y] = res[x][y + 1] = cnt;
        ++ cnt;
        res[x + 2][y + 1] = res[x + 1][y + 1] = res[x + 2][y] = cnt;            
    }        
}
void trans(int id) {
    int x = X[id] , y = Y[id];
    if (type[id] == 0) {
        for (int i = 0 ; i < 3 ; ++ i)
            swap(res[x][y + i] , res[x + 1][y + i]);       
    } else {
        for (int i = 0 ; i < 3 ; ++ i)
            swap(res[x + i][y] , res[x + i][y + 1]);           
    }
}


int main() {

    scanf("%d%d" , &n , &m);
    for (int i = 1 ; i <= n ; ++ i)
        for (int j = 1 ; j <= m ; ++ j) {
            scanf("%d" , &a[i][j]);
        } 
    int nn = n , mm = m;
    if (n & 1) {
        for (int i = 1 ; i <= m ; i += 2)
            paint(n - 2 , i , 1);
        n -= 3;
    }
    if (m & 1) {
        for (int i = 1 ; i <= n ; i += 2) 
            paint(i , m - 2 , 0);
        m -= 3;
    }

    if (n % 3 == 0) {
        for (int i = 1 ; i <= n ; i += 3)
            for (int j = 1 ; j <= m ; j += 2)
                paint(i , j , 1);
    } else {
        for (int i = 1 ; i <= n ; i += 2)
            for (int j = 1 ; j <= m ; j += 3)
                paint(i , j , 0);        
    }
    n = nn , m = mm;

    int dx[5] = {1 , 0 , -1 , 0 , 0};
    int dy[5] = {0 , -1 , 0 , 1 , 0};

    int v[5];
    for (int i = 1 ; i <= n ; ++ i) {
        for (int j = 1 ; j <= m ; ++ j) {
            int cnt = 0;
            for (int k = 0 ; k < 4 ; ++ k) {
                int x = i + dx[k] , y = j + dy[k];
                if (res[x][y] == res[i][j])
                    v[cnt ++] = k;
            }
            if (cnt < 2)
                continue;
            v[cnt ++] = 4;
            int papa = 0;
            for (int k = 0 ; k < cnt && !papa ; ++ k) {
                int K = v[k];
                for (int l = k + 1 ; l < cnt ; ++ l) {
                    int L = v[l];
                    if (a[i + dx[K]][j + dy[K]] != a[i + dx[L]][j + dy[L]]) {
                        papa = 1;
                        break;
                    }
                }
            }
            if (!papa) {
                trans(id[i][j]);
            }
        }
    }

    
    for (int i = 1 ; i <= n ; ++ i)
        for (int j = 1 ; j <= m ; ++ j)
            printf("%d%c" , res[i][j] , " \n"[j == m]);
    return 0;
}
