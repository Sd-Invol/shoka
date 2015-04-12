#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 200005;

int n , fa , fb;
struct pro {
    int id;
    int a , b;
    LL t;
    bool operator < (const pro& R) const {
        return make_pair(t , b) < make_pair(R.t , R.b);
    }
}p[N];
LL late[N];
int res[N << 1];
bool check(LL T) {
    int i , j , x , y;
    for (i = 0 ; i < n ; ++ i)
        late[i] = p[i].t + T - p[i].b;
    for (i = n - 2 ; i >= 0 ; -- i) {
        late[i] = min(late[i] , late[i + 1] - p[i].b);
     }

    T = 0;
    int cnt = 0;
    i = 0 , j = 0;

    while (j < n) {

        x = res[cnt] < 0 ? 0 : fa; 
        y = res[cnt] > 0 ? 0 : fb;
        if (i < n && T + x + p[i].a + fb <= late[j]) {
            T += x + p[i].a;
            res[++ cnt] = -p[i].id;
            i ++;
        } else {
            if (i <= j)
                return 0;            
            T += y + p[j].b;
            res[++ cnt] = p[j].id;
            j ++;
            while (j < i) {
                T += p[j].b;
                res[++ cnt] = p[j].id;
                ++ j;
            }
        }

    }
    return 1;
}

int main() {
    int i , j , x , y;
    scanf("%d%d%d",&n,&fa,&fb);
    for (i = 0 ; i < n ; ++ i) {
        scanf("%d%d%lld" , &p[i].a , &p[i].b , &p[i].t);
        p[i].id = i + 1;
    }
    sort(p , p + n);
    LL l = 0 , r = 1e15 , m;
    while (l < r) {
        m = l + r >> 1;
        if (check(m))
            r = m;
        else
            l = m + 1;
    }
    check(r);
    cout << r << endl;
    for (i = 1 ; i <= n + n ; ++ i)
        printf("%d%c" , res[i] , " \n"[i == n + n]);
}

