#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
const int N = 200000 / 32 + 5;

struct Poly {
    unsigned int a[N];
    int n;
    Poly (int _n = 0) {
        n = _n;
        memset(a , 0 , sizeof(a));
    }
    void input() {
        int len;
        scanf("%d" , &len);
        n = len / 32;
        memset(a , 0 , sizeof(a));
        for (int i = 0 ; i <= len ; ++ i) {
            unsigned int x;
            scanf("%u" , &x);
            a[i >> 5] |= x << (i & 31);
        }
    }
    int deg() const {
        int len = (n + 1) << 5;
        while (len > 0 && ~a[len >> 5] >> (len & 31) & 1)
            -- len;
        return len;
    }
    void output() {
        int len = deg();
        printf("%d" , len);
        for (int i = 0 ; i <= len ; ++ i)
            printf(" %u" , a[i >> 5] >> (i & 31) & 1);
        puts("");
    }
    Poly operator + (const Poly &R) const {
        Poly res(max(R.n , n));
        for (int i = 0 ; i <= res.n ; ++ i) {
            res.a[i] = a[i] ^ R.a[i];
        }
        while (res.n > 0 && !res.a[res.n])
            -- res.n;
        return res;
    }
    Poly operator << (const int &R) const {
        int t = R >> 5 , r = R & 31;
        Poly res(n + t + 1);
        for (int i = 0 ; i <= n ; ++ i)
            res.a[i + t] = a[i];
        if (r) {
            unsigned int x = 0 , y;
            for (int i = 0 ; i <= res.n ; ++ i) {           
                y = res.a[i] >> (32 - r);
                res.a[i] = res.a[i] << r | x;
                x = y;
            }
        }
        while (res.n > 0 && !res.a[res.n])
            -- res.n;
        return res;
    }
} pool[4];

int mess[1000000] , cnt;

int main() {
    int T;
    scanf("%d" , &T);
    while (T --) {
        Poly *A = pool , *B = A + 1 , *X = B + 1 , *Y = X + 1;
        *A = Poly(0);
        A -> a[0] = 1;
        *B = Poly(0);
        
        X -> input();
        Y -> input();

        cnt = 0;

        while (1) {
            int dx = X -> deg() , dy = Y -> deg();
            if (dy == 0 && !Y->a[0])
                break;
            if (dy > dx || dx == 0 && !X->a[0]) {
                swap(X , Y);
                mess[cnt ++] = -1;
            } else {                
                int k = dx - dy;
                swap(X , Y);
                *Y = *Y + (*X << k);
                mess[cnt ++] = k;                
                mess[cnt ++] = -1;
            }
        }
        while (cnt) {
            int x = mess[-- cnt];
            if (!~x) {
                swap(A , B);
            } else {
                *B = *B + (*A << x);
            }

        }
        A -> output();
        B -> output();
    }
    return 0;
}
