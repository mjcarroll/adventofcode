#include "aoc_solution.hh"

#include "spdlog/spdlog.h"

SOLUTION(2019, 10, "263", "1110");

std::string test_input = R"(.#..#
.....
#####
....#
...##)";

std::string test_input2 = R"(......#.#.
#..#.#....
..#######.
.#.#.###..
.#..#.....
..#....#.#
#..#....#.
.##.#..###
##...#..#.
.#....####)";

std::string test_input3 = R"(#.#...#.#.
.###....#.
.#....#...
##.#.#.#.#
....#.#.#.
.##..###.#
..#...##..
..##....##
......#...
.####.###.)";

std::string test_input_large = R"(.#..##.###...#######
##.############..##.
.#.######.########.#
.###.#######.####.#.
#####.##.#.##.###.##
..#####..#.#########
####################
#.####....###.#.#.##
##.#################
#####.##.###..####..
..######..##.#######
####.##.####...##..#
.#####..#.######.###
##...#.##########...
#.##########.#######
.####.#.###.###.#.##
....##.##.###..#####
.#.#.###########.###
#.#.#.#####.####.###
###.##.####.##.#..##)";

struct Line {
  Line(int x1, int x2, int y1, int y2):
    x1(x1), x2(x2), y1(y1), y2(y2)
  {
    range = sqrt((x2 - x1) * (x2 - x1) +
                 (y2 - y1) * (y2 - y1));
    bearing = atan2(y2 - y1, x2 - x1) * 180.0/M_PI - 270.0;

    bearing = fmod(bearing, 360);
    if (bearing < 0)
      bearing += 360;
  }

  bool operator<(const Line& other) const {
    return this->bearing < other.bearing;
  }

  int x1;
  int x2;
  int y1;
  int y2;
  float range;
  float bearing;
};

struct Line2: public Line
{
  using Line::Line;

  bool operator<(const Line2& other) const {
    if (this->bearing == other.bearing)
    {
      return this->range < other.range;
    }
    else
    {
      return this->bearing < other.bearing;
    }
  }
};

template <typename LineType>
auto compute_vis(const std::vector<std::string>& grid,
                 int y1, int x1)
{
  std::set<LineType> vis;
  for(int y2 = 0; y2 < grid.size(); ++y2)
  {
    for(int x2 = 0; x2 < grid[y2].size(); ++x2)
    {
      if (x2 == x1 && y2 == y1)
      {
        continue;
      }
      if (grid[y2][x2] == '#')
      {
        vis.insert(LineType{x1, x2, y1, y2});
      }
    }
  }

  return vis;
}

auto solve(const std::string& raw_input)
{
  auto input = split_lines(raw_input);
  int max = 0;
  std::pair<int, int> ret;

  for(size_t yy = 0; yy < input.size(); ++yy)
  {
    for (size_t xx = 0; xx < input[yy].size(); ++xx)
    {
      if(input[yy][xx] == '#')
      {
        auto vals2 = compute_vis<Line>(input, yy, xx);

        if(vals2.size() > max)
        {
          max = vals2.size();
          ret = {yy, xx};
        }

        std::string str = fmt::format("{} ({},{}): ", vals2.size(), yy, xx);
        for (auto val: vals2)
        {
          str += fmt::format("({},{} => {}) ", val.y2, val.x2, val.bearing);
        }
        spdlog::debug(str);
      }
    }
  }

  return std::make_tuple(max, ret.first, ret.second);
}

void AocSolution::test_part1()
{
  /*
  {
    auto [max, yy, xx] = solve(test_input);
    assert(max == 8);
    assert(xx == 3);
    assert(yy == 4);
  }
  {
    auto [max, yy, xx] = solve(test_input2);
    assert(max == 33);
    assert(xx == 5);
    assert(yy == 8);
  }
  {
    auto [max, yy, xx] = solve(test_input3);
    assert(max == 35);
    assert(xx == 1);
    assert(yy == 2);
  }
  {
    auto [max, yy, xx] = solve(test_input_large);
    assert(max == 210);
    assert(xx == 11);
    assert(yy == 13);
  }
  */
}

std::string AocSolution::part1()
{
  auto [max, yy, xx] = solve(kInput);
  spdlog::debug("{} {}", xx, yy);
  return std::to_string(max);
}

void AocSolution::test_part2()
{
  std::string more_input = R"(.#....#####...#..
##...##.#####..##
##...#...#.#####.
..#.....#...###..
..#.#.....#....##)";

  auto input = split_lines(test_input_large);
  auto vals = compute_vis<Line2>(input, 13, 11);

  int xx, yy;
  size_t ii = 1;
  while (!vals.empty())
  {
    std::set<Line2> to_del;
    float cur = -1;
    for (auto val: vals)
    {
      if(val.bearing > cur)
      {
        spdlog::debug("{} ({},{} => {:3.2f}) ", ii, val.y2, val.x2, val.bearing);
        to_del.insert(val);
        cur = val.bearing;

        if (ii++ == 200)
        {
          xx = val.x2;
          yy = val.y2;
          break;
        }
      }
    }
    for (auto val: to_del)
    {
      vals.erase(val);
    }
  }
  spdlog::debug("{} {} => {}", xx, yy, 100 * xx + yy);
}

std::string AocSolution::part2()
{
  auto input = split_lines(kInput);
  auto vals = compute_vis<Line2>(input, 29, 23);

  int xx, yy;
  size_t ii = 1;
  while (!vals.empty())
  {
    std::set<Line2> to_del;
    float cur = -1;
    for (auto val: vals)
    {
      if(val.bearing > cur)
      {
        spdlog::debug("{} ({},{} => {:3.2f}) ", ii, val.y2, val.x2, val.bearing);
        to_del.insert(val);
        cur = val.bearing;

        if (ii == 200)
        {
          xx = val.x2;
          yy = val.y2;
        }
        ii++;
      }
    }
    for (auto val: to_del)
    {
      vals.erase(val);
    }
  }
  return std::to_string(xx * 100 + yy);
}
