#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
const int N = 1005;
int n , X[N] , Y[N];
vector<double> V;

int main() {
    scanf("%d" , &n);
    for (int i = 0 ; i < n ; ++ i)
        scanf("%d%d" , &X[i] , &Y[i]);
    for (int i = 0 ; i < n ; ++ i) {
        for (int j = 0 ; j < i ; ++ j) {
            int dx = X[i] - X[j];
            int dy = Y[i] - Y[j];
            if (!dx) continue;

            double x = (X[i] + X[j]) / 2.0;
            double y = (Y[i] + Y[j]) / 2.0;
            swap(dx , dy) , dy = -dy;
            x -= y / dy * dx;
            V.push_back(x);
        }
    }
    sort(V.begin() , V.end());
    int res = 1;
    n = V.size();
    for (int i = 0 ; i < n ; ++ i) {
        int j = i;
        while (j < n && fabs(V[i] - V[j]) < 1e-8)
            ++ j;
        ++ res;
        i = j - 1;
    }
    printf("%d\n" , res);
    return 0;
}
