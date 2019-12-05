#include "aoc_common.hh"

int calc_fuel(int mass)
{
  return (mass / 3) - 2;
}

int rec_calc_fuel(int mass)
{
  int fuel = calc_fuel(mass);
  if (fuel <= 0)
    return 0;
  else
    return fuel + rec_calc_fuel(fuel);
}

void part1()
{
  assert(calc_fuel(12) == 2);
  assert(calc_fuel(14) == 2);
  assert(calc_fuel(1969) == 654);
  assert(calc_fuel(100756) == 33583);

  auto masses = read_ints(input_path(2019,1));
  std::vector<int> fuels;
  for (auto m: masses)
  {
    fuels.push_back(calc_fuel(m));
  }
  std::cout << "Part1: " << std::accumulate(fuels.begin(), fuels.end(), 0) << std::endl;
}

void part2()
{
  assert(rec_calc_fuel(14) == 2);
  assert(rec_calc_fuel(1969) == 966);
  assert(rec_calc_fuel(100756) == 50346);
  auto masses = read_ints(input_path(2019,1));
  std::vector<int> fuels;
  for (auto m: masses)
  {
    fuels.push_back(rec_calc_fuel(m));
  }
  std::cout << "Part2: " << std::accumulate(fuels.begin(), fuels.end(), 0) << std::endl;
}

int main(int argc, char** argv)
{
  part1();
  part2();
  return 0;
}
