pair<int, int> find() {
  int s = 0, t = 0;
  for (int i = 1; i <= n; ++i) {
    d[i].w = 0;
    d[i].V.clear();
    vis[i] = 0;
  }
  for (int i = 1; i <= n; ++i) {
    int x = -1;
    for (int j = 1; j <= n; ++j)
      if (!f[j] && !vis[j] && (!~x || d[x] < d[j]))
        x = j;
    if (!~x)
      break;
    vis[x] = 1, s = t, t = x;
    for (int j = 1; j <= n; ++j)
      if (!f[j] && !vis[j])
        d[j] += g[x][j];
  }
  res = min(res, d[t]);
  return make_pair(s, t);
}

void global_minimum_cut() {
  memset(f, 0, sizeof(f));
  for (int i = 1; i < n; ++i) {
    pair<int, int> t = find();
    int x = t.first, y = t.second;
    f[y] = 1;
    for (int i = 1; i <= n; ++i) {
      g[x][i] += g[y][i];
      g[i][x] += g[i][y];
    }
  }
}
