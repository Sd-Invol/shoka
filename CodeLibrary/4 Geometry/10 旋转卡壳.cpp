p[n] = p[0];
std::vector<Point> events = {Point(1, 0)};
for (int i = 0; i < n; ++i) {
  Point v = p[i + 1] - p[i];
  int g = std::abs(std::gcd(v.x, v.y));
  v.x /= g;
  v.y /= g;
  for (int k = 0; k < 4; ++k) {
    events.emplace_back(v);
    w[k][i] = v;
    std::swap(v.x, v.y);
    v.x = -v.x;
  }
}
std::sort(events.begin(), events.end());
events.erase(std::unique(events.begin(), events.end()), events.end());
int pivot[4], cur[4];
for (int i = 0; i < 4; ++i) {
  pivot[i] = std::min_element(w[i], w[i] + n) - w[i];
  std::rotate(w[i], w[i] + pivot[i], w[i] + n);
  cur[i] = 0;
}
double res = 0;
int m = events.size();
for (int j = 0, l = 0; j < m; ++j) {
  for (int i = 0; i < 4; ++i) {
    while (cur[i] < n && (j + 1 == m || w[i][cur[i]] < events[j + 1])) {
      pivot[i] = (pivot[i] + 1) % n;
      ++cur[i];
    }
  }
  Point d = p[pivot[3]] - p[pivot[1]];
  Point c = p[pivot[2]] - p[pivot[0]];
  double L = events[j].angle();
  double R = j + 1 == m ? 2 * pi : events[j + 1].angle();
  res += cal(R, d.x, d.y, c.y, -c.x);
  res -= cal(L, d.x, d.y, c.y, -c.x);
}
