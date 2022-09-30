/** Normal complex FFT **/
const double pi = std::acos(-1.0);
struct Complex {
  double x, y;
  Complex() {
    x = y = 0;
  }
  Complex(double _x, double _y) {
    x = _x, y = _y;
  }
  Complex operator+(const Complex &r) const {
    return Complex(x + r.x, y + r.y);
  }
  Complex operator-(const Complex &r) const {
    return Complex(x - r.x, y - r.y);
  }
  Complex operator*(const Complex &r) const {
    return Complex(x * r.x - y * r.y, x * r.y + y * r.x);
  }
  int operator=(const int a) {
    *this = Complex(a, 0);
    return a;
  }
};

void FFT(Complex P[], int n, int oper) {
  for (int i = 1, j = 0; i < n - 1; i++) {
    for (int s = n; j ^= s >>= 1, ~j & s;)
      ;
    if (i < j) {
      std::swap(P[i], P[j]);
    }
  }
  for (int d = 0; (1 << d) < n; d++) {
    int m = 1 << d, m2 = m * 2;
    double p0 = pi / m * oper;
    Complex unit_p0(std::cos(p0), std::sin(p0));
    for (int i = 0; i < n; i += m2) {
      Complex unit(1, 0);
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

/**  FFT mod 1e9 + 7, three mods with CRT by NTT */
constexpr int power(int A, int B, int QQ = Q) {
  int res = 1;
  while (B) {
    if (B & 1) {
      res = 1LL * res * A % QQ;
    }
    A = 1LL * A * A % QQ;
    B >>= 1;
  }
  return res;
}
inline int add(int A, int B, int mod) {
  return A + B >= mod ? A + B - mod : A + B;
}
template <int mod, int root>
void FFT(int P[], int n, int oper) {
  for (int i = 0; i < n; i++) {
    if (i < rev[i]) {
      std::swap(P[i], P[rev[i]]);
    }
  }
  for (int d = 0; (1 << d) < n; d++) {
    int m = 1 << d, m2 = m << 1;
    int unit_p0 = power(root, (mod - 1) >> (d + 1), mod);
    if (oper == -1) {
      unit_p0 = power(unit_p0, mod - 2, mod);
    }
    for (int i = 0; i < n; i += m2) {
      int unit = 1, *a = P + i + m, *b = P + i;
      for (int j = 0; j < m; j++) {
        int t = 1LL * unit * *a % mod;
        *a = add(*b, mod - t, mod);
        *b = add(*b, t, mod);
        unit = 1LL * unit * unit_p0 % mod;
        ++a, ++b;
      }
    }
  }
}

int _a[N], _b[N];
template <int mod, int root = 3>
void convolution(int *a, int *b, int len, int *res) {
  for (int i = 0; i < len; ++i) {
    _a[i] = a[i] % mod;
    _b[i] = b[i] % mod;
  }
  FFT<mod, root>(_a, len, 1);
  FFT<mod, root>(_b, len, 1);
  int inv = power(len, mod - 2, mod);
  for (int i = 0; i < len; ++i) {
    res[i] = 1LL * _a[i] * _b[i] % mod * inv % mod;
  }
  FFT<mod, root>(res, len, -1);
}

const int M1 = 167772161;
const int M2 = 469762049;
const int M3 = 754974721;
const int64 pq = 1LL * M3 * M2;
const int i0 = power(M3 % M2, M2 - 2, M2);
const int i1 = power(pq % M1, M1 - 2, M1);
const int u0 = pq % Q;

int _c0[N], _c1[N], _c2[N];
void convolution(int *a, int *b, int len, int *res) {
  int LN = __builtin_ctz(len);
  for (int i = 0; i < len; ++i) {
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (LN - 1));
  }
  convolution<M1>(a, b, len, _c0);
  convolution<M2>(a, b, len, _c1);
  convolution<M3, 11>(a, b, len, _c2);
  for (int i = 0; i < len; ++i) {
    int q0 = 1LL * (_c1[i] - _c2[i] % M2 + M2) * i0 % M2;
    int64 y = 1LL * M3 * q0 + _c2[i];
    int q1 = 1LL * (_c0[i] - y % M1 + M1) * i1 % M1;
    // int128 z = 1LL * pq * q1 + y;
    res[i] = (1LL * u0 * q1 % Q + y) % Q;
  }
}

/** x = A * 2^15 + B */
Complex w[N];
int rev[N];
int len;
void FFTperpare(int n) {
  int LN = __builtin_ctz(n);
  for (int i = 0; i < n; ++i) {
    double ang = 2 * pi * i / n;
    w[i] = Complex(cos(ang), sin(ang));
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (LN - 1));
  }
}
void FFT(Complex P[], int n, int oper) {
  for (int i = 0; i < n; i++) {
    if (i < rev[i]) {
      swap(P[i], P[rev[i]]);
    }
  }
  for (int d = 0; (1 << d) < n; d++) {
    int m = 1 << d, m2 = m * 2, rm = n / m2;
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
Complex A[N], B[N], C1[N], C2[N];
void convolution(int *a, int *b, int *res) {
  for (int i = 0; i < len; ++i) {
    A[i] = Complex(a[i] / M, a[i] % M);
    B[i] = Complex(b[i] / M, b[i] % M);
  }
  FFT(A, len, 1);
  FFT(B, len, 1);
  for (int i = 0; i < len; ++i) {
    int j = i ? len - i : i;
    Complex a1 = (A[i] + A[j].conj()) * Complex(0.5, 0);
    Complex a2 = (A[i] - A[j].conj()) * Complex(0, -0.5);
    Complex b1 = (B[i] + B[j].conj()) * Complex(0.5, 0);
    Complex b2 = (B[i] - B[j].conj()) * Complex(0, -0.5);
    Complex c11 = a1 * b1, c12 = a1 * b2;
    Complex c21 = a2 * b1, c22 = a2 * b2;
    C1[j] = c11 + c12 * Complex(0, 1);
    C2[j] = c21 + c22 * Complex(0, 1);
  }
  FFT(C1, len, -1);
  FFT(C2, len, -1);
  for (int i = 0; i < len; ++i) {
    int x = (LL)(C1[i].x / len + 0.5) % Q;
    int y1 = (LL)(C1[i].y / len + 0.5) % Q;
    int y2 = (LL)(C2[i].x / len + 0.5) % Q;
    int z = (LL)(C2[i].y / len + 0.5) % Q;
    res[i] = ((LL)x * M * M + (LL)(y1 + y2) * M + z) % Q;
  }
}

/** FWT **/
void FWT(int a[], int len) {
  for (int k = 0; 1 << k < len; ++k) {
    for (int i = 0; i < len; ++i) {
      if (~i >> k & 1) {
        int j = i ^ (1 << k);
        int x = (a[i] + a[j]) % Q;
        int y = (a[i] + Q - a[j]) % Q;
        a[i] = x;
        a[j] = y;
      }
    }
  }
}
