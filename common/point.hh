#ifndef POINT_HH_
#define POINT_HH_

struct Point {
  int x;
  int y;

  Point(int x, int y): x(x), y(y) {}

  bool operator<(const Point& other) const {
    return (10000 * x + y) < (10000 * other.x + other.y);
  }

  bool operator==(const Point& other) const {
    return (x == other.x) && (y == other.y);
  }

  bool operator!=(const Point& other) const {
    return !(*this == other);
  }

  Point& operator+=(const Point& other) {
    x += other.x;
    y += other.y;
    return *this;
  }
};

Point operator+(const Point& a, const Point& b)
{
  auto out = a;
  out.x += b.x;
  out.y += b.y;
  return out;
}

Point operator*(const int& a, const Point& pt)
{
  auto out = pt;
  out.x *= a;
  out.y *= a;
  return out;
}

#endif // POINT_HH_
