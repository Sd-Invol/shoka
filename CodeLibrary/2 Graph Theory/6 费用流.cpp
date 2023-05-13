template <typename F, typename C, int maxN = 1 << 15, int maxM = 1 << 20>
struct CostFlow {
  bool negativeCost;
  int source, sink, pre[maxN], cur[maxN], mcnt;
  C d[maxN], h[maxN];
  bool vis[maxN];
  struct arc {
    int x;
    F f;
    C c;
    int next;
  } e[maxM];
  CostFlow() {
    memset(pre, -1, sizeof(pre));
    mcnt = 0;
    negativeCost = false;
  }
  void addarc(int x, int y, F z, C c) {
    negativeCost |= (c < 0);
    e[mcnt] = (arc){y, z, c, pre[x]}, pre[x] = mcnt++;
    e[mcnt] = (arc){x, 0, -c, pre[y]}, pre[y] = mcnt++;
  }
  bool BellmanFord() {
    std::queue<int> q;
    memset(h, 0x3f, sizeof(h));
    h[sink] = 0;
    vis[sink] = 1;
    q.push(sink);
    bool found = false;
    while (!q.empty()) {
      int x = q.front();
      q.pop();
      vis[x] = false;
      found |= (x == source);
      for (int i = pre[x]; ~i; i = e[i].next) {
        int y = e[i].x;
        C z = e[i ^ 1].c;
        if (e[i ^ 1].f && h[y] > h[x] + z) {
          h[y] = h[x] + z;
          if (!vis[y]) {
            q.push(y);
            vis[y] = true;
          }
        }
      }
    }
    return found;
  }
  bool Dijkstra() {
    std::priority_queue<std::pair<C, int>> pq;
    memset(d, 0x3f, sizeof(d));
    pq.push({-(d[sink] = 0), sink});
    bool found = false;
    std::vector<int> que;
    while (!pq.empty()) {
      auto [w, x] = pq.top();
      pq.pop();
      if (-w > d[x]) {
        continue;
      }
      que.push_back(x);
      found |= (x == source);
      for (int i = pre[x]; ~i; i = e[i].next) {
        int y = e[i].x;
        C z = e[i ^ 1].c + h[x] - h[y];
        if (e[i ^ 1].f && d[x] + z < d[y]) {
          d[y] = d[x] + z;
          pq.push({-d[y], y});
        }
      }
    }
    if (!found) {
      return false;
    }
    for (auto &x : que) {
      h[x] += d[x];
    }
    return true;
  }
  F augment(int x, F flow) {
    if (x == sink) {
      return flow;
    }
    vis[x] = 1;
    F sum = 0;
    for (int &i = cur[x]; ~i; i = e[i].next) {
      int y = e[i].x;
      if (e[i].f && !vis[y] && h[x] == e[i].c + h[y]) {
        F u = augment(y, std::min(flow, e[i].f));
        e[i].f -= u;
        e[i ^ 1].f += u;
        flow -= u;
        sum += u;
        if (!flow) {
          break;
        }
      }
    }
    vis[x] = 0;
    return sum;
  }
  std::pair<F, C> MincostMaxflow(F limit = std::numeric_limits<F>::max()) {
    memset(vis, 0, sizeof(vis));
    negativeCost ? BellmanFord() : Dijkstra();
    F maxflow = 0;
    C ans = 0;
    do {
      memcpy(cur, pre, sizeof(cur));
      F delta = augment(source, limit - maxflow);
      maxflow += delta;
      ans += h[source] * delta;
    } while (maxflow < limit && Dijkstra());
    // Try Dijkstra -> BellmanFord if it is slow
    return {maxflow, ans};
  }
};
