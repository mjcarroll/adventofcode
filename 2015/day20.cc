#include "aoc_solution.hh"

#include "spdlog/spdlog.h"

SOLUTION(2015, 20, "665280", "705600");

void AocSolution::test_part1()
{
}

std::string AocSolution::part1()
{
  auto input = toInt(kInput);

  std::vector<int> houses(input, 0);
  int min = input;

  for(size_t ii = 1; ii < input; ++ii)
  {
    //spdlog::debug("Elf:  {}", ii);
    for(size_t jj = ii; jj < input; jj += ii)
    {
      houses[jj] += 10 * ii;

      if (houses[jj] >= input && jj < min)
      {
        min = jj;
      }
    }
  }

  return std::to_string(min);
}

void AocSolution::test_part2()
{
}

std::string AocSolution::part2()
{
  auto input = toInt(kInput);

  std::vector<int> houses(input, 0);
  int min = input;

  for(size_t ii = 1; ii < input; ++ii)
  {
    int delivered = 0;
    for(size_t jj = ii; jj < input; jj += ii)
    {
      delivered++;
      houses[jj] += 11 * ii;

      if (houses[jj] >= input && jj < min)
      {
        min = jj;
      }

      if (delivered == 50)
        break;
    }
  }

  return std::to_string(min);
}
