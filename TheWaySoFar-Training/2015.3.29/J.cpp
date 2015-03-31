#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 1000005;

LL n , m;
int Q;

LL power(LL A , LL B , LL C) {
    LL res = 1;
    while (B) {
        if (B & 1)
            res *= A , res %= C;
        A *= A , A %= C , B >>= 1;
    }
    return res;
}
LL F;

pair<LL , LL> cal(LL n , int x , int y) {
    if (!n) return make_pair(0 , 1);
    pair<LL , LL> res;
    res.second = power(F , n / y , y);
    res.first = (n / y) * (y / x);
    pair<LL , LL> sum = cal((n / y) * (y / x) , x , y);
    res.first += sum.first;
    res.second *= sum.second , res.second %= y;
    //cout << n << ' ' << x << ' ' << y << ' ' << res.first << ' ' << res.second << endl;
    for (LL i = y * (n / y) + 1 ; i <= n ; ++ i) {
        LL z = i;
        while (z % x == 0)
            z /= x , ++ res.first;
        res.second *= z % y , res.second %= y;
    }
    //     cout << n << ' ' << x << ' ' << y << ' ' << res.first << ' ' << res.second << endl;
    return res;
}

vector< pair<LL , LL> > fac;

void exgcd(LL a, LL b, LL &x, LL &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return;
    }
    exgcd(b, a % b, x, y);
    LL tmp = x;
    x = y;
    y = tmp - a / b * y;
}

LL CRT() {
    LL res = 0, M = 1;
    for (int i = 0; i < fac.size(); ++i) M *= fac[i].first;
    for (int i = 0; i < fac.size(); ++i) {
        LL Mi = M / fac[i].first , x , y;
        exgcd(Mi, fac[i].first, x, y);
        res = (res + Mi * x % M * fac[i].second % M + M) % M;
    }
    return res;
}

int main() {
    scanf("%lld%lld%d", &n,&m,&Q);
    int i , j , x , y , z ;
    x = Q;
    
    for (i = 2 ; i <= x ; ++ i) {
        if (x % i == 0) {
            y = 1 , z = 0;
            while (x % i == 0)
                x /= i , y *= i , ++ z;
            F = 1;
            for (j = 1 ; j <= y ; ++ j) {                
                if (j % i != 0)
                    F *= j , F %= y;
            }
            pair<LL , LL> a = cal(n , i , y);            
            pair<LL , LL> b = cal(m , i , y);            
            pair<LL , LL> c = cal(n - m , i , y);
            int d = a.first - b.first - c.first;
            if (d >= z)
                fac.push_back(make_pair(y , 0));
            else {
                LL p = a.second;
                //cout << p << endl;
                p *= power(b.second , y / i * (i - 1) - 1 , y);
                p %= y;
                p *= power(c.second , y / i * (i - 1) - 1 , y);
                p %= y;
                while (d --)
                    p *= i , p %= y;
                fac.push_back(make_pair(y , p));
            }                        
        }        
    }
    
    // for (i = 0 ; i < fac.size() ; ++ i)
    //     printf("%lld %lld\n" , fac[i].first , fac[i].second);
    cout << CRT() << endl;
    return 0;
}
