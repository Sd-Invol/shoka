#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
int n;
int X[N] , Y[N] , R[N];
vector<int> e[N];
int dep[N];

void dfs(int x , int d) {
    dep[x] = d;
    for (auto y : e[x]) {
        if (!dep[y])
            dfs(y , d + 1);
    }
}

void work() {
    scanf("%d" , &n);
    for (int i = 0 ; i < n ; ++ i) {
        e[i].clear();
        scanf("%d%d%d" , &X[i] , &Y[i] , &R[i]);
    }
    for (int i = 0 ; i < n ; ++ i) {
        for (int j = i + 1 ; j < n ; ++ j) {
            int dx = X[i] - X[j] , dy = Y[i] - Y[j] , dr = R[i] + R[j];
            dx *= dx , dy *= dy;
            if (dx + dy == dr * dr) {
                e[i].push_back(j);
                e[j].push_back(i);
            }
        }
    }
    memset(dep , 0 , sizeof(dep));
    dfs(0 , 1);
    for (int i = 0 ; i < n ; ++ i) {
        if (!dep[i])
            puts("not moving");
        else {
            int x = R[0] , y = R[i] , z = __gcd(x , y);
            x /= z , y /= z;
            if (y == 1)
                printf("%d " , x);
            else
                printf("%d/%d " , x , y);
            if (dep[i] & 1)
                puts("clockwise");
            else
                puts("counterclockwise");
        }
    }
}

int main() {
    int _;
    scanf("%d",&_);
    while (_ --)
        work();
    return 0;
}
