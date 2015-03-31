#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 200005;


int cal(int p , int q , LL n) {
    //printf("%d %d %lld\n" , p , q , n);
    if (n % p == 0)
        return 1;
    if (n < p) {
        if (p > q) {
            return 0;
        } else {
            if (n + p < q) {
                return 1;
            } else {
                int delta = q - p;
                if (n % delta == 0)
                    return 0;
                return cal(p , q , n % delta);
            }
        }
    }
    if (p > q) {
        return !cal(q , p , n % p);
    } else 
        return 1;
   
}

void work() {
    int p , q , n;
    scanf("%d%d%d",&p,&q,&n);
    int d = __gcd(p , q);
    if (n % d) {
        puts("R");
        return;
    }
    p /= d , q /= d , n /= d;
    puts(cal(p , q , n) ? "E" : "P");
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}
