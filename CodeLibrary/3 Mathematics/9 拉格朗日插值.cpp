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
scanf("%d%d", &n, &K);
for (int i = 1; i <= K + 1; ++i) {
  f[i] = (f[i - 1] + power(i, K)) % Q;
}
if (n <= K + 1) {
  printf("%d\n", f[n]);
  return;
}
int A = 1, B = 1;
for (int i = 0; i <= K + 1; ++i)
  A = (LL)A * (n - i) % Q;
for (int i = 1; i <= K + 1; ++i)
  B = (LL)B * (Q - i) % Q;
int res = 0;
for (int i = 0; i <= K + 1; ++i) {
  int C = (LL)A * inverse((LL)(n - i) * B % Q) % Q;
  res += (LL)f[i] * C % Q, res %= Q;
  if (i == K + 1)
    break;
  B = (LL)B * (i + 1) % Q * inverse(Q - (K + 1 - i)) % Q;
}
printf("%d\n", res);
