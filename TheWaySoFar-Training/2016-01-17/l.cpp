#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
using namespace std;
const int N = 205;
char G[N][N] = {
    "rwwgwwwrwwwgwwr",
    "wbwwwywwwywwwbw",
    "wwbwwwgwgwwwbww",
    "gwwbwwwgwwwbwwg",
    "wwwwbwwwwwbwwww",
    "wywwwwwwwwwwwyw",
    "wwgwwwgwgwwwgww",
    "rwwgwwwswwwgwwr",
    "wwgwwwgwgwwwgww",
    "wywwwwwwwwwwwyw",
    "wwwwbwwwwwbwwww",
    "gwwbwwwgwwwbwwg",
    "wwbwwwgwgwwwbww",
    "wbwwwywwwywwwbw",
    "rwwgwwwrwwwgwwr"    
};

int L[256] , W[256];
int C[] = {0 , 1, 3, 2, 3, 2, 1, 5, 5, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 3, 10, 5, 10, 5, 10, 10, 10, 5, 5, 10, 10, 3};

bool F[N][N];

int n , m , res[N];

int main() {
    L['w'] = 1 , W['w'] = 1;
    L['s'] = 1 , W['s'] = 1;
    L['g'] = 2 , W['g'] = 1;
    L['y'] = 3 , W['y'] = 1;
    L['b'] = 1 , W['b'] = 2;
    L['r'] = 1 , W['r'] = 3;

    scanf("%d%d" , &n , &m);
    for (int k = 0 ; k < m ; ++ k) {
        int cnt;
        scanf("%d" , &cnt);
        int r = 0;
        set<int> Hash;            
        for (int j = 0 ; j < cnt ; ++ j) {
            int x , y , z; char dir[10];
            scanf("%d%s%d%d" , &z , dir , &x , &y);
            -- x , -- y;
            int p = 1 , s = 0;
            for (int i = 0 ; i < z ; ++ i) {
                int w;
                scanf("%d" , &w);
                if (!F[x][y]) {
                    Hash.insert(w);
                    ++ r;
                }
                p *= W[G[x][y]];
                s += L[G[x][y]] * C[w];                
                F[x][y] = 1;
                if (*dir == 'h')
                    ++ x;
                else
                    ++ y;
            }
            res[k % n] += p * s;
        }
        // printf("?%d\n" , r);
        if (r == 7)
            res[k % n] += 15;        
    }
    for (int i = 0 ; i < n ; ++ i)
        printf("%d\n" , res[i]);
    return 0;
}
