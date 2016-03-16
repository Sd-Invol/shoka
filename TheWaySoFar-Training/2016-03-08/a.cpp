#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 6005;

int num[N], color[N];
int C[N][26], d[N];
int grid[3005][3005];
int bo[6005];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            int ch;
            while (ch = getchar(), ch != '?' && !isalpha(ch));
            if (ch != '?') {
                C[i][ch - 'a'] ++;
                C[j + n][ch - 'a'] ++;
                grid[i][j] = ch - 'a';
            } else grid[i][j] = -1;
        }
    queue<int> que;
    for (int i = 1; i <= 2 * n; ++i) {
        for (int j = 0; j < 26; ++j)
            if (C[i][j]) ++d[i];
        if (d[i] <= 1) que.push(i); 
    }
    int t = 0;
    while (!que.empty()) {
        int id = que.front(); que.pop();
        if (bo[id]) continue;
        //printf("%d %d\n", id, d[id]);
        /*if (id == 3) {
            for (int i = 1; i <= n; ++i)
                for (int j = 1; j <= n; ++j)
                    printf("%d%c", grid[i][j], " \n"[j == n]);
                    }*/
        int col = 0;
        for (int i = 1; i <= n; ++i) {
            if (id <= n && grid[id][i] >= 0) col = grid[id][i];
            if (id > n && grid[i][id - n] >= 0)
                col = grid[i][id - n];
        }
        //if (id == 3) cout << col << endl;
        bo[id] = 1;
        ++t;
        num[t] = id;
        color[t] = col;
        for (int i = 1; i <= n; ++i) {
            if (id <= n) {
                if (grid[id][i] == -1) continue;
                if (--C[i + n][grid[id][i]] == 0) {
                    if (--d[i + n] <= 1) que.push(i + n);
                }
                grid[id][i] = -1;
            }
            else {
                if (grid[i][id - n] == -1) continue;
                if (--C[i][grid[i][id - n]] == 0) {
                    if (--d[i] <= 1) que.push(i);
                }
                grid[i][id - n] = -1;
            }
        }
    }
    for (int i = t; i >= 1; --i) {
        if (num[i] <= n) {
            printf("h %d %c\n", num[i], 'a' + color[i]);
        }
        else printf("v %d %c\n", num[i] - n, 'a' + color[i]);
    }
    return 0;
}
