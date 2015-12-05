#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;

typedef long long LL;

struct Point {
    int x, y;

    void input() {
        scanf("%d%d", &x, &y);
    }

    Point operator - (const Point &a) const {
        return (Point) {x - a.x, y - a.y};
    }
    
    LL det(Point a) {
        return (LL)x * a.y - (LL)a.x * y;
    }

    LL operator * (const Point &a) const {
        return (LL)x * a.x + (LL)y * a.y;
    }

    LL len() {
        return (LL)x * x + (LL)y * y;
    }
}P[5];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        for (int i = 0; i < 4; ++i) {
            P[i].input();
        }
        static int ca = 0;
        printf("Case #%d: ", ++ca);
        if ((P[1] - P[0]).det(P[3] - P[2]) != 0 ||
            (P[2] - P[1]).det(P[3] - P[0]) != 0) {
            puts("Others");
            continue;
        }
        if ((P[1] - P[0]) * (P[2] - P[1]) == 0) {
            if ((P[0] - P[1]).len() == (P[1] - P[2]).len())
                puts("Square");
            else puts("Rectangle");
            continue;
        }
        if ((P[0] - P[1]).len() == (P[1] - P[2]).len())
            puts("Diamond");
        else puts("Parallelogram");
    }
}