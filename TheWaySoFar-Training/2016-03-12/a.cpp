#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 100005;
const int MAGIC = 23;
const int Q = 1e9 + 7;

int n , m;
char a[N] , b[N];

void build(char *s) {
    for (int i = 0 ; s[i] ; ++ i)
        if (s[i] != '9')
            return;
    s[0] = '0'; s[1] = 0;
}

pair<int , int> fa[40][N] , fb[40][N] , f9[40];

pair<int , int> operator + (const pair<int , int> &A , const pair<int , int> &B) {
    return make_pair(((LL)A.first * B.second + B.first) % Q , (LL)A.second * B.second % Q);
}

void init(char *s , int len , pair<int , int> f[][N]) {
    for (int i = 0 ; i < len ; ++ i) {
        f[0][i] = make_pair(s[i] - '0' + 1 , MAGIC);
    }
    for (int j = 1 ; j < 40 ; ++ j) {
        for (int i = 0 ; i < len ; ++ i) {
            int x = (i + (1LL << j - 1)) % len;
            f[j][i] = f[j - 1][i] + f[j - 1][x];
        }
    }
}

void work() {
    scanf("%s%s" , a , b);
    build(a);
    n = strlen(a);
    init(a , n , fa);
    build(b);
    m = strlen(b);
    init(b , m , fb);

    f9[0] = make_pair(11 , MAGIC);
    for (int i = 1 ; i < 40 ; ++ i) {
        f9[i] = f9[i - 1] + f9[i - 1];
    }
    
    LL T = (LL)n / __gcd(n , m) * m;
    int q;
    scanf("%d" , &q);
    for (int o = 0 ; o < q ; ++ o) {
        LL w;
        scanf("%lld" , &w); -- w;
        pair<int , int> nowx(0 , 1) , nowy(0 , 1) , nowz(0 , 1);
        int x = (w + 1) % n , y = (w + 1) % m; LL l = 0;
        for (int k = 39 ; k >= 0 ; -- k) {
            pair<int , int> nxtx = nowx + fa[k][x];
            pair<int , int> nxty = nowy + fb[k][y];
            pair<int , int> nxtz = nowz + f9[k];
            if ((nxtx.first + nxty.first) % Q == nxtz.first) {
                l += 1LL << k;
                x = (x + (1LL << k)) % n;
                y = (y + (1LL << k)) % m;                
                nowx = nxtx;
                nowy = nxty;
                nowz = nxtz;
            }
        }
        int ans = a[w % n] - '0' + b[w % m] - '0';
        int delta = a[(w + l + 1) % n] - '0' + b[(w + l + 1) % m] - '0';
        if (delta >= 10 || l >= T)
            ++ ans;
        printf("%d" , ans % 10);        
    }
    puts("");    
}

int main() {
    freopen("aplusb.in" , "r" , stdin);
    freopen("aplusb.out" , "w" , stdout);
    
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}
