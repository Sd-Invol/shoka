#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 105;
typedef pair<int , int> Point;
#define x first
#define y second
int n , ca;
Point a[N];
Point operator - (const Point& A , const Point& B) {
    return Point(A.x - B.x , A.y - B.y);
}
int operator ^ (const Point& A , const Point& B) {
    return A.x * B.y - A.y * B.x;
}

void work() {
    int i , j , k;
    for (i = 0 ; i < n ; ++ i) {
        scanf("%d%d" , &a[i].x , &a[i].y);
    }
    double res = 1e30;
    for (i = 0 ; i < n ; ++ i) {
        for (j = i + 1 ; j < n ; ++ j) {
            int L = 1 << 30 , R = -1 << 30;
            Point V = a[j] - a[i];
            double len = sqrt(V.x * V.x + V.y * V.y);
            for (k = 0 ; k < n ; ++ k) {
                int x = (a[k] - a[i]) ^ V;
                L = min(L , x);
                R = max(R , x); 
            }
            res = min(res , (R - L) / len);
        }
    }
    printf("Case %d: %.2f\n" , ++ ca , ceil(res * 100) / 100);
}

int main() {
    while (scanf("%d" , &n) , n)
        work();
    return 0;
}
