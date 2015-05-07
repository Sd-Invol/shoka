#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

struct Point {
    double x , y;
    Point () {}
    Point (double _x , double _y) {
        x = _x , y = _y;
    }
    Point operator + (const Point& R) const {
        return Point(x + R.x , y + R.y);
    }
    Point operator - (const Point& R) const {
        return Point(x - R.x , y - R.y);
    }
    Point operator * (const Point& R) const {
        return Point(x * R.x - y * R.y , x * R.y + y * R.x);
    }
    Point operator / (const double& R) const {
        return Point(x / R , y / R);
    }
    Point operator / (const Point& R) const {
        double v = R.x * R.x + R.y * R.y;
        return *this * Point(R.x , -R.y) / v;
    }

};
pair<int , int> Pround(Point P) {
    return make_pair(lround(P.x) , lround(P.y));
}

int p[12] , res , ca;
Point S[3];
int q[6];

int check(int x , int y , int z , int a , int b , int c) {
    if ((x == y) ^ (a == b)) return 0;
    if ((x == z) ^ (a == c)) return 0;
    if ((y == z) ^ (b == c)) return 0;
    map<int , int> Hash;
    Hash[x] = a , Hash[y] = b , Hash[z] = c;
    if (Hash.size() == 1) return 2;
    auto A = *Hash.begin();
    auto B = *Hash.rbegin();
    int dy = B.second - A.second;
    int dx = B.first - A.first;
    if (dy % dx) return 0;
    int K = dy / dx , C = a - K * x;
    if (K * y + C == b && K * z + C == c)
        return 1;
    return 0;
}

void cal(int x , int y) {
    Point V(x , y) , W(sqrt(x * x + y * y) , 0);
    Point X = V / W;
    for (int i = 0 ; i < 3 ; ++ i) {
        pair<int , int> Y = Pround(S[i] * X);
        q[i << 1] = Y.first;
        q[i << 1 | 1] = Y.second;
    }
    //for (int i = 0 ; i < 6 ; ++ i)
    //    printf("%d%c" , q[i] , " \n"[i == 5]);
    for (int i = 0 ; i < 3 ; ++ i)
        for (int j = 0 ; j < 3 ; ++ j)
            for (int k = 0 ; k < 3 ; ++ k) {
                if (i == j || j == k || i == k)
                    continue;
                res += (check(q[0] , q[2] , q[4] , p[i << 1] , p[j << 1] , p[k << 1]) * check(q[1] , q[3] , q[5] , p[i << 1 | 1] , p[j << 1 | 1] , p[k << 1 | 1]));
            }
}

void work() {
    int i , j;
    for (i = 0 ; i < 3 ; ++ i)
        S[i] = Point(p[i << 1] , p[i << 1 | 1]);
    for (i = 0 ; i < 6 ; ++ i)
        p[i] = p[i + 6];
    res = 0;
    for (i = -10 ; i <= 10 ; ++ i)
        for (j = -10 ; j <= 10 ; ++ j)
            if (abs(i) == 10 || abs(j) == 10)
                cal(i , j);
    printf("Case %d: " , ++ ca);
    if (res == 0)
        puts("no solution");
    else if (res == 2)
        puts("equivalent solutions");
    else
        puts("inconsistent solutions");
}


int main() {
    while (1) {
        int x = 0;
        for (int i = 0 ; i < 6 ; ++ i) {
            scanf("%d" , p + i);
            x |= p[i];
        }
        if (!x) break;
        for (int i = 6 ; i < 12 ; ++ i) {
            scanf("%d" , p + i);
        }
        work();
    }
    return 0;
}
