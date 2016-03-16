#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 100005;

int n , K , L;
char str[N] , res[N];

int main() {
    scanf("%d%s" , &K , str);
    n = strlen(str);

    for (int i = 0 ; i < n ; ++ i) {
        if (str[i] == 's') {
            int j = i;
            while (str[j] == 's')
                ++ j;
            if (str[j] > 's') {
                for (int k = i ; k < j ; ++ k)
                    res[L ++] = 's';
            } else {
                int m = j - i;
                int d = min(m , K);
                K -= d , m -= d;
                for (int k = 0 ; k < m ; ++ k)
                    res[L ++] = 's';
            }
            i = j - 1;
        } else {
            res[L ++] = str[i];
        }
    }
    for (int i = L - 1 ; i >= 0 ; -- i)
        if (K && res[i] == 's')
            res[i] = -1 , -- K;
    for (int i = 0 ; i < L ; ++ i)
        if (res[i] > 0)
            putchar(res[i]);
    puts("");
    return 0;
}
