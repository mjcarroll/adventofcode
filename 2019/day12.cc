#include "aoc_solution.hh"
#include "trim.hh"

#include "spdlog/spdlog.h"

SOLUTION(2019, 12, "6735", "326489627728984");

std::string test_input = R"(<x=-1, y=0, z=2>
<x=2, y=-10, z=-7>
<x=4, y=-8, z=8>
<x=3, y=5, z=-1>)";

std::string test_input2 = R"(<x=-8, y=-10, z=0>
<x=5, y=5, z=10>
<x=2, y=-7, z=3>
<x=9, y=-8, z=-3>)";

struct Planet {
  int id;
  int x;
  int y;
  int z;
  int vx {0};
  int vy {0};
  int vz {0};

  bool operator==(const Planet& other) const
  {
    return this->id == other.id;
  }

  int pot() const {
    return abs(x) + abs(y) + abs(z);
  }

  int kin() const {
    return abs(vx) + abs(vy) + abs(vz);
  }

  int total() const {
    return pot() * kin();
  }
};

static int id {0};

Planet parse(const std::string& line)
{
  auto ll = line.substr(1, line.size() - 2);
  auto coords = split_string(ll, ',');
  assert(coords.size() == 3);
  int x, y, z;
  for( auto coord: coords)
  {
    auto vals = split_string(coord, '=');
    trim(vals[0]);

    if (vals[0] == "x")
      x = toInt(vals[1]);
    else if (vals[0] == "y")
      y = toInt(vals[1]);
    else if (vals[0] == "z")
      z = toInt(vals[1]);
    else
      spdlog::error("Unknown coordinate: {}", coord);
  }
  return Planet{id++, x, y, z};
}

auto print_planets(const std::vector<Planet>& planets)
{
  std::string str = "";
  for (auto planet: planets)
  {
    str += fmt::format("pos=<x={:>3} y={:>3} z={:>3}>, vel=<x={:>3} y={:>3} z={:>3}>\n",
        planet.x, planet.y, planet.z, planet.vx, planet.vy, planet.vz);
  }
  return str;
}

void step(std::vector<Planet>& planets)
{
  for (auto& planet1: planets)
  {
    int dx = 0, dy = 0, dz = 0;
    for (auto& planet2: planets)
    {
      if (planet1 == planet2)
        continue;

      if (planet2.x > planet1.x)
        dx++;
      else if (planet2.x < planet1.x)
        dx--;

      if (planet2.y > planet1.y)
        dy++;
      else if (planet2.y < planet1.y)
        dy--;

      if (planet2.z > planet1.z)
        dz++;
      else if (planet2.z < planet1.z)
        dz--;
    }
    planet1.vx += dx;
    planet1.vy += dy;
    planet1.vz += dz;
  }

  for (auto& planet: planets)
  {
    planet.x += planet.vx;
    planet.y += planet.vy;
    planet.z += planet.vz;
  }
}

int run(std::vector<Planet> planets, int tmax, int print_mod=1)
{
  spdlog::debug("After 0 steps:");
  spdlog::debug(print_planets(planets));

  for (size_t t = 1; t <= tmax; ++t)
  {
    step(planets);

    if (t % print_mod == 0)
    {
      spdlog::debug("After {} steps:", t);
      spdlog::debug(print_planets(planets));
    }
  }

  int sum = 0;
  for (auto& planet: planets)
  {
    spdlog::debug("pot: {:>3}; kin: {:>3}; total: {:>3}",
        planet.pot(), planet.kin(), planet.total());
    sum += planet.total();
  }
  spdlog::debug("Total: {}", sum);
  return sum;
}

long find_repeat(std::vector<Planet> planets)
{
  long x_repeat = 0;
  long y_repeat = 0;
  long z_repeat = 0;

  std::set<std::vector<int>> x_seen;
  std::set<std::vector<int>> y_seen;
  std::set<std::vector<int>> z_seen;

  long iter = 0;
  while(!x_repeat || !y_repeat || !z_repeat)
  {
    step(planets);
    std::vector<int> x, y, z;
    for(auto planet: planets)
    {
      x.push_back(planet.x);
      x.push_back(planet.vx);
      y.push_back(planet.y);
      y.push_back(planet.vy);
      z.push_back(planet.z);
      z.push_back(planet.vz);
    }

    if (x_seen.count(x) && !x_repeat)
    {
      x_repeat = iter;
    }
    if (y_seen.count(y) && !y_repeat)
    {
      y_repeat = iter;
    }
    if (z_seen.count(z) && !z_repeat)
    {
      z_repeat = iter;
    }

    x_seen.insert(x);
    y_seen.insert(y);
    z_seen.insert(z);
    iter++;
  }

  long val = std::lcm(std::lcm(x_repeat, y_repeat), z_repeat);
  spdlog::debug("{} {} {} => {}", x_repeat, y_repeat, z_repeat, val);
  return val;
}

void AocSolution::test_part1()
{
  {
    auto input = split_lines(test_input);
    auto planets = map(input, parse);
    auto sum = run(planets, 10, 1);
    assert(sum == 179);
  }

  {
    auto input = split_lines(test_input2);
    auto planets = map(input, parse);
    auto sum = run(planets, 100, 10);
    assert(sum == 1940);
  }
}

std::string AocSolution::part1()
{
  auto input = split_lines(kInput);
  auto planets = map(input, parse);
  auto sum = run(planets, 1000, 100);
  return std::to_string(sum);
}

void AocSolution::test_part2()
{
  {
    auto input = split_lines(test_input);
    auto planets = map(input, parse);
    assert(find_repeat(planets) == 2772);
  }

  {
    auto input = split_lines(test_input2);
    auto planets = map(input, parse);
    assert(find_repeat(planets) == 4686774924);
  }
}

std::string AocSolution::part2()
{
  auto input = split_lines(kInput);
  auto planets = map(input, parse);
  auto repeat = find_repeat(planets);
  return std::to_string(repeat);
}
