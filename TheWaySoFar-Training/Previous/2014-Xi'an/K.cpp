#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 100005;
int ca;

LL gcd(LL A , LL B) {
    if (B == 0)
        return !!A + 1;
    return (A - 1) / B + gcd(B , A % B);
}

void work() {
    LL A , B;
    cin >> A >> B;
    printf("Case #%d: %I64d\n" , ++ ca , gcd(A , B));
}

int main() {
    int _; scanf("%d",&_); while (_ --)
        work();
    return 0;
}
