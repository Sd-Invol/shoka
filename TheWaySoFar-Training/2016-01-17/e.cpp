#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
const int N = 1605;
int n , m , K , u , v;
int X[N] , Y[N] , p[N];
bool g[N][N];
double dist[N][N] , d[N];
bool f[N];
int main() {
    scanf("%d%d%d%d%d" , &n , &m , &K , &u , &v);
    for (int i = 0 ; i < n ; ++ i) {
        scanf("%d%d" , &X[i] , &Y[i]);
    }
    for (int i = 0 ; i < m ; ++ i) {
        int x , y;
        scanf("%d%d" , &x , &y);
        -- x , -- y;
        g[x][y] = g[y][x] = 1;        
    }
    for (int i = 0 ; i < n ; ++ i) {
        for (int j = 0 ; j < n ; ++ j) {
            int dx = X[i] - X[j];
            int dy = Y[i] - Y[j];
            dist[i][j] = sqrt(dx * dx + dy * dy);
            if (g[i][j])
                dist[i][j] /= u;
            else
                dist[i][j] /= v;
        }
    }
    double res = 0;
    int st = 0 , ed;
    vector<int> Route;
    Route.push_back(0);
    for (int k = 0 ; k <= K ; ++ k) {
        if (k < K) {
            scanf("%d" , &ed);
            -- ed;
        } else {
            ed = n - 1;
        }
        for (int i = 0 ; i < n ; ++ i) {
            d[i] = 1e60;
            f[i] = 0;
        }
        d[st] = 0 , p[st] = -1;

        for (int i = 0 ; i < n ; ++ i) {
            int x = -1;
            for (int j = 0 ; j < n ; ++ j) {
                if (!f[j] && (!~x || d[j] < d[x]))
                    x = j;
            }
            if (x == ed || d[x] > 1e50)
                break;
            f[x] = 1;
            for (int j = 0 ; j < n ; ++ j)
                if (!f[j] && d[x] + dist[x][j] < d[j]) {
                    d[j] = d[x] + dist[x][j];
                    p[j] = x;
                }
        }
        vector<int> R;
        int x = ed;
        while (x != st) {
            R.push_back(x);
            x = p[x];
        }
        reverse(R.begin() , R.end());
        Route.insert(Route.end() , R.begin() , R.end());
        res += d[ed];
        st = ed;
    }
    printf("%.10f\n" , res);
    for (int i = 0 ; i < (int)Route.size() ; ++ i)
        printf("%d%c" , Route[i] + 1 , " \n"[i + 1 == (int)Route.size()]);
    return 0;
}
