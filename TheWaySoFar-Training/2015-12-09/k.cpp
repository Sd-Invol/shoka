#include <cstdio>
#include <cstring>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;
const int N = 10;

long double res;
const long double pi = acos(-1);

void cal(vector<int> &a) {
    int n = a.size();
    long double mx = 1 , w = 1;
    for (int i = 1 ; i < n ; ++ i) {
        w = w * a[(i + n - 1) % n] / a[(i + 1) % n];
        mx = max(w , mx);
    }    
    long double l = -1.0 / mx , r = 1.0 / mx , m;
    for (int T = 0 ; T < 100 ; ++ T) {
        m = (l + r) / 2;
        long double sum = acos(m);
        w = m;
        for (int i = 1 ; i < n ; ++ i) {            
            w = w * a[(i + n - 1) % n] / a[(i + 1) % n];

            w = min(w , (long double)1.0);
            w = max(w , (long double)-1.0);            
            sum += acos(w);
        }
        assert(sum == sum);
        if (sum > pi + pi)
            l = m;
        else
            r = m;
    }
    w = (l + r) / 2; long double sum = acos(w);
    for (int i = 1 ; i < n ; ++ i) {            
        w = w * a[(i + n - 1) % n] / a[(i + 1) % n];
        w = min(w , (long double)1.0);
        w = max(w , (long double)-1.0);            
        sum += acos(w);
    }
    if (fabs(sum - pi - pi) > 1e-10)
        return;
    w = (l + r) / 2;
    long double area = 0;
    for (int i = 0 ; i < n ; ++ i) {
        w = min(w , (long double)1.0);
        w = max(w , (long double)-1.0); 
        area += a[i] * a[(i + 1) % n] * sqrt(1 - w * w);        
        w = w * a[i] / a[(i + 2) % n];
    }
    assert(area == area);
    res = max(res , area / 2);
}
int n , a[N] , b[N];

int main() {    
    scanf("%d" , &n);
    for (int i = 0 ; i < n ; ++ i)
        scanf("%d" , &a[i]);    
    sort(a , a + n , greater<int>());
    for (int k = 3 ; k <= n ; ++ k) {
        int m = 0;
        for (int i = k - 1 ; i >= 0 ; -- i)
            b[m ++] = a[i];        
        do {
            vector<int> V;
            for (int i = 0 ; i < m ; ++ i) {               
                V.push_back(b[i]);
            }
            cal(V);
        } while (next_permutation(b + 1 , b + m));
    }
    assert(res == res);
    printf("%.15f\n" , (double)res);
    return 0;
}
