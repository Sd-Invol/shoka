#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

struct Oper {
    int op;
    pair<int, int> A, B;
};

vector<Oper> V;

void newop(int op , int a , int b , int c = 0 , int d = 0) {
    Oper T;
    T.op = op;
    T.A = make_pair(a , b);
    T.B = make_pair(c , d);
    V.push_back(T);
    assert(V.size() <= 15000u);
}


int main() {
    int a , b , c , d;
    cin >> a >> b >> c >> d;
    bool swapd = 0;
    if (a > b) {
        swap(a , b);
        swap(c , d);
        swapd = 1;
    }
    int delta = b - a;
    if (a < b) {
        while (delta % 2 == 0)
            delta /= 2;
        if (c >= d || (d - c) % delta != 0) {
            puts("0");
            return 0;
        }
    } else {
        if (c != d) {
            puts("0");
            return 0;
        }
    }

    while (b - a != delta) {
        if (a % 2 == 0 && b % 2 == 0) {
            newop(2 , a , b);
            a /= 2 , b /= 2;
        } else {
            newop(1 , a , b);
            ++ a , ++ b;
        }
    }
    while (a != 1) {
        for (int i = 0 ; a + i < b ; ++ i) {
            newop(1 , a + i , b + i);
        }
        newop(3 , a , b , b , b + b - a);
        b += b - a;
        if (a & 1) {
            newop(1 , a , b);
            ++ a , ++ b;
        }
        newop(2 , a , b);
        a /= 2 , b /= 2;
    }

    for (int i = 0 ; i < d - c ; ++ i) {
        newop(1 , a + i , b + i);
    }
    while (b - a < d - c) {
        newop(3 , a , b , b , b + delta);
        b += delta;
    }

    for (int i = 0 ; i < c - a ; ++ i) {
        newop(1 , a + i , b + i);
    }

    if (swapd) {
        for (int i = 0 ; i < (int)V.size() ; ++ i) {
            if (V[i].op == 3) {
                swap(V[i].A.first , V[i].A.second);
                swap(V[i].B.first , V[i].B.second);
                swap(V[i].B , V[i].A);
            } else {
                swap(V[i].A.first , V[i].A.second);
            }
        }
    }
    printf("%d\n" , (int)V.size());
    for (int i = 0 ; i < (int)V.size(); ++ i) {
        if (V[i].op <= 2) {
            printf("%d %d %d\n" , V[i].op , V[i].A.first , V[i].A.second);
        } else {
            printf("%d %d %d %d %d\n" , V[i].op , V[i].A.first , V[i].A.second , V[i].B.first , V[i].B.second);
        }
    }
    return 0;
}
