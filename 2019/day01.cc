#include "aoc_solution.hh"

SOLUTION(2019, 1, "3334297", "4998565");

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

void AocSolution::test_part1()
{
  assert(calc_fuel(12) == 2);
  assert(calc_fuel(14) == 2);
  assert(calc_fuel(1969) == 654);
  assert(calc_fuel(100756) == 33583);
}

std::string AocSolution::part1()
{
  auto masses = map(split_lines(kInput), toInt);
  auto fuels = map(masses, calc_fuel);
  return std::to_string(sum(fuels));
}

void AocSolution::test_part2()
{
  assert(rec_calc_fuel(14) == 2);
  assert(rec_calc_fuel(1969) == 966);
  assert(rec_calc_fuel(100756) == 50346);
}

std::string AocSolution::part2()
{
  auto masses = map(split_lines(kInput), toInt);
  auto fuels = map(masses, rec_calc_fuel);
  return std::to_string(sum(fuels));
}
