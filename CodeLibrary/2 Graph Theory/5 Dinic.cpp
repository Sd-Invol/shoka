template <typename F, int maxN = 1 << 18, int maxM = 1 << 20>
struct Flow {
  int pre[maxN], mcnt, s, t;
  struct arc {
    int x, next;
    F f;
  } e[maxM];
  Flow() {
    memset(pre, -1, sizeof(pre));
    mcnt = 0;
  }
  void addarc(int x, int y, F z, F r = 0) {
    e[mcnt] = {y, pre[x], z}, pre[x] = mcnt++;
    e[mcnt] = {x, pre[y], r}, pre[y] = mcnt++;
  }
  int d[maxN], cur[maxN], q[maxN];
  bool bfs() {
    memset(d, -1, sizeof(d));
    int top = 0, bot = -1;
    q[++bot] = t, d[t] = 1;
    while (top != bot + 1) {
      int x = q[top++];
      for (int i = pre[x]; ~i; i = e[i].next) {
        int y = e[i].x;
        if (!~d[y] && e[i ^ 1].f) {
          d[y] = d[x] + 1, q[++bot] = y;
          if (y == s)
            return 1;
        }
      }
    }
    return 0;
  }
  F dfs(int x, F flow = std::numeric_limits<F>::max()) {
    if (x == t || !flow)
      return flow;
    F sum = 0;
    for (int& i = cur[x]; ~i; i = e[i].next) {
      int y = e[i].x;
      F u;
      if (d[x] == d[y] + 1 && (u = dfs(y, std::min(flow, e[i].f)))) {
        e[i].f -= u, e[i ^ 1].f += u;
        sum += u, flow -= u;
        if (!flow)
          break;
      }
    }
    if (!sum)
      d[x] = -1;
    return sum;
  }
  F dinic() {
    F ans = 0;
    while (bfs()) {
      memcpy(cur, pre, sizeof(cur));
      ans += dfs(s);
    }
    return ans;
  }
};
Flow<int64, 2005> G;
