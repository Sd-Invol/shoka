#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <bitset>
using namespace std;

bitset<1005> swit[36], light[1005];

int main() {
    int n, m, q;
    while (scanf("%d%d%d", &n, &m, &q),n || m || q) {
        for (int i = 0; i < q; ++i) {
            int p = 0;
            for (int j = 0; j < n; ++j) {
                int ch;
                while (ch = getchar(), !isdigit(ch));
                int p = 0;
                if (ch == '1') p = 1;
                if (i == 0) swit[j][i] = p;
                else swit[j][i] = swit[j][i - 1] ^ p;
                
            }
            for (int j = 0; j < m; ++j) {
                int ch;
                while (ch = getchar(), !isdigit(ch));
                if (ch == '1') light[j][i] = 1;
            }
        }
        for (int i = 0; i < m; ++i) {
            int mark = -1;
            for (int j = 0; j < n && mark != -2; ++j) {
                if ((swit[j] & light[i]) == light[i] && light[i].count() == swit[j].count()) {
                    if (mark == -1) mark = j;
                    else mark = -2;
                }
            }
            if (mark < 0) putchar('?');
            else if (mark < 10) putchar('0' + mark);
            else putchar('A' + mark - 10);
        }
        puts("");
        for (int i = 0; i < q; ++i) {
            for (int j = 0; j < n; ++j)
                swit[j][i] = 0;
            for (int j = 0; j < m; ++j)
                light[j][i] = 0;
        }
    }
    return 0;
}
