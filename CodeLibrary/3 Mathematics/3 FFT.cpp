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
void NTT(int P[], int n, int oper) {
    for (int i = 1, j = 0; i < n - 1; i++) {
        for (int s = n; j ^= s >>= 1, ~j & s;);
        if (i < j) {
            swap(P[i], P[j]);
        }
    }//998244353 1004535809
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
void FFT(int P[] , int n , int oper) {
    if (n == 1) return;
    int m = 0;
    for (int i = 0 ; i < n ; i += 3) tmp[m ++] = P[i];
    for (int i = 1 ; i < n ; i += 3) tmp[m ++] = P[i];
    for (int i = 2 ; i < n ; i += 3) tmp[m ++] = P[i];
    memcpy(P , tmp , n << 2) , m = n / 3;
    FFT(P , m , oper);
    FFT(P + m , m , oper);
    FFT(P + m + m , m , oper);
    int unit_p0 = hash[oper * n];
    int unit = 1;
    for (int i = 0 , j = 0 ; i < n ; ++ i) {
        tmp[i] = P[j] + (LL)unit * (P[m + j] + (LL)unit * P[m + m + j] % Q) % Q;
        tmp[i] %= Q;
        unit = (LL)unit * unit_p0 % Q;
        if (++ j == m)
            j = 0;
    }
    memcpy(P , tmp , n << 2);
}
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
