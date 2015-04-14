#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e6 + 5;
const int P = 1e9 + 9;

LL n; 
int d[N] , len;
int main() {
    cin >> n;
    while (n) {
        d[len ++] = n & 1;
        n >>= 1;
    }
    bool flag;
    do {
        flag = 0;
        for (int i = 0 ; i < len ; ++ i)
            if (d[i] > 1) {
                d[i] -= 2;
                d[i + 1] += 1;
                flag = 1;
                break;
            }
        if (flag) {
            while (d[len])
                len ++;
            continue;
        }
        for (int i = 0 ; i + 1 < len ; ++ i)
            if (d[i] == 1 && d[i + 1] == 1) {
                d[i] = -1;
                d[i + 1] = 0;
                d[i + 2] ++;;
                flag = 1;
                break;
            }
        while (d[len])
            len ++;        
    } while (flag);
    for (int i = len - 1 ; i >= 0 ; -- i)
        printf("%d%c" , d[i] , " \n"[i == 0]);
    return 0;
}
