template <typename T>
class FenwickTree {
 public:
  int n;
  std::vector<T> a;
  FenwickTree(int n) : n(n) {
    a.resize(n);
  }
  void add(int x, T w) {
    while (x < n) {
      a[x] += w;
      x |= (x + 1);
    }
  }
  T query(int x) {
    T res{};
    x = std::min(x, n - 1);
    while (x >= 0) {
      res += a[x];
      x = (x & (x + 1)) - 1;
    }
    return res;
  }
  std::pair<int, T> kth(T k) {
    int x = -1;
    for (int i = 20; i >= 0; --i) {
      int y = x + (1 << i);
      if (y < n && a[y] < k) {
        k -= a[y];
        x = y;
      }
    }
    return {x + 1, k};
  }
};
struct CHU_2_BIT {
  int n;
  LL B[N], C[N];
  void init(int size) {
    n = size;
    memset(B, 0, n + 1 << 3);
    memset(C, 0, n + 1 << 3);
  }
  CHU_2_BIT() {}
  CHU_2_BIT(int size) {
    init(size);
  }
  inline LL _sum(LL* c, int x) {
    LL res = 0;
    for (; x > 0; x -= x & -x)
      res += c[x];
    return res;
  }
  void add(int l, int r, LL w) {
    for (int i = l; i <= n; i += i & -i)
      B[i] += w, C[i] += w * l;
    ++r;
    for (int i = r; i <= n; i += i & -i)
      B[i] -= w, C[i] -= w * r;
  }
  LL sum(int l, int r) {
    LL res = 0;
    --l;
    res += (r + 1) * _sum(B, r) - _sum(C, r);
    res -= (l + 1) * _sum(B, l) - _sum(C, l);
    return res;
  }
} T;
