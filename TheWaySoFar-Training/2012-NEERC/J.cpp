#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 100005;
int A , B , C , n;
int res[N] , cnt , pos;

void move(int k) {
    printf("%d " , pos);
    pos += k;
    if (abs(k) == 1) {
        assert(A > 0);
        -- A;
    }
    if (abs(k) == 2) {
        assert(B > 0);
        -- B;
    }
    if (abs(k) == 3) {
        assert(C > 0);
        -- C;
    }
}

void work() {
    int i , j , k;
    scanf("%d%d%d",&A,&B,&C);
    pos = 0 , cnt = 1;
    j = C % 3 , k = C / 3;
    if (j == 0) {
        for (i = 0 ; i < k ; ++ i)
            move(3);
        move(1);
        for (i = 0 ; i < k ; ++ i)
            move(-3);
        move(1);
        for (i = 0 ; i < k ; ++ i)
            move(3);
    } else if (j == 1) {
        for (i = 0 ; i <= k ; ++ i)
            move(3);
        move(-2);
        for (i = 0 ; i < k ; ++ i)
            move(-3);
        move(1);
        for (i = 0 ; i < k ; ++ i)
            move(3);
        move(2);
    } else {
        for (i = 0 ; i <= k ; ++ i)
            move(3);
        move(-1);
        for (i = 0 ; i < k ; ++ i)
            move(-3);
        move(-1);
        for (i = 0 ; i <= k ; ++ i)
            move(3);
    }
    while (A > 1)
        move(1);
    assert(C == 0);
    j = B % 2 , k = B / 2;
    if (j == 0) {
        for (i = 0 ; i < k ; ++ i)
            move(2);
        move(1);
        for (i = 0 ; i < k ; ++ i)
            move(-2);
    } else {
        for (i = 0 ; i <= k ; ++ i)
            move(2);
        move(-1);
        for (i = 0 ; i < k ; ++ i)
            move(-2);
    }
    assert(A == 0) , assert(B == 0);
    printf("%d\n" , pos);
}

int main()
{
    freopen("jumping.in","r",stdin);
    freopen("jumping.out","w",stdout);
    int _; scanf("%d",&_); while (_ --)
        work();
    return 0;
}
