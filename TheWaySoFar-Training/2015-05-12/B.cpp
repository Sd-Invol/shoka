#include <bits/stdc++.h>
using namespace std;
const int N = 505;

int a[N] , f[N] , n , m , ca;
int num[12] = {1,17,9,24,5,20,12,3,18,16,4,6};
int s[N] , K;
bool check() {
    int i , j , x;
    K = 0;
    for (i = 0 ; i < n ; ++ i) {
        int x = 0;
        for (j = 0 ; j < 5 ; ++ j) {
            x <<= 1;
            x |= f[i + j];
        }
        i += 5;
        for (j = 0 ; j < 12 ; ++ j)
            if (x == num[j])
                break;
        if (j >= 12 || (i < n && f[i]))
            return 0;
        s[K ++] = j;
    }
    if (s[K - 1] != 11 || s[0] != 11)
        return 0;
    for (i = 1 ; i + 1 < K ; ++ i)
        if (s[i] == 11)
            return 0;
    int w = K - 4;
    //for (i = 0 ; i < K ; ++ i)
    //    printf("%d%c" , s[i] , " \n"[i + 1 == K]);
    int c = 0 , k = 0;
    for (i = 1 ; i <= w ; ++ i) {
        c += ((w - i) % 10 + 1) * s[i];
        c %= 11;
    }
    if (s[w + 1] != c) {
        puts("bad C");
        return 1;
    }
    for (i = 1 ; i <= w + 1 ; ++ i) {
        k += ((w - i + 1) % 9 + 1) * s[i];
        k %= 11;
    }
    if (s[w + 2] != k) {
        puts("bad K");
        return 1;
    }
    for (i = 1 ; i <= w ; ++ i) {
        if (s[i] < 10)
            putchar(s[i] + '0');
        else
            putchar('-');
    }
    puts("");
    return 1;
}

void work() {
    int i , j , x;
    for (i = 0 ; i < n ; ++ i) {
        scanf("%d" , &a[i]);
    }
    printf("Case %d: " , ++ ca);
    if (n % 6 != 5) {
        puts("bad code");
        return;
    }
    x = *min_element(a , a + n);
    double l = 0 , r = x * 100 / 95.0;
    for (i = 0 ; i < n ; ++ i) {
        if (a[i] <= 105 * x / 95) {
            l = max(l , a[i] * 100 / 105.0);
        }
    }
    l *= 2 , r *= 2;
    for (i = 0 ; i < n ; ++ i) {
        if (a[i] > 105 * x / 95) {
            l = max(l , a[i] * 100 / 105.0);
            r = min(r , a[i] * 100 / 95.0);
            if (r - l < -(1e-8)) {
                puts("bad code");
                return;
            }
            f[i] = 1;
        } else {
            f[i] = 0;
        }
    }    
    if (check()) {
        return;
    }
    reverse(f , f + n);
    if (check()) {
        return;
    }
    
    puts("bad code");
}

int main() {
    while (scanf("%d" , &n) , n)
        work();
    return 0;
}
