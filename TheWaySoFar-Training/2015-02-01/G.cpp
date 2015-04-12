#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const ULL MAGIC = 1e9 + 7;
const int N = 1005;
int n , m , a[N];
LL res;
ULL Hash[N] , power[N];
map<ULL , vector< pair<int , int> > > Map;
pair<int , int> s[N];

void cal(vector< pair<int , int> >& V) {
    sort(V.begin() , V.end());
    int top = 0;
    for (auto it : V) {
        while (top && it.second >= s[top].second)
            -- top;
        s[++ top] = it;
    }
    for (int i = 1 ; i <= top ; ++ i)
        res += (LL) s[i].second * (s[i].first - s[i - 1].first);
}

void work() {
    int i , j , k , x , y;
    scanf("%d%d",&n,&m);
    for (i = 1 ; i <= m ; ++ i)
        scanf("%d" , &a[i]);
    a[0] = 0 , a[m + 1] = n + 1;
    x = max(a[1] - 1 , n - a[m]);
    power[0] = 1;
    for (i = 1 ; i < m ; ++ i) {
        x = max(x , a[i + 1] - a[i] - 1);
        Hash[i] = Hash[i - 1] * MAGIC;
        Hash[i] += a[i + 1] - a[i];
        power[i] = power[i - 1] * MAGIC;
    }
    res += x;
    vector< pair<int , int> > single;
    for (i = 1 ; i <= m ; ++ i) {
        single.push_back(make_pair(a[i] - a[i - 1] , a[i + 1] - a[i]));    
    }
    cal(single);
    for (i = 1 ; i <= m ; ++ i)
        for (j = i + 1 ; j <= m ; ++ j) {
            ULL H = Hash[j - 1] - Hash[i - 1] * power[j - i];
            Map[H].push_back(make_pair(a[i] - a[i - 1] , a[j + 1] - a[j]));
        }
    for (auto& it : Map)
        cal(it.second);
    cout << res << endl;
}

int main() {
    work();    
    return 0;
}
