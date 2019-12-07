#include "aoc_solution.hh"
#include "aoc_common.hh"
#include "aoc_config.hh"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/fmt.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <iostream>
#include <chrono>

auto compute_path(int year, int day)
{
  std::string inp{AOC_PROJECT_DIR};
  auto dayStr = std::to_string(day);

  if (day < 10) {
    dayStr = std::string(1, '0').append(dayStr);
  }

  inp += "/" +
    std::to_string(year) +
    "/input/" +
    dayStr +
    ".txt";
  return inp;
}

BaseSolution::BaseSolution(
  int year, int day, const std::string & part1,
  const std::string & part2)
: year(year),
  day(day),
  kInputPath(compute_path(year, day)),
  kInput(read_string(kInputPath)),
  part1_answer(part1),
  part2_answer(part2)
{
}


int main(int argc, char ** argv)
{
  std::vector<std::string> args;
  for (size_t ii = 0; ii < argc; ++ii)
  {
    args.push_back(std::string(argv[ii]));
  }

  auto find_arg = [&](auto arg){
    return std::find(args.begin(), args.end(), arg) != args.end();
  };

  if (find_arg("-d"))
  {
    spdlog::set_level(spdlog::level::debug);
  }

  spdlog::set_pattern("%v");
  auto solution = AocSolution();
  spdlog::info("{}/{:02}", solution.year, solution.day);

  solution.test_part1();

  auto p1start = std::chrono::steady_clock::now();
  auto part1 = solution.part1();
  auto p1end = std::chrono::steady_clock::now();

  solution.test_part2();

  auto p2start = std::chrono::steady_clock::now();
  auto part2 = solution.part2();
  auto p2end = std::chrono::steady_clock::now();

  auto part1_right = true;
  auto part2_right = true;

  auto check = "\U00002714";
  auto cross = "\U0000274E";

  std::string val = "";
  std::string sol = "";

  auto delta1 = std::chrono::duration_cast<std::chrono::microseconds>(p1end-p1start).count();
  if (solution.part1_answer != "") {
    val = part1 == solution.part1_answer ? check : cross;
    sol = fmt::format("{} == {}", part1, solution.part1_answer);
  } else {
    sol = part1;
    val = "?";
  }
  spdlog::info("Part1: {:<30}{:>10}{:>10} micros", sol,val,delta1);

  auto delta2 = std::chrono::duration_cast<std::chrono::microseconds>(p2end-p2start).count();
  if (solution.part2_answer != "") {
    val = part2 == solution.part2_answer ? check : cross;
    sol = fmt::format("{} == {}", part2, solution.part2_answer);
  } else {
    sol = part2;
    val = "?";
  }
  spdlog::info("Part2: {:<30}{:>10}{:>10} micros", sol,val,delta2);


  if (part1_right && part1_right)
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;

}
