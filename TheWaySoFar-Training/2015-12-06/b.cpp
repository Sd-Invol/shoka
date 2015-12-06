#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
const int N = 1005;
int F[N][4005] , len[N];

void init() {
    len[0] = 1 , F[0][0] = 1;
    for (int i = 1 ; i < N ;  ++ i) {

        for (int j = 0 ; j < len[i - 1] ; ++ j) {
            if (F[i - 1][j]) {
                ++ F[i][j + 1];
                ++ F[i][j + 3];
            }
        }
        len[i] = len[i - 1] + 3;
        for (int j = 0 ; j < len[i] ; ++ j)
            if (F[i][j] > 1) {
                F[i][j] -= 2;
                F[i][j + 1] += 1;
            }
        while (F[i][len[i]]) {
            if (F[i][len[i]] > 1) {
                F[i][len[i]] -= 2;
                F[i][len[i] + 1] += 1;            
            }
            ++ len[i];
        }
    }
}

int bo[10005][305];
int num[10005][305];
int Len[10005], Li[10005];
int res[10005];

int main() {
    init();
    int n;
    scanf("%d", &n);
    Len[0] = 1;
    bo[1][0] = 1;
    Len[1] = 1;
    num[1][1] = 1;
    Li[0] = Li[1] = 1;
    int m = 1;
    for (int i = 2; m < n; ++i) {
        int tmp = m;
        for (int j = 0; j <= tmp && m < n; ++j) {
            if (res[j]) continue;
            //cout << m << endl;
            if (i == 3 && j == 2) {
                // printf("%d\n", bo[j][i - 1]);
            }
            if (F[i - 1][i - 1] ^ bo[j][i - 1]) {
                ++m;
                Len[m] = i;
                for (int k = 1; k <= Len[j]; ++k) {
                    num[m][k] = num[j][k];
                }
                num[m][i] = 1;
                int x = 0;
                for (int k = 0; k < len[i]; ++k) {
                    bo[m][k] = F[i - 1][k] + bo[j][k] + x;
                    if (bo[m][k] > 1) {
                        bo[m][k] -= 2;
                        x = 1;
                    }
                    else x = 0;
                }
                Li[m] = len[i];
                while (x > 0) {
                    ++Li[m];
                    bo[m][Li[m] - 1] = 1;
                    x = 0;
                }
            }
            if (bo[j][i - 1] == 1) {
                res[j] = 1;
            }
        }
    }
    for (int i = Len[m]; i > 0; --i)
        putchar('0' + num[m][i]);
    puts("");
    return 0;
}
