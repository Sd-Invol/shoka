#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 10005;

char s[N] , t[N];

int n;

vector< pair<int , int> > S , T;

int p , a , b , c;

void check(vector< pair<int , int> > &V , int l , int r) {
    if (l < r)
        V.push_back(make_pair(l , r));
}

void trans(char *str , vector< pair<int , int> > &V) {
    p = 1;
    a = 0 , b = 0 , c = 0;
    int m = 0;
    for (int i = 0 ; i < n ; ) {
        int j = i;
        while (j < n && str[j] == str[i]) {
            ++ j;
        }
        int w = j - i;
        m += w;
        if (p == 1) {
            if (str[i] == '0') {
                b += w;
            } else {
                if (~w & 1) {
                    check(V , a , m - 1);
                    a += w;
                } else {
                    check(V , a , m - 2);
                    a += w - 1;
                    p = 2;
                }
            }
        } else if (p == 2) {
            if (str[i] == '0') {
                p = 3;
                c = w;
            } else {
                if (w & 1) {
                    check(V , a , m - 1);
                    c = 0;
                    a += w + 1;
                    p = 1;
                } else {
                    check(V , a , m - 2);
                    a += w;
                }
            }
        } else {
            if (str[i] == '0') {
                c += w;
            } else {
                if (w & 1) {
                    check(V , a , m - 1);
                    a += w;
                    swap(b , c);
                } else {
                    check(V , a , m - 2);
                    a += w;
                    check(V , a - 1 , m - 1);
                }
            }

        }
        i = j;
    }

}

int main() {
    scanf("%s" , s);
    scanf("%s" , t);
    n = strlen(s);

    trans(s , S);

    // printf("%d %d %d %d\n" , p , a , b , c);
    int ps = p , as = a , bs = b , cs = c;
    trans(t , T);

    //printf("%d %d %d %d\n" , p , a , b , c);
    int pt = p , at = a , bt = b , ct = c;

    if (ps == pt && as == at && bs == bt && cs == ct) {
        puts("YES");
        printf("%d\n" , (int)S.size() + (int)T.size());
        for (int i = 0 ; i < S.size() ; ++ i) {
            printf("%d %d\n" , S[i].first + 1 , S[i].second + 1);
        }
        reverse(T.begin() , T.end());
        for (int i = 0 ; i < T.size() ; ++ i) {
            printf("%d %d\n" , T[i].first + 1 , T[i].second + 1);
        }
    } else {
        puts("NO");


    }

}
