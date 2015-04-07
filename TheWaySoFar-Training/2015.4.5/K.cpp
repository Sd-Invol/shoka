#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 100005;

int mask;
char str[N];
int f[N];
#define get(i) (x >> i & 1)
void work() {
    int i , j;
    for (i = 0 ; i < 128 ; ++ i)
        f[i] = str[i] - '0';
    for (i = 0 ; i < 1 << 19 ; ++ i) {
        int x = i , y = i & mask , z , k;
        z = get(9) << 6 | get(7) << 5 | get(6) << 4 | get(4) << 3 | get(2) << 2 | get(1) << 1 | get(0);
        y |= f[z] << 4;
        z = get(11) << 6 | get(9) << 5 | get(8) << 4 | get(6) << 3 | get(4) << 2 | get(3) << 1 | get(1);
        y |= f[z] << 6;
        z = get(12) << 6 | get(10) << 5 | get(9) << 4 | get(7) << 3 | get(5) << 2 | get(4) << 1 | get(2);
        y |= f[z] << 7;
        z = get(14) << 6 | get(12) << 5 | get(11) << 4 | get(9) << 3 | get(7) << 2 | get(6) << 1 | get(4);
        y |= f[z] << 9;
        z = get(16) << 6 | get(14) << 5 | get(13) << 4 | get(11) << 3 | get(9) << 2 | get(8) << 1 | get(6);
        y |= f[z] << 11;
        z = get(17) << 6 | get(15) << 5 | get(14) << 4 | get(12) << 3 | get(10) << 2 | get(9) << 1 | get(7);
        y |= f[z] << 12;
        z = get(18) << 6 | get(17) << 5 | get(16) << 4 | get(14) << 3 | get(12) << 2 | get(11) << 1 | get(9);
        y |= f[z] << 14;
        x = y;
        z = get(14) << 6 | get(12) << 5 | get(11) << 4 | get(9) << 3 | get(7) << 2 | get(6) << 1 | get(4);
        k = f[z];
        if (k != (x >> 9 & 1)) {
            //printf("%d : %d %d %d\n" , i , x , k , z);
            //for (j = 0 ; j < 19 ; ++ j)
            //    printf("%d" , x >> j & 1);
            puts("no");
            return;
        }
    }
    puts("yes");        
}

int main() {
    mask = ~0;
    mask &= ~(1 << 4);
    mask &= ~(1 << 6);
    mask &= ~(1 << 7);
    mask &= ~(1 << 9);
    mask &= ~(1 << 11);
    mask &= ~(1 << 12);
    mask &= ~(1 << 14);    
    while (scanf("%s", str) , *str != '#')
        work();
    return 0;
}
