using uint64 = unsigned long long;
using uint128 = __uint128_t;

uint64 mod_exp(uint64 a, uint64 x, uint64 n) {
  uint64 ret = 1;
  while (x) {
    if (x & 1) {
      ret = (uint128)ret * a % n;
    }
    a = (uint128)a * a % n;
    x >>= 1;
  }
  return ret;
}
bool MillerRabin(uint64 n) {  // O(7log^2n)
  if (n < 2 || n % 2 == 0) {
    return n == 2;
  }
  uint64 d = n - 1, s = 0;
  while (d % 2 == 0) {
    d >>= 1;
    ++s;
  }
  auto check = [&](uint128 a) {
    uint64 x = mod_exp(a, d, n);
    if (x == 1 || x == n - 1) {
      return false;
    }
    for (int i = 1; i < s; ++i) {
      x = (uint128)x * x % n;
      if (x == n - 1) {
        return false;
      }
    }
    return true;
  };
  for (uint64 a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
    if (a % n && check(a % n)) {
      return false;
    }
  }
  return true;
}
uint64 Pollard(uint64 n) {
  if (n % 2 == 0) {
    return 2;
  }
  if (MillerRabin(n)) {
    return n;
  }
  auto f = [n](uint64 x) { return ((uint128)x * x + 1) % n; };
  int i = 0;
  while (true) {
    uint64 x = i++, y = f(x), p = std::gcd(y - x, n);
    while (p == 1) {
      x = f(x);
      y = f(f(y));
      p = std::gcd(y - x + n, n);
    }
    if (p == 0 || p == n) {
      continue;
    }
    return p;
  }
}
std::vector<uint64> factorize(uint64 n) {
  if (n == 1) {
    return {};
  }
  uint64 x = Pollard(n);
  if (x == n) {
    return {x};
  }
  auto A = factorize(x), B = factorize(n / x);
  A.insert(A.end(), B.begin(), B.end());
  return A;
}