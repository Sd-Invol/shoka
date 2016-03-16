#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
const int N = 1000005;

struct Point {
    int x , y;
    Point (int _x = 0 , int _y = 0) {
        x = _x;
        y = _y;
    }
    int sgn() const {
        return y > 0 || (y == 0 && x > 0);
    }
    Point operator + (const Point &R) const {
        return Point(x + R.x , y + R.y);
    }
    bool operator < (const Point &R) const {
        if (this -> sgn() != R.sgn())
            return R.sgn() < this -> sgn();
        return x * R.y - y * R.x > 0;
    }
};
Point v[N] , p[N];
    
int main() {

    int w = 170;
    int n , m = 0;
    for (int i = 1 ; i < w ; ++ i) {
        for (int j = 1 ; j <= i ; ++ j) {
            if (__gcd(i - j , j) == 1) {
                int x = i - j , y = j;
                for (int k = 0 ; k < 4 ; ++ k) {
                    v[m ++] = Point(x , y);
                    swap(x , y);
                    x = -x;                    
                }
            }
        }
    }
    for (int j = 0 ; j <= 120; ++ j) {
        if (__gcd(w - j , j) == 1) {
            int x = w - j , y = j;
            for (int k = 0 ; k < 4 ; ++ k) {
                if (x == 87 && y == 83 || x == -87 && y == -83);
                else v[m ++] = Point(x , y);
                swap(x , y);
                x = -x;
            }
        }
        }
    int maxx = -1 << 30 , minx = 1 << 30;
    int maxy = -1 << 30 , miny = 1 << 30;
    
    sort(v , v + m);
    for (int i = 0 ; i < m ; ++ i) {
        p[i + 1] = p[i] + v[i];
        maxx = max(maxx , p[i].x);
        maxy = max(maxy , p[i].y);
        minx = min(minx , p[i].x);
        miny = min(miny , p[i].y);        
    }
    cout << m << endl;
    for (int i = 0 ; i < m ; ++ i) {
        p[i].x -= minx;
        p[i].y -= miny;
    }
    scanf("%d" , &n);
    if (n > m)
        puts("NO");
    else {
        puts("YES");
        for (int i = 0 ; i < n ; ++ i)
            printf("%d %d\n" , p[i].x , p[i].y);
    }
    return 0;
}
