#include "aoc_solution.hh"

#include "spdlog/spdlog.h"

SOLUTION(2015, 17, "654", "57");

int compute(const std::vector<int>& containers, int volume,
            std::vector<int>& cur_solution,
            std::vector<std::vector<int>>& solutions)
{
  if (containers.size() == 0)
    return 0;

  std::vector<int> remain = {containers.begin() + 1, containers.end()};

  if (containers[0] > volume)
  {
    // Skip
  }
  else if(containers[0] == volume)
  {
    // If the container matches remaining volume, we are done
    auto sol = std::vector<int>{cur_solution.begin(), cur_solution.end()};
    sol.push_back(containers[0]);
    solutions.push_back(sol);
  }
  else
  {
    // Compute solutoins with the first container included
    auto sol = std::vector<int>{cur_solution.begin(), cur_solution.end()};
    sol.push_back(containers[0]);
    compute(remain, volume - containers[0], sol, solutions);
  }

  // Compute solutions with the first container excluded
  auto sol = std::vector<int>{cur_solution.begin(), cur_solution.end()};
  return compute(remain, volume, cur_solution, solutions);
}

void AocSolution::test_part1()
{
  auto containers = std::vector<int>{20, 15, 10, 5, 5};
  std::vector<int> cur_solution;
  std::vector<std::vector<int>> solutions;
  compute(containers, 25, cur_solution, solutions);

  for (auto sol: solutions)
  {
    auto str = std::string("");
    str += fmt::format("{}: ", sol.size());
    for (auto container: sol)
    {
      str += fmt::format("{} ", container);
    }
    spdlog::debug(str);
  }

  assert(solutions.size() == 4);
}

std::string AocSolution::part1()
{
  auto lines = split_lines(kInput);
  auto containers = map(lines, toInt);

  std::vector<int> cur_solution;
  std::vector<std::vector<int>> solutions;
  compute(containers, 150, cur_solution, solutions);

  return std::to_string(solutions.size());
}

void AocSolution::test_part2()
{
}

std::string AocSolution::part2()
{
  auto lines = split_lines(kInput);
  auto containers = map(lines, toInt);

  std::vector<int> cur_solution;
  std::vector<std::vector<int>> solutions;
  compute(containers, 150, cur_solution, solutions);

  auto sizes = map(solutions, [](auto sol) { return sol.size(); });
  auto min = *std::min_element(sizes.begin(), sizes.end());

  auto sum = std::count_if(sizes.begin(), sizes.end(), [min](auto val){ return val == min; });
  return std::to_string(sum);
}
