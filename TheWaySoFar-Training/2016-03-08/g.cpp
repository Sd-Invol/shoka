#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

const int N = 20;
const int n = 3;

int board[N][N] , tag[N][N];
int dx[] = {1 , 1 , 1 , 0 , 0 , -1 , -1 , -1};
int dy[] = {1 , 0 , -1 , 1 , -1 , 1 , 0 , -1};
set< pair<int , int> > ch;

inline bool in(int x , int y) {
    return 1 <= x && x <= n && 1 <= y && y <= n;
}

bool dfs(int x , int y , int e) {
    //printf("<-- %d %d %d\n" , x , y , e);
    tag[x][y] = e;
    vector< pair<int , int> > V;
    for (int k = 0 ; k < 8 ; ++ k) {
        int i = x + dx[k] , j = y + dy[k];
        if (!in(i , j) || !~board[i][j] || ch.count({i , j}))
            continue;
        ch.insert({i , j});
        V.push_back({i , j});
    }
    bool fail = 0;
    int xx = -1 , yy = -1 , w = 1 << 30;
    for (auto &it : ch) {
        
        int X = it.first , Y = it.second;
        int nm = 0 , nb = 0;
        for (int k = 0 ; k < 8 ; ++ k) {            
            int i = X + dx[k] , j = Y + dy[k];
            if (!in(i , j) || ~board[i][j])
                continue;
            if (tag[i][j] == 1)
                ++ nm;
            if (tag[i][j] == -1)
                ++ nb;                
        }
        if (nb == 0) {
            if (nm != board[X][Y]) {
                fail = 1;
                break;
                // fail;
            }
        } else if (nb < w) {
            w = nb;
            xx = X;
            yy = Y;
        }
        
    }
    //printf("%d %d\n" , xx , yy);
    if (!fail) {
        if (xx == -1 && yy == -1) {
                        
        } else {
            int X = -1 , Y = -1;
            for (int k = 0 ; k < 8 ; ++ k) {     
                int i = xx + dx[k] , j = yy + dy[k];
                if (!in(i , j) || ~board[i][j] || ~tag[i][j])
                    continue;
                X = i , Y = j;
                break;
            }
            //printf("%d %d\n" , X , Y);
            if (!dfs(X , Y , 1) && !dfs(X , Y , 0))
                fail = 1;
        }
    }
    for (auto &it : V)
        ch.erase(it);
    tag[x][y] = -1;
    //printf("%d %d %d : %d --> \n" , x , y , e , fail);
    return !fail;
}

int main() {

    memset(board , -1 , sizeof(board));
    memset(tag , -1 , sizeof(tag));
    
    int x , y;
    scanf("%d%d" , &x , &y);

    while (1) {
        printf("1 %d %d\n" , x , y);
        fflush(stdout);

        int m;
        scanf("%d" , &m);
        while (m --) {
            int i , j , k;
            scanf("%d%d%d" , &i , &j , &k);
            board[i][j] = k;
        }
        bool flag = 0;
        x = -1 , y = -1;
        for (int i = 1 ; i <= n ; ++ i) {
            for (int j = 1 ; j <= n ; ++ j) {
                if (!~board[i][j] && dfs(i , j , 0)) {
                    x = i , y = j;
                    flag = 1;
                    break;
                }
            }
            if (flag) break;
        }
        if (x == -1 && y == -1) {
            for (int i = 1 ; i <= n ; ++ i)
                for (int j = 1 ; j <= n ; ++ j)
                    if (!~board[i][j]) {
                        printf("3 %d %d\n" , i , j);
                        fflush(stdout);
                        scanf("%*d%*d%*d%*s");
                    }
            printf("4\n");
            fflush(stdout);
            break;
        }
    }
    return 0;
}
