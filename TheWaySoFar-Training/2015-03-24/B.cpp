#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int ans1 = 0;

int calc(int A, int B, int C, int D, int mask) {
    int ans = 0;
    if (mask == 0 || mask == 3) {
        if ((A - C == 2) && (B - D) == 2) {
            if ((B % 4 != 0) ^ (A % 4 != 0)) ++ ans1;
        }
        else if ((A - C) == 2 && D % 4 == 0) {
                 if (A % 4 == 0) ++ans;
            }
        //if ((A - C) % 4 == 0) ++ans;
    }
    else {
        if (A % 4 == 0) ++ans;
    }
    return ans;
}

int main() {
    int A, B, C, D;
    scanf("%d%d%d%d", &A, &B, &C, &D);
    int ans = 0; 
    for (int i = 0; i < 1 << 2; ++i)
        ans += calc(A, B, C, D, i) + calc(B, A, D, C, i);
    printf("%d\n", ans + ans1 / 2);
    return 0;
}
