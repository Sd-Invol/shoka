#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
#include <cctype>
#include <unordered_map>
#include <queue>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
const int N = 20005;
uint n , ca;
struct Matrix {
    int n , m;
    uint a[2][2];
    Matrix (int _n , int _m) {
        n = _n , m = _m;
        memset(a , 0 , sizeof(a));
    }
    uint* operator [] (int x) {
        return a[x];
    }
    const uint* operator [] (int x) const {
        return a[x];
    }
    bool operator == (const Matrix& R) const {
        for (int i = 0 ; i < n ; ++ i)
            for (int j = 0 ; j < m ; ++ j)
                if (a[i][j] != R[i][j])
                    return 0;
        return 1;
    }
    bool isI() {
        for (int i = 0 ; i < n ; ++ i)
            for (int j = 0 ; j < m ; ++ j)
                if (a[i][j] != (i == j))
                    return 0;
        return 1;
    }
};
Matrix operator * (const Matrix& A , const Matrix& B) {
    Matrix res(A.n , B.m);
    for (int i = 0 ; i < A.n ; ++ i)
        for (int j = 0 ; j < A.m ; ++ j) if (A[i][j])
            for (int k = 0 ; k < B.m ; ++ k) {
                res[i][k] += A[i][j] * B[j][k] % n;
                res[i][k] %= n;
            }
    return res;
}
struct hash_func {  
    size_t operator() (const Matrix &p) const {  
        uint res = 0;
        for (int i = 0 ; i < p.n ; ++ i)
            for (int j = 0 ; j < p.m ; ++ j) {
                res *= 1000003;
                res += p[i][j];
            }
        return res;
    }  
};
uint get() {
    uint m = sqrt(n) + 5;
    unordered_map<Matrix , uint , hash_func> Hash;
    Matrix P(2 , 2) , S(2 , 2) , W(2 , 2) , I(2 , 2);
    P[0][1] = n - 1 , P[1][0] = 1 , P[1][1] = 10 % n;
    I[0][0] = 10 % n , I[0][1] = 1 , I[1][0] = n - 1;    
    S[0][0] = S[1][1] = S[2][2] = 1;
    W = S;
    for (uint i = 0 ; i < m ; ++ i) {
        if (i && S.isI())
            return i;
        if (!Hash.count(S))
            Hash[S] = i;
        S = S * P;
        W = W * I;        
    }
    I = Matrix(2 , 2);
    I[0][0] = I[1][1] = 1;
    for (uint i = 1 ;  ; ++ i) {
        I = I * W;
        if (Hash.count(I))
            return i * m + Hash[I];
    }
}
uint cal(int x) {
    Matrix P(2 , 2) , S(1 , 2);
    P[0][1] = n - 1 , P[1][0] = 1 , P[1][1] = 10 % n;    
    S[0][0] = 2 % n , S[0][1] = 10 % n;
    while (x) {
        if (x & 1)
            S = S * P;
        P = P * P , x >>= 1;
    }
    return S[0][0];
}

void work() {
    uint X;
    scanf("%u%u" , &X , &n);
    uint m = get();
    uint x = m , phi = m;
    for (uint i = 2 ; i * i <= x ; ++ i) {
        if (x % i == 0) {
            phi /= i , phi *= i - 1;
            while (x % i == 0)
                x /= i;
        }
    }
    if (x > 1)
        phi /= x , phi *= x - 1;
    uint res;
    if (0) {
        uint e = 1;
        while (X --)
            e <<= 1;
        ++ e;
        res = cal(e);
    } else {
        if (X >= phi)
            X = X % phi + phi;        
        uint e = 1;
        while (X --) {
            e <<= 1;
            e %= m;
        }
        ++ e , e %= m;
        res = cal(e);
    }
    res += n - 1 , res %= n;
    printf("Case #%u: %u\n" , ++ ca , res);
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();    
    return 0;
}
