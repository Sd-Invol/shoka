#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int main() {
    LL x1 , x2 , y2 , y1;
    cin >> x1 >> y1 >> x2 >> y2;
    if (x1 > x2) {
        swap(x1 , x2);
        swap(y1 , y2);        
    }
    LL res = 1LL << 60;
    LL dx = abs(x1 - x2);
    LL dy = abs(y1 - y2);
    res = min(res , max(3LL , dx + 1) + max(3LL , dy + 1) + 3);
    if (y2 > y1) {
        dx += 2 , dy += 2;
        LL z = max(3LL , min(dx , dy) - 3);
        LL x = dx - z;
        LL y = dy - z;
        res = min(res , max(3LL , x) + max(3LL , y) + z);
    }
    for (int i = 1 ; i <= 100 ; ++ i) {
        LL y3 = y2 - i , x3 = x2 - i;
        dx = abs(x1 - x3);
        dy = abs(y1 - y3);
        res = min(res , max(3LL , dx + 1) + max(3LL , dy + 1) + max(i + 1 , 3));
    }
    swap(x1 , x2);
    swap(y1 , y2);      
    for (int i = 1 ; i <= 100 ; ++ i) {
        LL y3 = y2 - i , x3 = x2 - i;
        dx = abs(x1 - x3);
        dy = abs(y1 - y3);
        res = min(res , max(3LL , dx + 1) + max(3LL , dy + 1) + max(i + 1 , 3));
    }
    cout << res * 3 - 13 << endl;
    return 0;
    
}
