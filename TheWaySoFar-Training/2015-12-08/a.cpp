#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <map>
using namespace std;
const int N = 250005;

typedef map<int, int>::iterator IT;

int a[N], o[N];

int main() {
    int n;
    char str[5];        
    scanf("%d" , &n);
    map<int, int> num;
    for (int i = 0 ; i < n ; ++ i) {
        scanf("%s%d" , str , a + i);
        o[i] = (*str == '+');
        if (o[i] == 1)
            ++num[a[i]];
        else if (--num[a[i]] == 0)
            num.erase(a[i]);
        long double w = 1;
        double ans = 0;
        for (IT it = num.begin(); it != num.end(); ++it) {
            w = w * (it -> second + 1);
            ans += (double)(it -> first) * (it -> second) / w;
            if (w > 1e50) break;
        }
        if (w <= 1e40) {
            double p = w / (w - 1);
            ans = ans * p;
        }
        printf("%.10f\n", ans);
    }
    
    return 0;
}
