#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 60;

struct Point {
    int x , y;
    Point () {}
    Point (int _x , int _y) {
        x = _x , y = _y;
    }
    Point operator + (const Point& R) const{
        return Point(x + R.x , y + R.y);
    }
    Point operator - (const Point& R) const{
        return Point(x - R.x , y - R.y);
    }
    int operator ^ (const Point& R) const{
        return x * R.y - y * R.x;
    }
    int operator % (const Point& R) const{
        return x * R.x + y * R.y;
    }
};
int n , s[N] , pre[N] , mcnt;
Point p[N][N];
struct edge {
    int x , next;
}e[N * N];
int c[N] , deg[N];
int vis[N];
bool f[N];

bool dfs(int x , int C) {
    if (f[x]) return 1;
    if (c[x]) return c[x] == C;
    c[x] = C;
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (!dfs(y , 3 - C))
            return 0;
    }
    return 1;
}
void add(int x , int w) {
    for (int i = pre[x] ; ~i ; i = e[i].next)
        deg[e[i].x] += w;
}

bool DFS() {
    int i , x , y;
    /*for (i = 0 ; i < n ; ++ i)
        if (!f[i])
            printf("%d-" , i);
            puts("");*/
    memset(c , 0 , sizeof(c));
    for (i = 0 ; i < n ; ++ i)
        if (!c[i] && !dfs(i , i))
            break;
    if (i >= n) return 1;

    x = -1;
    for (i = 0 ; i < n ; ++ i)
        if (!vis[i] && !f[i] && (!~x || deg[i] < deg[x]))
            x = i;
    if (!~x) return 0;
    //cout << x << '*' << endl;
    for (i = pre[x] ; ~i ; i = e[i].next) {
        y = e[i].x , add(y , -1);
        ++ vis[x] , ++ vis[y];
    }
    f[x] = 1;
    if (DFS()) return 1;
    f[x] = 0;
    for (i = pre[x] ; ~i ; i = e[i].next) {
        y = e[i].x , add(y , 1);
        -- vis[x] , -- vis[y];
    }
    int z = x;
    for (int j = pre[z] ; ~j ; j = e[j].next) {
        x = e[j].x;
        if (vis[x]) continue;
        for (i = pre[x] ; ~i ; i = e[i].next) {
            y = e[i].x , add(y , -1);
            ++ vis[x] , ++ vis[y];
        }
        f[x] = 1;
        if (DFS()) return 1;
        f[x] = 0;
        for (i = pre[x] ; ~i ; i = e[i].next) {
            y = e[i].x , add(y , 1);
            -- vis[x] , -- vis[y];
        }
    }
    return 0;    
}

bool OnSegment(Point P , Point a1 , Point a2) {
    return ((a1 - P) ^ (a2 - P)) == 0 && ((a1 - P) % (a2 - P)) < 0;
}
bool check(int i , int k , int j , int l) {
    Point V = p[i][k + 1] - p[i][k];
    Point V1 = p[j][l] - p[i][k];
    Point V2 = p[j][l + 1] - p[i][k];
    if ((V ^ V1) || (V ^ V2)) return 0;
    //if (OnSegment(p[i][k] , p[j][l] , p[j][l + 1])) return 1;
    //if (OnSegment(p[i][k + 1] , p[j][l] , p[j][l + 1])) return 1;
    //if (OnSegment(p[j][l] , p[i][k] , p[i][k + 1])) return 1;
    if (V % V1 <= 0 && V % V2 <= 0) return 0;
    V = p[i][k] - p[i][k + 1];
    V1 = p[j][l] - p[i][k + 1];
    V2 = p[j][l + 1] - p[i][k + 1];
    if (V % V1 <= 0 && V % V2 <= 0) return 0;    
    return 1;
}

void work() {
    int i , j , k , l , x , y;
    for (i = 0 ; i < n ; ++ i) {
        scanf("%d" , &s[i]);
        for (j = 0 ; j < s[i] ; ++ j) {
            scanf("%d%d" , &p[i][j].x , &p[i][j].y);
        }
        p[i][s[i]] = p[i][0];
    }
    memset(pre , -1 , sizeof(pre)) , mcnt = 0;
    memset(deg , 0 , sizeof(deg));
    for (i = 0 ; i < n ; ++ i) {
        for (j = i + 1 ; j < n ; ++ j) {
            for (k = 0 ; k < s[i] ; ++ k) {
                for (l = 0 ; l < s[j] ; ++ l) {
                    if (check(i , k , j , l))
                        break;
                }
                if (l < s[j])
                    break;
            }
            if (k < s[i]) {
                ++ deg[i] , ++ deg[j];
                //cout << "*" << i << ' ' << j << endl;
                e[mcnt] = (edge) {i , pre[j]} , pre[j] = mcnt ++;
                e[mcnt] = (edge) {j , pre[i]} , pre[i] = mcnt ++;
            }            
        }
    }
    if (!mcnt) {
        puts("1");
        return;
    } 
    memset(c , 0 , sizeof(c));
    memset(vis , 0 , sizeof(vis));
    memset(f , 0 , sizeof(f));
    for (i = 0 ; i < n ; ++ i)
        if (!c[i] && !dfs(i , 1))
            break;
    if (i >= n) {
        puts("2");
        return;
    }
    if (DFS()) {
        puts("3");
    } else {
        puts("4");
    }
}

int main() {
    while (scanf("%d",&n) , n)
        work();
    return 0;
}
