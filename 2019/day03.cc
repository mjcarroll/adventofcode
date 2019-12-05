#include "aoc_solution.hh"

#include "point.hh"

SOLUTION(2019, 3, "399", "15678");

auto
extract_coords(const std::vector<std::string>& wire)
{
  std::vector<Point> coords;
  Point current = {0, 0};
  coords.push_back(current);

  for (auto cmd: wire)
  {
    auto val = atoi(cmd.substr(1).c_str());
    auto step = Point(0,0);
    switch(cmd[0]) {
      case 'U':
        step.y = 1;
        break;
      case 'D':
        step.y = -1;
        break;
      case 'R':
        step.x = 1;
        break;
      case 'L':
        step.x = -1;
        break;
    }

    auto endpt = current + val * step;

    while (current != endpt)
    {
      current += step;
      coords.push_back(current);
    }
  }
  return coords;
}

int solve_part1(const std::string& input1, const std::string& input2)
{
  auto line1 = split_string(input1, ',');
  auto line2 = split_string(input2, ',');

  auto coords1 = extract_coords(line1);
  auto coords2 = extract_coords(line2);

  std::set<Point> unique1(coords1.begin(), coords1.end());
  std::set<Point> unique2(coords2.begin(), coords2.end());

  std::vector<Point> output;
  std::vector<int> output_man;
  for (auto pt: unique1)
  {
    if(pt.x == 0 && pt.y == 0)
      continue;

    if(unique2.count(pt))
    {
      output.push_back(pt);
      output_man.push_back(abs(pt.x) + abs(pt.y));
    }
  }

  int min = 1e6;
  for(size_t ii = 0; ii < output.size(); ++ii)
  {
    if (output_man[ii] < min)
    {
      min = output_man[ii];
    }
  }

  return min;
}

int solve_part2(const std::string& input1, const std::string& input2)
{
  auto line1 = split_string(input1, ',');
  auto line2 = split_string(input2, ',');

  auto coords1 = extract_coords(line1);
  auto coords2 = extract_coords(line2);

  std::set<Point> unique1(coords1.begin(), coords1.end());
  std::set<Point> unique2(coords2.begin(), coords2.end());

  std::vector<Point> output;
  std::vector<int> output_man;
  for (auto pt: unique1)
  {
    if(pt.x == 0 && pt.y == 0)
      continue;

    if(unique2.count(pt))
    {
      output.push_back(pt);
      output_man.push_back(abs(pt.x) + abs(pt.y));
    }
  }

  int min = 1e6;
  for(size_t ii = 0; ii < output.size(); ++ii)
  {
    auto it1 = std::find(coords1.begin(), coords1.end(), output[ii]);
    auto it2 = std::find(coords2.begin(), coords2.end(), output[ii]);

    auto dist1 = it1 - coords1.begin();
    auto dist2 = it2 - coords2.begin();

    if (dist1 + dist2 < min)
      min = dist1 + dist2;
  }

  return min;
}

void AocSolution::test_part1() {
  assert(solve_part1("R8,U5,L5,D3", "U7,R6,D4,L4") == 6);
  assert(solve_part1("R75,D30,R83,U83,L12,D49,R71,U7,L72",
                     "U62,R66,U55,R34,D71,R55,D58,R83") == 159);
  assert(solve_part1("R98,U47,R26,D63,R33,U87,L62,D20,R33,U53,R51",
                     "U98,R91,D20,R16,D67,R40,U7,R15,U6,R7") == 135);
}

std::string AocSolution::part1()
{
  auto lines = split_lines(kInput);
  return std::to_string(solve_part1(lines[0], lines[1]));
}

void AocSolution::test_part2() {
  assert(solve_part2("R8,U5,L5,D3", "U7,R6,D4,L4") == 30);
  assert(solve_part2("R75,D30,R83,U83,L12,D49,R71,U7,L72",
                     "U62,R66,U55,R34,D71,R55,D58,R83") == 610);
  assert(solve_part2("R98,U47,R26,D63,R33,U87,L62,D20,R33,U53,R51",
                     "U98,R91,D20,R16,D67,R40,U7,R15,U6,R7") == 410);
}

std::string AocSolution::part2()
{
  auto lines = split_lines(kInput);
  return std::to_string(solve_part2(lines[0], lines[1]));
}
