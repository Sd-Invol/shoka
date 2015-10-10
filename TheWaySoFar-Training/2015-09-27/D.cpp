#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
typedef long long LL;
const int N = 1005;

struct DFA {
    int n , m , K;
    bool end[N];
    int u[N][26];
    void init() {
        scanf("%d%d%d", &n , &m , &K);
        memset(end , 0 , sizeof(end));
        for (int i = 0 ; i <= n ; ++ i)
            memset(u[i] , 0 , sizeof(u[i]));
        for (int i = 0 ; i < K ; ++ i) {
            int x;
            scanf("%d" , &x);
            end[++ x] = 1;
        }
        for (int i = 0 ; i < m ; ++ i) {
            int x , y; char str[5];
            scanf("%d%d%s" , &x , &y , str);
            ++ x , ++ y;            
            u[x][*str - 'a'] = y;
        }
    }
} A , B;
int d[N][N] , p[N][N] , ca;
void work() {
    printf("Case #%d: " , ++ ca);
    A.init();
    B.init();
    for (int i = 0 ; i <= A.n ; ++ i)
        for (int j = 0 ; j <= B.n ; ++ j)
            d[i][j] = -1;
    d[1][1] = 0 , p[1][1] = -1;
    queue<int> Q;
    Q.push(1); Q.push(1);
    while (!Q.empty()) {
        int x = Q.front(); Q.pop();
        int y = Q.front(); Q.pop();
        if (A.end[x] ^ B.end[y]) {
            int X = x , Y = y;
            vector<int> res;
            while (1) {
                int w = p[X][Y];
                if (!~w) break;
                y = w % N , w /= N;
                x = w % N , w /= N;
                res.push_back(w);
                X = x , Y = y;
            }
            reverse(res.begin() , res.end());
            for (int i = 0 ; i < res.size() ; ++ i)
                printf("%c" , res[i] + 'a');
            puts("");
            return;
        }

        
        for (int i = 0 ; i < 26 ; ++ i) {
            int X = A.u[x][i] , Y = B.u[y][i];
            if (!~d[X][Y]) {
                d[X][Y] = d[x][y] + 1;
                p[X][Y] = (i * N + x) * N + y;
                Q.push(X);
                Q.push(Y);
            }
        }
    }
    puts("0");
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}