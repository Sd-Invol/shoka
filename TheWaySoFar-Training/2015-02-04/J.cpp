#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 200005;

int n , m;
int s[N];

void work() {
    int i , j , res = 0;
    scanf("%d%d" , &n,&m);
    for (i = 1 ; i <= n ; ++ i) {
        scanf("%d" , &s[i]);
        s[i] ^= s[i - 1];
    }
    for (j = 29 ; j >= 0 ; -- j) {
        int z = res >> j , flag = 1 , x = 0;
        int k = 0;
        for (i = 1 ; i <= n ; ++ i) {
            int y = (s[i] ^ s[k]) >> j; 
            if ((y & z) == y) {
                ++ x;
                k = i;
            }
        }
        if (k == n && x >= m)
            flag = 0;
        res |= flag << j;
    }
    cout << res << endl;
}

int main() {
    work();
    return 0;
}
