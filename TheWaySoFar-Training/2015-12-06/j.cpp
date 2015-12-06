#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <set>
using namespace std;

typedef long long LL;
const int N = 1005;
int a[N], bo[N];
char S[N];
int n;
int T[N];

int check() {
    int t = 0;
    for (int i = 0; i < n; ++i)
        S[i] = a[i] + '0';
    S[n] = '\0';
    puts(S);
    fflush(stdout);
    scanf("%d", &t);
    /*for (int i = 0; i < n; ++i)
        t += (a[i] == 0);
    if (t != n / 2 && t != n)
    t = 0;*/
    if (t == n) exit(0);
    return t;
}



int main() {
  
    srand(time(0));
    scanf("%d", &n);
    while (1) {
        for (int i = 0; i < n; ++i) {
            a[i] = rand() % 2;
        }
        if (check() == n / 2) break;
    }
    int l = 0;
    for (int i = 1; i < n; ++i) {
        a[i] = a[i] ^ 1;
        a[0] = a[0] ^ 1;
        if (check() == n / 2)
            bo[i] = 1;
        else bo[i] = 0;
        a[0] ^= 1;
        a[i] ^= 1;
    }
    for (int i = 0; i < n; ++i)
        if (bo[i] == 0)
            a[i] ^= 1;
    check();
    for (int i = 0; i < n; ++i)
        a[i] ^= 1;
    check();
    return 0;
}
