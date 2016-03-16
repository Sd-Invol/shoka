#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 2e5 + 5;

char str[N];

int main() {
    gets(str);
    int n = strlen(str);
    int q;
    scanf("%d", &q);
    int rev = 0, sft = 0;
    while (q--) {
        int x;
        scanf("%d", &x);
        rev ^= 1;
        sft = n - sft;
        sft = (sft + n * 10) % n;

        sft = (sft + x) % n;
    }
    if (rev) reverse(str, str + n);
    for (int i = 0; i < n; ++i)
        putchar(str[(i - sft + n) % n]);
    puts("");
}
