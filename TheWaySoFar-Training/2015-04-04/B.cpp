#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

bool dis[55][55][2505];
int map[55][55];

int gett(int ch) {
    if (ch == '^') return 0;
    if (ch == '>') return 1;
    if (ch == 'v') return 2;
    if (ch == '<') return 3;
    return -1;
}

const int C[4] = {-1, 0, 1, 0};
const int D[4] = {0, 1, 0, -1};

int main() {
    //cout << dis
    memset(dis, 0, sizeof(dis));
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            int ch;
            while (ch = getchar(), gett(ch) == -1); 
            map[i][j] = gett(ch);
        }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            for (int k = 0; k < 4; ++k) {
                int x = i + C[k], y = j + D[k];
                int val = (k - map[i][j] + 4) % 4;
                if (val == 3) val = 1;
                if (val == 0) val = 1;
                if (x < 1 || y < 1 || x > n || y > m)
                    dis[i][j][val] = 1;
                else {
                    if (abs(map[x][y] - k) != 2)
                        dis[i][j][val] = 1;
                }
                //if (dis[i][j][val])
                //    printf("!%d %d %d\n", i, j, val);
            }
    for (int num = 0; num < 2500; ++num)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) 
                for (int k = 0; k < 4; ++k) {
                    int x = i + C[k], y = j + D[k];
                    int val = (k - map[i][j] + 4) % 4;
                    if (val == 3) val = 1;
                    if (val == 0) val = 1;
                    if (x < 1 || y < 1 || x > n || y > m) continue;
                    if (abs(map[x][y] - k) == 2)
                        dis[i][j][num + val] |= dis[x][y][num];
           
                }
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            int k = map[i][j];
            if (k >= 2) continue;
            int x = i + C[k], y = j + D[k];
            if (x < 1 || y < 1 || x > n || y > m) continue;
            if (abs(k - map[x][y]) != 2) continue;
            for (int L = 0; ; ++L)
                if (dis[x][y][L] || dis[i][j][L]) {
                    ans += L;
                    break;
                }
        }
    printf("%d\n", ans);
}
