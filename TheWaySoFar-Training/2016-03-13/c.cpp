#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 15;

int n;
char s[N] , t[N];
char p[N] , q[N];


int main() {
    scanf("%s%s" , s , t);
    n = strlen(s);
    double res = 1;

    for (int i = 0 ; i < n ; ++ i) {
        scanf("%s" , q);
        p[0] = q[0];
        p[1] = q[5];
        p[2] = q[2];
        p[3] = q[4];
        p[4] = q[1];
        p[5] = q[3];
        p[6] = 0;
        int cnt = 0 , w = 0;
        for (int j = 0 ; j < 6 ; ++ j) {
            if (p[j] == s[i]) {
                cnt += 2;

                for (int k = 0 ; k < 3 ; ++ k) {
                    if (k != (j >> 1)) {
                        int flag = 0;
                        for (int l = 0 ; l < 6 ; ++ l) {
                            if (p[l] == t[i] && (l >> 1) != k)
                                flag = 1;
                        }
                        w += flag;
                    }
                }

            }

        }
        res = res * w / cnt;
        //printf("%d : %f\n"  , i , 1.0 * w / cnt);
    }
    printf("%.10f\n" , res);
    return 0;
}
