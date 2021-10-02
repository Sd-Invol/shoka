
p[n] = p[0];
std::vector<Point> events = {Point(1, 0)};
std::vector<std::pair<Point, int>> wtf;
for (int i = 0; i < n; ++i) {
  Point v = p[i + 1] - p[i];
  int64 g = std::abs(std::gcd(v.x, v.y));
  v.x /= g;
  v.y /= g;
  for (int k = 0; k < 4; ++k) {
    events.emplace_back(v);
    wtf.emplace_back(std::make_pair(v, i * 4 + k));
    std::swap(v.x, v.y);
    v.x = -v.x;
  }
}
std::sort(events.begin(), events.end());
std::sort(wtf.begin(), wtf.end());
events.erase(std::unique(events.begin(), events.end()), events.end());
int m = events.size();

int dmax = 0, dmin = 0, cmax = 0, cmin = 0;
for (auto it : wtf) {
  int o = it.second % 4;
  int k = it.second >> 2;
  if (o == 0) {
    cmin = (k + 1) % n;
  } else if (o == 2) {
    cmax = (k + 1) % n;
  } else if (o == 1) {
    dmin = (k + 1) % n;
  } else if (o == 3) {
    dmax = (k + 1) % n;
  }
}
double res = 0;
for (int j = 0, l = 0; j < m; ++j) {
  while (l < wtf.size() && (j + 1 == m || wtf[l].first < events[j + 1])) {
    int o = wtf[l].second % 4;
    int k = wtf[l].second >> 2;
    if (o == 0) {
      cmin = (cmin + 1) % n;
    } else if (o == 2) {
      cmax = (cmax + 1) % n;
    } else if (o == 1) {
      dmin = (dmin + 1) % n;
    } else if (o == 3) {
      dmax = (dmax + 1) % n;
    }
    l++;
  }
  Point d = p[dmax] - p[dmin];
  Point c = p[cmax] - p[cmin];
  double L = events[j].angle();  // note atan2 return [-pi, pi)
  double R = j + 1 == m ? 2 * pi : events[j + 1].angle();
  res += cal(R, d.x, d.y, c.y, -c.x);
  res -= cal(L, d.x, d.y, c.y, -c.x);
}
