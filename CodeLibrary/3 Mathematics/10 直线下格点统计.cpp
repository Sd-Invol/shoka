// $\sum_{i=0}^{n-1} \lfloor \frac{a+bi}{m}\rfloor$, $n,a,b>=0,m>0$
int64 solve(int64 n, int64 a, int64 b, int64 m) {
  if (b == 0)
    return n * (a / m);
  if (a >= m)
    return n * (a / m) + solve(n, a % m, b, m);
  if (b >= m)
    return (n - 1) * n / 2 * (b / m) + solve(n, a, b % m, m);
  return solve((a + b * n) / m, (a + b * n) % m, m, b);
}
