#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 1005;
string str;
int main() {

    while (cin >> str) {
        if (str == "#")
            break;
        int n = str.size() , m = 0;
        LL a = -1 , b = 1;
        while (n > 0) {
            string t = str.substr(n - 4 , 4);
            if (t == "west") {
                if (a == -1) {
                    a = 90;
                } else {
                    LL x = a * (1LL << m) + b * 90;
                    LL y = b * (1LL << m);
                    LL z = __gcd(x , y);
                    a = x / z , b = y / z;
                }
                n -= 4;
            } else {
                if (a == -1) {
                    a = 0;
                } else {
                    LL x = a * (1LL << m) - b * 90;
                    LL y = b * (1LL << m);
                    LL z = __gcd(x , y);
                    a = x / z , b = y / z;
                }
                n -= 5;
            }
            ++ m;
        }
        LL c = __gcd(a , b);
        a /= c , b /= c;
        if (b < 0) a = -a , b = -b;
        if (b == 1)
            printf("%lld\n" , a);
        else
            printf("%lld/%lld\n" , a , b);
    }
    
    return 0;
}
