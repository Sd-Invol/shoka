int mx[N], my[N];
queue<int> que;
int dx[N], dy[N];
bool vis[N];

bool find(int x) {
  for (int i = pre[x]; ~i; i = e[i].next) {
    int y = e[i].x;
    if (!vis[y] && dy[y] == dx[x] + 1) {
      vis[y] = 1;
      if (!~my[y] || find(my[y])) {
        mx[x] = y, my[y] = x;
        return 1;
      }
    }
  }
  return 0;
}

int matching() {
  memset(mx, -1, sizeof(mx));
  memset(my, -1, sizeof(my));
  int ans = 0;
  while (1) {
    bool flag = 0;
    while (!que.empty())
      que.pop();
    memset(dx, 0, sizeof(dx));
    memset(dy, 0, sizeof(dy));
    for (int i = 0; i < n; ++i)
      if (!~mx[i])
        que.push(i);
    while (!que.empty()) {
      int x = que.front();
      que.pop();
      for (int i = pre[x]; ~i; i = e[i].next) {
        int y = e[i].x;
        if (!dy[y]) {
          dy[y] = dx[x] + 1;
          if (~my[y])
            que.push(my[y]), dx[my[y]] = dy[y] + 1;
          else
            flag = 1;
        }
      }
    }
    if (!flag)
      break;
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < n; ++i)
      if (!~mx[i] && find(i))
        ++ans;
  }
  return ans;
}
