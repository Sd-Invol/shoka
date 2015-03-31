#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

const int N = 1e2 + 5;
typedef long long LL;
int p , q , n , d;
int res[N * 10][2];
map< pair<int , int> , int > f;
void work() {
    int i , x , y;
    f.clear();
    n = 0;
    d = __gcd(p , q);
    p /= d , q /= d;
    f[make_pair(p , q)] = ++ n;
    while (1) {
        if (q == p + p) {
            res[n][0] = -1;
            res[n][1] = -2;
            break;
        } else if (q > p + p) {
            p <<= 1;
            d = __gcd(p , q);
            p /= d , q /= d;    
            res[n][0] = -2;
            if (f.count(make_pair(p , q))) {
                res[n][1] = f[make_pair(p , q)];
                break;
            } else {
                res[n][1] = n + 1;
                f[make_pair(p , q)] = ++ n;
            }
        } else {
            p = p + p - q;            
            d = __gcd(p , q);
            p /= d , q /= d;
            res[n][0] = -1;
            if (f.count(make_pair(p , q))) {
                res[n][1] = f[make_pair(p , q)];
                break;
            } else {
                res[n][1] = n + 1;
                f[make_pair(p , q)] = ++ n;
            }  
        }        
    }
    printf("%d\n" , n + 2);
    for (i = 1 ; i <= n ; ++ i) {
        x = res[i][0] < 0 ? n - res[i][0] : res[i][0];
        y = res[i][1] < 0 ? n - res[i][1] : res[i][1];
        printf("%d %d\n" , x , y);
    }
}

int main() {
    freopen("drunkard.in" , "r" , stdin);
    freopen("drunkard.out" , "w" , stdout);
    while (scanf("%d%d",&p,&q) , p || q)
        work();
    return 0;
}
