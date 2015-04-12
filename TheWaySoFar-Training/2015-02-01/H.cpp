#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 2005;
const int Q = 1e9 + 7;
struct Point {
    int x , y;
    Point () {}
    Point (int _x , int _y) {
        x = _x , y = _y;
    }
    Point operator + (const Point& R) const {
        return Point(x + R.x , y + R.y);
    }
    Point operator - (const Point& R) const {
        return Point(x - R.x , y - R.y);
    }
    LL operator ^ (const Point& R) const {
        return (LL)x * R.y - (LL)y * R.x;
    }
    LL operator % (const Point& R) const {
        return (LL)x * R.x + (LL)y * R.y;
    }
    bool operator == (const Point& R) const {
        return R.x == x && R.y == y;
    }
    int quad() const {
        if (y != 0) {
            return y > 0;
        }
        return x > 0;
    }
    LL len() const {
        return (LL)x * x + (LL)y * y;
    }
};

bool operator < (const Point& A , const Point& B) {
    int x = A.quad() , y = B.quad();
    if (x != y)
        return x < y;
    LL Cross = A ^ B;
    if (Cross != 0)
        return Cross > 0;
    return A.len() < B.len();
}

int n , m;
Point p[N];
LL power[N];

bool check(const pair<Point , int>& A , const pair<Point , int>& B) {
    LL C = A.first ^ B.first;
    if (C != 0)
        return C > 0;
    if (A.first % B.first < 0)
        return 1;
    LL D = A.first.len() - B.first.len();
    if (D != 0)
        return D < 0;
    return A.second < B.second;
}

void work() {
    int i , j , k , x , y , z;
    scanf("%d",&n);
    power[0] = 1;
    for (i = 0 ; i < n ; ++ i) {
        scanf("%d%d" , &x , &y);
        p[i] = Point(x , y);
        power[i + 1] = power[i] * 2 % Q;
    }
    LL res = 0;
    for (i = 0 ; i < n ; ++ i) {
        int factor = 0;
        vector< pair<Point , int> > V;
        for (j = 0 ; j < n ; ++ j) {
            if (p[i] == p[j]) {
                if (j < i) {
                    ++ factor;
                }
            } else {
                V.push_back(make_pair(p[j] - p[i] , j));
            }
        }
        sort(V.begin() , V.end());
        m = V.size();
        LL delta = 0;
        for (j = 0 , k = 1 ; j < m ; ++ j) {
            while (k < m && check(V[j] , V[(j + k) % m]))
                ++ k;
            delta += power[m - k];
            delta %= Q;
            if (k > 1)
                -- k;
        }
        res += delta * power[factor] % Q;
        res %= Q;    
    }
    sort(p , p + n);
    for (i = 0 ; i < n ; ++ i) {
        j = i;
        while (j < n && p[j] == p[i])
            ++ j;
        res += power[j - i] - 1;
        res %= Q;
        i = j - 1;
    }
    cout << res << endl;
    
}

int main() {
    work();    
    return 0;
}
