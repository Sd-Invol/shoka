#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;

LL n , m , maxn;
int LOG ;

void update(LL A , LL B , int &step , LL &opt , LL &mn) {
    int p = __builtin_popcountll(A ^ B);
    if (p < step) {
        step = p;
        opt = 1;
        mn = B;
    } else if (p == step) {
        ++ opt;
        mn = min(mn , B);
    }
}

int main() {
    int step = 1 << 30;
    LL opt = 0 , mn = 0;
    scanf("%lld%lld" , &n , &m);
    maxn = 1 , LOG = 0;
    while (n >= maxn) {
        maxn <<= 1;
        ++ LOG;
    }
    if (n / m <= 1LL << 25) {
        for (LL x = 0 ; x < maxn ; x += m) {
            update(n , x , step , opt , mn);
        }        
    } else {
        LL L = 1LL << (LOG + 1 >> 1);
        LL R = 1LL << (LOG >> 1);
        LL nl = n / R;
        LL nr = n % R;
        for (LL mod = 0 ; mod < m ; ++ mod) {
            int ls = 1 << 30;
            LL lo = 0 , lm = -1;
            for (LL x = mod ; x < L ; x += m) {
                update(nl , x , ls , lo , lm);
            }
            int rs = 1 << 30;
            LL ro = 0 , rm = -1;
            for (LL x = (m - mod * R % m) % m ; x < R ; x += m) {
                update(nr , x , rs , ro , rm);
            }
            if (!~lm || !~rm)
                continue;
            int S = ls + rs;
            LL O = lo * ro;
            LL M = lm * R + rm;
            if (S < step) {
                step = S;
                opt = O;
                mn = M;
            } else if (S == step) {
                opt += O;
                mn = min(mn , M);
            }
        }
    }
    printf("%d %lld %lld\n" , step , opt , mn);
    return 0;    
}
