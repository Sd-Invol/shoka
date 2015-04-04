#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1005;
int n , I[N][N];
int f[N];
int getf(int x) {
    return f[x] == x ? x : f[x] = getf(f[x]);
}

inline int cross(int x , int y) {
    return max(0 , 1000000 - abs(x - y));
}
int X[N];
bool vis[N];
bool check(vector<int>& V) {
    int m = V.size() , i , j , x , y , z;
    queue<int> Q;
    Q.push(V[0]) , X[V[0]] = 0 , vis[V[0]] = 1;
    while (!Q.empty()) {
        x = Q.front() , Q.pop();
        for (y = 0 ; y < n ; ++ y)
            if (I[x][y] && !vis[y]) {
                int d = 1000000 - I[x][y];
                z = X[x] - d;
                for (i = 0 ; i < m ; ++ i)
                    if (vis[V[i]] && cross(X[V[i]] , z) != I[V[i]][y])
                        break;
                if (i >= m) {
                    vis[y] = 1;
                    Q.push(y);
                    X[y] = z;
                    continue;
                }
                z = X[x] + d;
                for (i = 0 ; i < m ; ++ i)
                    if (vis[V[i]] && cross(X[V[i]] , z) != I[V[i]][y])
                        break;
                if (i >= m) {
                    vis[y] = 1;
                    Q.push(y);
                    X[y] = z;
                    continue;
                }
                return 0;
            }
    }
    return 1;
}

void work() {
    int i , j , x , y;
    scanf("%d",&n);
    for (i = 0 ; i < n ; ++ i)
        f[i] = i;
    for (i = 0 ; i < n ; ++ i)
        for (j = 0 ; j < n ; ++ j) {
            scanf("%d" , &I[i][j]);
            if (I[i][j])
                f[getf(i)] = getf(j);
        }
    for (i = 0 ; i < n ; ++ i)
        if (getf(i) == i) {
            vector<int> V;
            for (j = 0 ; j < n ; ++ j)
                if (getf(j) == i)
                    V.push_back(j);
            if (!check(V)) {
                puts("No");
                return;
            }
        }
    puts("Yes");
}

int main() {
    work();    
    return 0;
}
