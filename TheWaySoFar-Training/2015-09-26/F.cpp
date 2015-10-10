#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
typedef long long LL;
using namespace std;
const int N = 105;
const int Q = 1e9 + 7;

struct Point {
    int x , y;
    Point (int _x = 0 , int _y = 0) {
        x = _x , y = _y;
    }
    Point operator - (const Point& R) const {
        return Point(x - R.x , y - R.y);
    }
    LL operator ^ (const Point& R) const {
        return (LL)x * R.y - (LL)y * R.x;
    }
    bool operator < (const Point& R) const {
        return make_pair(x , y) < make_pair(R.x , R.y);
    }
};
bool cmp(const Point& A , const Point& B) {
    return (A ^ B) > 0;
}

int n , K , m , ca;
Point p[N] , v[N];
LL f[N][N];
void work() {
    scanf("%d%d" , &n , &K);
    for (int i = 0 ; i < n ; ++ i)
        scanf("%d%d" , &p[i].x , &p[i].y);
    sort(p , p + n);
    LL res = 0;
    for (int l = 0 ; l < n ; ++ l) {
        m = 0;
        for (int i = l + 1 ; i < n ; ++ i)
            v[m ++] = p[i] - p[l];
        sort(v , v + m , cmp);
        memset(f , 0xC0 , sizeof(f));
        for (int i = 0 ; i < m ; ++ i) {
            f[i][1] = 0;
            for (int j = 2 ; j < K ; ++ j) {
                for (int k = 0 ; k < i ; ++ k) {
                    f[i][j] = max(f[i][j] , f[k][j - 1] + (v[k] ^ v[i]));
                }
                res = max(res , f[i][j]);
            }
        }
    }
    printf("Case #%d: %lld\n" , ++ ca , res);
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}