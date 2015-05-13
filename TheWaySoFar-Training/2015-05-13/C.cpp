#include <bits/stdc++.h>
using namespace std;
const int N = 105;
typedef pair<int , int> Point;
#define x first
#define y second

int n;
Point a[N];

int main() {
    int i , j;
    scanf("%d" , &n);
    for (i = 0 ; i < n ; ++ i)
        scanf("%d%d" , &a[i].x , &a[i].y);
    a[n] = a[0];
    double area = 0;
    int L = 1 << 30 , R = -1 << 30;
    double sx = 0;
    for (i = 0 ; i < n ; ++ i) {
        double delta = (a[i].x * a[i + 1].y - a[i].y * a[i + 1].x) / 2.0;
        sx += (a[i].x + a[i + 1].x) / 3.0 * delta;
        area += delta;
        if (a[i].y == 0) {
            L = min(L , a[i].x);
            R = max(R , a[i].x);            
        }
    }
    if (area < 0) {
        area = -area;
        sx = -sx;
    }
    int X = a[0].first;
    double A = area;
    double B = sx - X * area;
    L -= X , R -= X;

    if (fabs(B) < 1e-8) {
        if (L <= 0 && 0 <= R)
            puts("0 .. inf");
        else
            puts("unstable");
    } else {
        //printf("%f %d %d %d\n" , B , A , L , R);
        if (B < 0) {
            B = -B;
            swap(L , R);
            L = -L , R = -R;
        }
        //printf("%f %d %d %d\n" , B , A , L , R);
        if (L > 0) {
            double l = B / L - A;
            double r = max(0.0 , B / R - A);
            if (B >= A * L)
                printf("%d .. %d\n" , (int)floor(r) , (int)ceil(l));
            else {
                puts("unstable");
            }
        } else {
            if (R <= 0) {
                puts("unstable");
            } else {
                double r = max(0.0 , B / R - A);
                printf("%d .. inf" , (int)floor(r));
            }
        }
    } 
    
    
    return 0;
}
