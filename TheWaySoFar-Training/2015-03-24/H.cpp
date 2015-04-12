#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int n = 4;
char str[10][10];
queue<int> Q;
char D[] = "RDLU" , res[30];
int dx[4] = {0 , 1 , 0 , -1} , dy[] = {1 , 0 , -1 , 0};
int d[10][10] , len;
bool f[10][10];
bool dfs(int x , int y) {
    if (x == 4 && y == 4) {
        return len > d[n][n];
    }
    for (int i = 0 ; i < 4 ; ++ i) {
        int X = x + dx[i] , Y = y + dy[i];
        if (!f[X][Y] && str[X][Y] == '.') {
            res[len ++] = D[i];
            f[X][Y] = 1;
            if (dfs(X , Y))
                return 1;
            f[X][Y] = 0;
            res[-- len] = 0;
        }
    }
    return 0;
}

int main() {
    int i , j , k , x , y , z;
    while (1) {
        for (i = 1 ; i <= n ; ++ i)
            scanf("%s" , str[i] + 1);
        memset(d , -1 , sizeof(d));
        Q.push(1) , Q.push(1) , d[1][1] = 0;
        while (!Q.empty()) {
            x = Q.front() , Q.pop();
            y = Q.front() , Q.pop();
            for (i = 0 ; i < 4 ; ++ i) {
                int X = x + dx[i] , Y = y + dy[i];
                if (str[X][Y] == '.' && !~d[X][Y]) {
                    d[X][Y] = d[x][y] + 1;
                    Q.push(X) , Q.push(Y);
                }
            }
        }
        if (!~d[n][n]) {
            puts("-1");
        } else {
            memset(f , 0 , sizeof(f));
            memset(res , 0 , sizeof(res));            
            f[1][1] = 1 , len = 0;
            if (dfs(1 , 1))
                puts(res);
            else
                puts("-1");
        }
        if (!~scanf("%s" , str[9] + 1) || str[9][1] != '-')
            break;  
    }
    

    return 0;
}
