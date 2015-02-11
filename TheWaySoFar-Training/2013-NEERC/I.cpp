#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 100005;

int p , v;
LL L[N] , R[N];
char str[N];
void work() {
    cin >> p >> v;

    for (int i = 0 ; i <= v ; ++ i)
        L[i] = 0 , R[i] = p;
    LL sum = (LL) (v + 1) * (p + 1);
    int T = 100;
    for (int t = 0 ; t < T ; ++ t) {
        if (sum == 1) {
            for (int i = 0 ; i <= v ; ++ i)
                if (L[i] <= R[i]) {
                    printf("answer %I64d\n" , (LL)i * t + L[i]);
                    fflush(stdout);
                }
            return;
        }
        int l = 0 , r = 1e9 , m;
        while (l < r) {
            m = l + r >> 1;
            LL cnt = 0;
            for (int i = 0 ; i <= v ; ++ i)
                if (L[i] <= R[i]) {
                    LL w = m - (LL) t * i;
                    if (w <= R[i])
                        cnt += max(0LL ,  w - L[i] + 1);
                    else
                        cnt += R[i] - L[i] + 1;
                }
            if (cnt >= sum - cnt)
                r = m;
            else
                l = m + 1;
        }
        printf("check 0 %d\n" , l);
        fflush(stdout);
        scanf("%s" , str);
        if (*str == 'Y') {
            for (int i = 0 ; i <= v ; ++ i)
                R[i] = min(R[i] , l - (LL) t * i);
        } else {
            for (int i = 0 ; i <= v ; ++ i)
                L[i] = max(L[i] , l - (LL) t * i + 1);
        }
        sum = 0;
        for (int i = 0 ; i <= v ; ++ i)
            sum += max(0LL , R[i] - L[i] + 1);
    }
    printf("answer 0\n");
    fflush(stdout);
}
int main() {
    work();
    return 0;
}
