/** Normal complex FFT **/
struct Complex {
    double x , y;
    Complex () {x = y = 0;}
    Complex (double _x , double _y) {x = _x , y = _y;}
    Complex operator + (const Complex& r) const {
        return Complex(x + r.x , y + r.y);
    }
    Complex operator - (const Complex& r) const {
        return Complex(x - r.x , y - r.y);
    }
    Complex operator * (const Complex& r) const {
        return Complex(x * r.x - y * r.y , x * r.y + y * r.x);
    }
    int operator = (const int a) {
        *this = Complex(a , 0);
        return a;
    }
};

void FFT(Complex P[], int n, int oper) {
    for (int i = 1, j = 0; i < n - 1; i ++) {
        for (int s = n; j ^= s >>= 1, ~j & s;);
        if (i < j) {
            swap(P[i], P[j]);
        }
    }
    for (int d = 0; (1 << d) < n; d++) {
        int m = 1 << d, m2 = m * 2;
        double p0 = pi / m * oper;
        Complex unit_p0(cos(p0) , sin(p0));
        for (int i = 0; i < n; i += m2) {
            Complex unit(1 , 0);
            for (int j = 0; j < m; j++) {
                Complex &P1 = P[i + j + m], &P2 = P[i + j];
                Complex t = unit * P1;
                P1 = P2 - t;
                P2 = P2 + t;
                unit = unit * unit_p0;
            }
        }
    }
}

/** NTT **/
int inverse(int x) {
    return x == 1 ? 1 : (long long)(Q - Q / x) * inverse(Q % x) % Q;
}
int power(int a , int b) {
    int res = 1;
    while (b) {
        if (b & 1) {
            res = (long long)res * a % Q;
        }
        a = (long long)a * a % Q;
        b >>= 1;
    }
    return res;
}
void FFT(int P[], int n, int oper) {
    for (int i = 1, j = 0; i < n - 1; i++) {
        for (int s = n; j ^= s >>= 1, ~j & s;);
        if (i < j) {
            swap(P[i], P[j]);
        }
    }//998244353 1004535809/ G = 3
    for (int d = 0; (1 << d) < n; d++) {
        int m = 1 << d, m2 = m << 1;
        int unit_p0 = power(G , Q - 1 >> d + 1);
        if (oper == -1)
            unit_p0 = inverse(unit_p0);
        for (int i = 0; i < n; i += m2) {
            int unit = 1;
            for (int j = 0; j < m; j++) {
                int &P1 = P[i + j + m], &P2 = P[i + j];
                int t = (LL)unit * P1 % Q;
                P1 = P2 - t + Q;
                if (P1 >= Q) P1 -= Q;
                P2 = P2 + t;
                if (P2 >= Q) P2 -= Q;
                unit = (LL)unit * unit_p0 % Q;
            }
        }
    }
}

/** Advance FFT mod any number**/
Complex w[N]; int rev[N];
int len;
void FFTperpare(int n) {
    int LN = __builtin_ctz(n);
    for (int i = 0 ; i < n ; ++ i) {
        double ang = 2 * pi * i / n;
        w[i] = Complex(cos(ang) , sin(ang));
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (LN - 1));
    }
}
void FFT(Complex P[], int n, int oper) {
    for (int i = 0 ; i < n ; i ++) {
        if (i < rev[i]) {
            swap(P[i], P[rev[i]]);
        }
    }
    for (int d = 0; (1 << d) < n; d++) {
        int m = 1 << d, m2 = m * 2 , rm = n / m2;
        for (int i = 0; i < n; i += m2) {
            for (int j = 0; j < m; j++) {
                Complex &P1 = P[i + j + m], &P2 = P[i + j];
                Complex t = w[rm * j] * P1;
                P1 = P2 - t;
                P2 = P2 + t;
            }
        }
    }
}
Complex A[N] , B[N] , C1[N] , C2[N];
void convolution(int *a , int *b , int *res) {
    for (int i = 0 ; i < len ; ++ i) {
        A[i] = Complex(a[i] / M , a[i] % M);
        B[i] = Complex(b[i] / M , b[i] % M);
    }
    FFT(A , len , 1);
    FFT(B , len , 1);
    for (int i = 0 ; i < len ; ++ i) {
        int j = i ? len - i : i;
        Complex a1 = (A[i] + A[j].conj()) * Complex(0.5 , 0);
        Complex a2 = (A[i] - A[j].conj()) * Complex(0 , -0.5);
        Complex b1 = (B[i] + B[j].conj()) * Complex(0.5 , 0);
        Complex b2 = (B[i] - B[j].conj()) * Complex(0 , -0.5);
        Complex c11 = a1 * b1 , c12 = a1 * b2;
        Complex c21 = a2 * b1 , c22 = a2 * b2;
        C1[j] = c11 + c12 * Complex(0 , 1);
        C2[j] = c21 + c22 * Complex(0 , 1);
    }
    FFT(C1 , len , -1);
    FFT(C2 , len , -1);
    for (int i = 0 ; i < len ; ++ i) {
        int x = (LL)(C1[i].x / len + 0.5) % Q;
        int y1 = (LL)(C1[i].y / len + 0.5) % Q;
        int y2 = (LL)(C2[i].x / len + 0.5) % Q;
        int z = (LL)(C2[i].y / len + 0.5) % Q;
        res[i] = ((LL)x * M * M + (LL)(y1 + y2) * M + z) % Q;
    }
}

/** FWT **/
void FWT(int a[] , int len , int oper) {
    for (int k = 0 ; 1 << k < len ; ++ k) {
        for (int i = 0 ; i < len ; ++ i) {
            if (~i >> k & 1) {
                int j = i ^ (1 << k);
                int x = (a[i] + Q - a[j]) % Q;
                int y = (a[i] + a[j]) % Q;
                if (oper == -1) {
                    x = (Q - x) % Q;
                    swap(x , y);
                }
                a[i] = x;
                a[j] = y;
            }
        }
    }
}
