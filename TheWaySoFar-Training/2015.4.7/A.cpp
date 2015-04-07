#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 100005;
int n;
struct Point {
    int x , y , v , id;
    bool operator < (const Point& R) const {
        return v > R.v;
    }
}a[N];

bool check(int i , int j , int k) {
    int dx1 = a[j].x - a[i].x;
    int dx2 = a[k].x - a[i].x;
    int dy1 = a[j].y - a[i].y;
    int dy2 = a[k].y - a[i].y;
    if ((LL)dx1 * dy2 == (LL)dx2 * dy1)
        return 0;
    return 1;
}

void work() {
    int i , j , k;
    scanf("%d" , &n);
    for (i = 0 ; i < n ; ++ i) {
        scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].v);
        a[i].id = i + 1;
    }
    sort(a , a + n);
    if (check(0 , 1 , 2)) {
        printf("%d\n" , a[0].v + a[1].v + a[2].v);
        for (i = 0 ; i < 3 ; ++ i)
            printf("%d%c" , a[i].id , " \n"[i == 2]);
        return;
    }
    int res = 0;
    for (i = 3 ; i < n ; ++ i) {
        if (check(0 , 1 , i))
            res = max(res , a[0].v + a[1].v + a[i].v);
    }
    for (i = 3 ; i < n ; ++ i) {
        if (check(0 , 2 , i))
            res = max(res , a[0].v + a[2].v + a[i].v);
    }
    for (i = 3 ; i < n ; ++ i) {
        if (check(1 , 2 , i))
            res = max(res , a[1].v + a[2].v + a[i].v);
    }
    printf("%d\n" , res);
    for (i = 3 ; i < n ; ++ i) {
        if (check(0 , 1 , i) && res == a[0].v + a[1].v + a[i].v) {
            printf("%d %d %d\n" , a[0].id , a[1].id , a[i].id);
            return;
        }
    }
    for (i = 3 ; i < n ; ++ i) {
        if (check(0 , 2 , i) && res == a[0].v + a[2].v + a[i].v) {
            printf("%d %d %d\n" , a[0].id , a[2].id , a[i].id);
            return;
        }
    }
    for (i = 3 ; i < n ; ++ i) {
        if (check(2 , 1 , i) && res == a[2].v + a[1].v + a[i].v) {
            printf("%d %d %d\n" , a[2].id , a[1].id , a[i].id);
            return;
        }
    }            
}

int main() {    
    work();
    return 0;
}
