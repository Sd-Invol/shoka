#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 200005;

void work() {
    int L , S;
    cin >> L >> S;
    if (L & 1) {
        puts("-1");
        return;        
    }
    L >>= 1;
    int a = L >> 1;
    int b = L - a;
    if ((LL)a * b == S) {
        printf("%d\n" , 4);
        printf("%d %d\n" , 0 , 0);
        printf("%d %d\n" , 0 , a);
        printf("%d %d\n" , b , a);
        printf("%d %d\n" , b , 0);
        return;
    }
    if (S < a + b - 1 || S > (LL) a * b) {
        puts("-1");
        return;
    }
    S -= a + b - 1;
    int x = S / (b - 1);
    int y = S % (b - 1);
    vector< pair<int , int> > V;
    V.push_back(make_pair(0 , 0));
    V.push_back(make_pair(b , 0));
    V.push_back(make_pair(b , x + 1));
    V.push_back(make_pair(b - (b - 1 - y) , x + 1));
    V.push_back(make_pair(b - (b - 1 - y) , x + 2));
    V.push_back(make_pair(1 , x + 2));
    V.push_back(make_pair(1 , a));
    V.push_back(make_pair(0 , a));
    V.resize(unique(V.begin() , V.end()) - V.begin());
    printf("%d\n" , (int)V.size());
    for (auto it : V) {
        printf("%d %d\n" , it.first , it.second);
    }
}

int main() {
    work();    
    return 0;
}
