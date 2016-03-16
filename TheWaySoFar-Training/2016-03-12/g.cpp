#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <bitset>
#include <algorithm>
using namespace std;
const int N = 1005;
int n , f[N][N];
vector< pair<int , int> > V[N];
int main() {
    cin >> n;
    for (int i = 0 ; i < n ; ++ i) {
        for (int j = 0 ; j < n ; ++ j) {
            bool vis[N] = {};
            for (int k = 0 ; k < i ; ++ k)
                vis[f[k][j]] = 1;
            for (int k = 0 ; k < j ; ++ k)
                vis[f[i][k]] = 1;
            for (int k = 1 ; k <= i && k <= j ; ++ k)
                vis[f[i - k][j - k]] = 1;
            int &x = f[i][j];
            while (vis[x])
                ++ x;
            V[x].push_back(make_pair(i , j));
        }
    }

    for (int i = 0 ; i < n ; ++ i) {
        for (int j = 0 ; j < n ; ++ j) {
            if (f[i][j] > 10)
                printf("**%c" , " \n"[j + 1 == n]);
            else if (i < j) 
                printf("!!%c" , " \n"[j + 1 == n]);
            else
                printf("%2d%c" , f[i][j] , " \n"[j + 1 == n]);
            
            //printf("%c" , ".*"[f[i][j] <= 10]);            
        }
        //puts("");
    }
       
}
