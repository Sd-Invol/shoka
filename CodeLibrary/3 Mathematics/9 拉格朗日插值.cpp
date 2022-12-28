// a : F(0), F(1) .. F(n - 1) mod P^e => F(u) mod P^e
int64 Lagrange(const std::vector<int64>& a, int64 u, int P, int e = 1) {
  // mod P^e // O(n(e + log))
  typedef std::pair<int64, int> Pint;  // first * P ^ second
  if (u < a.size()) {
    return a[u];
  }
  int64 Pe = 1, n = a.size();
  for (int i = 0; i < e; ++i) {
    Pe *= P;
  }
  std::function<void(Pint&, int64)> multi = [&](Pint& A, int64 x) {
    while (x && x % P == 0) {
      x /= P;
      ++A.second;
    }
    A.first = A.first * x % Pe;
  };
  Pint numerator = {1, 0};
  for (int i = 0; i < n; ++i) {
    multi(numerator, u - i);
  }
  std::vector<Pint> fac(n);
  fac[0] = {1, 0};
  for (int i = 1; i < n; ++i) {
    fac[i] = fac[i - 1];
    multi(fac[i], i);
  }
  int64 res = 0;
  for (int i = 0; i < n; ++i) {
    Pint denominator = fac[i];
    denominator.second += fac[n - i - 1].second;
    denominator.first = denominator.first * fac[n - i - 1].first % Pe;
    multi(denominator, u - i);
    if (numerator.second - denominator.second < e) {
      int64 delta =
          numerator.first * power(denominator.first, Pe / P - 1, Pe) % Pe;
      delta = delta * power(P, numerator.second - denominator.second, Pe) % Pe;
      if ((n - i - 1) & 1) {
        delta = Pe - delta;
      }
      res = (res + delta * a[i] % Pe) % Pe;
    }
  }
  return res;
}
/******************************************/
// 特殊的，一个K阶多项式已知前K+1项求第n项 O(Klogn)
// 例: 求前n个自然数的K次方和，多项式是K+1阶
int Lagrange(const std::vector<int>& f, int k) {
  int n = (int)f.size() - 1;
  if (k <= n) {
    return f[k];
  }
  int cur = 1;
  for (int i = 1 ; i <= n ; ++ i) {
    cur = 1LL * cur * (k - i) % Q * inverse(Q - i) % Q;
  }
  int res = 1LL * cur * f[0] % Q;
  for (int i = 0 ; i < n ; ++ i) {
    cur = 1LL * cur * (Q + i - n) % Q * inverse(i + 1) % Q;
    cur = 1LL * cur * (k - i) % Q * inverse(k - i - 1) % Q;
    res = (res + 1LL * cur * f[i + 1]) % Q;
  }
  return res;
}
// \sum_{i=1}^{n} i^K
int sumOfPower(int n, int K) { 
  std::vector<int> f(K + 2);
  for (int i = 1; i <= K + 1; ++i) {
    f[i] = (f[i - 1] + power(i, K)) % Q;
  }
  return Lagrange(f, n);
}
