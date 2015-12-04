#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 1005;

int a[N];
int bo[N][N];

int check(int x, int y) {
    if (x == y) return 0;
    if (bo[x][y] != -1) return bo[x][y];
    printf("1 %d %d\n", x, y);
    fflush(stdout);
    char str[10];
    scanf("%s", str);
    if (str[0] == 'Y') {
        bo[x][y] = 1;
        bo[y][x] = 0;
        return bo[x][y] = 1;
    }
    else {
        bo[x][y] = 0;
        bo[y][x] = 1;
        return bo[x][y] = 0;
        
    }
}

int main() {
    // srand(236345457);
    memset(bo, -1, sizeof(bo));
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        a[i] = i;
    //for (int i = 2; i <= n; ++i) {
    //    int p = (rand() % (i - 1)) + 1;
    //    swap(a[i], a[p]);
    // }
    stable_sort(a + 1, a + 1 + n, check);
    printf("0");
    for (int i = 1; i <= n; ++i)
        printf(" %d", a[i]);
    puts("");
    fflush(stdout);
    return 0;
}