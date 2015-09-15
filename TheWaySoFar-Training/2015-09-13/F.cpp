#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <queue>
#include <vector>
#include <bitset>
#include <cctype>
#include <map>
using namespace std;
typedef long long LL;
const int N = 20005;
char str[N];
int n , f[N];
int MinR(char *str) {
    int i = 0 , j = 1 , k = 0 , len = n;
    while (i < len && j < len && k < len) {
        int cmp = str[(j + k) % len] - str[(i + k) % len];
        if (!cmp)
            ++ k;
        else {
            if (cmp < 0)
                j += k + 1;
            else
                i += k + 1;
            if (i == j)
                ++ j;
            k = 0;
        }
    }
    return min(i , j);
}
int MaxR(char *str) {
    int p = MinR(str);
    f[0] = f[1] = 0;
    for (int i = 1 ; i < n ; ++ i) {
        int j = f[i];
        while (j && str[(i + p) % n] != str[(j + p) % n])
            j = f[j];
        f[i + 1] = (str[(i + p) % n] == str[(j + p) % n]) ? j + 1 : 0;
    }
    int j = 0 , ret = -1;
    for (int i = 0 ; i + 1 < n + n ; ++ i) {
        while (j == n || j && str[i % n] != str[(j + p) % n])
            j = f[j];
        if (str[i % n] == str[(j + p) % n])
            ++ j;
        if (j == n)
            ret = i - n + 1;
    }
    return ret;
}
char t[N];

void work() {
    scanf("%d%s" , &n , str);
    int x = MinR(str);
    strcpy(t , str);
    rotate(t , t + x , t + n);
    reverse(str , str + n);
    int y = MaxR(str);
    rotate(str , str + y , str + n);
    y = n - y - 1;
    int z = strcmp(t , str);
    if (z != 0) {
        if (z > 0)
            printf("%d 0\n" , x + 1);
        else
            printf("%d 1\n" , y + 1);
    } else {
        if (x <= y)
            printf("%d 0\n" , x + 1);
        else
            printf("%d 1\n" , y + 1);
    }
}

extern int main2(void) __asm__ ("main2");
int main() {
    int __size__ = 256 << 20;  // 256Mb
    char *p = (char *)malloc(__size__) + __size__;
    __asm__ __volatile__(
        "movq  %0, %%rsp\n"
        "pushq $exit\n"
        "jmp main2\n"
        :: "r"(p));
    return 0;
}
int main2() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}
