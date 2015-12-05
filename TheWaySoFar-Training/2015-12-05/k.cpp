#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct Point {
    int x , y;
    Point (int _x = 0 , int _y = 0) {
        x = _x , y = _y;
    }
    Point operator + (const Point &R) const {
        return Point(x + R.x , y + R.y);
    }
    Point operator - (const Point &R) const {
        return Point(x - R.x , y - R.y);
    }
    int operator ^ (const Point &R) const {
        return x * R.y - y * R.x;
    }
    int operator % (const Point &R) const {
        return x * R.x + y * R.y;
    }
};   

const int n = 7;
Point p[n];
int a[n];

bool rect(Point A , Point B , Point C , Point D) {
    int area = 0;
    area += (A ^ B) + (B ^ C) + (C ^ D) + (D ^ A);
    if (area == 0) return 0;

    if ((B - A) % (B - A) != (C - D) % (C - D))
        return 0;
    if (((B - A) ^ (C - D)) != 0)
        return 0;
    return 1;
}

bool eqtri(Point A , Point B , Point C) {
    int area = (A ^ B) + (B ^ C) + (C ^ A);
    if (area == 0) return 0;
    if ((B - A) % (B - A) != (C - A) % (C - A))
        return 0;
    return 1;
}

bool line(Point A , Point B , Point C , Point D) {
    Point V = B - A;
    if ((V ^ (C - A)) != 0)
        return 0;
    if ((V ^ (D - A)) != 0)
        return 0;
    if ((B - A) % (C - A) <= 0)
        return 0;
    if ((B - A) % (D - A) <= 0)
        return 0;
    if ((C - A) % (D - A) <= 0)
        return 0;
    int b = (B - A) % (B - A);
    int c = (C - A) % (C - A);
    int d = (D - A) % (D - A);
    if (b >= c) return 0;
    if (b >= d) return 0;
    if (c >= d) return 0;
    int d1 = (B - A) % (B - A);
    int d2 = (D - C) % (D - C);
    return d1 == d2;
}

int main() {
    for (int i = 0 ; i < n ; ++ i) {
        scanf("%d%d" , &p[i].x , &p[i].y);
        a[i] = i;
    }
    do {
        if (!rect(p[a[2]] , p[a[3]] , p[a[4]] , p[a[5]]))
            continue;
        if (!eqtri(p[a[0]] , p[a[1]] , p[a[6]]))
            continue;
        if (!line(p[a[1]] , p[a[2]] , p[a[5]] , p[a[6]]))
            continue;

        Point V = p[a[6]] - p[a[1]];
        int A = (p[a[0]] - p[a[1]]) ^ V;
        int B = (p[a[3]] - p[a[1]]) ^ V;
        if ((long long) A * B >= 0)
            continue;
        int area = 0;
        for (int i = 0 ; i < n ; ++ i)
            area += (p[a[i]] ^ p[a[(i + 1) % n]]);
        if (area >= 0)
            continue;
        puts("Yes");
        for (int i = 0 ; i < n ; ++ i)
            printf("%d%c" , a[i] + 1 , " \n"[i + 1 == n]);
        return 0;
    } while (next_permutation(a , a + n));
    puts("No");
    return 0;
}

