#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
typedef long long LL;
using namespace std;
const int N = 100005;

int n , m , ca;
int t[N << 1];
inline int id(int l , int r) {
    return l + r | l != r;
}
void update(int l , int r , int x , int w) {
    int p = id(l , r);
    if (l == r)
        t[p] = w % m;
    else {
        int mid = l + r >> 1;
        if (x <= mid)
            update(l , mid , x , w);
        else
            update(mid + 1 , r , x , w);
        t[p] = (LL)t[id(l , mid)] * t[id(mid + 1 , r)] % m;
    }
}

void work() {
    printf("Case #%d:\n" , ++ ca);
    scanf("%d%d" , &n , &m);
    for (int i = 0 ; i <= n + n ; ++ i)
        t[i] = 1;
    for (int i = 1 ; i <= n ; ++ i) {
        int j , x;
        scanf("%d%d" , &j , &x);
        if (j == 1)
            update(1 , n , i , x);
        else
            update(1 , n , x , 1);
        printf("%d\n" , t[id(1 , n)]);
    }
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}