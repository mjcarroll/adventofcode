#include "aoc_solution.hh"

#include "json.hpp"

#include <iostream>
using json = nlohmann::json;

SOLUTION(2015, 12, "111754");

int sum_numbers(json input)
{
  int sum = 0;

  for (json::iterator it = input.begin(); it != input.end(); ++it)
  {
    if (it->is_object() || it->is_array())
    {
      sum += sum_numbers(*it);
    }
    else if (it->is_number_integer())
    {
      sum += it->get<int>();
    }
  }

  return sum;
}

void AocSolution::test_part1()
{
  auto input1 = json::parse("[1,2,3]");
  assert(sum_numbers(input1) == 6);

  auto input2 = json::parse(R"({"a":2,"b":4})");
  assert(sum_numbers(input2) == 6);

  auto input3 = json::parse("[[[3]]]");
  assert(sum_numbers(input3) == 3);

  auto input4 = json::parse(R"({"a":{"b":4},"c":-1})");
  assert(sum_numbers(input4) == 3);

  auto input5 = json::parse(R"({"a":[-1,1]})");
  assert(sum_numbers(input5) == 0);

  auto input6 = json::parse(R"([-1,{"a":1}])");
  assert(sum_numbers(input6) == 0);

  auto input7 = json::parse(R"([])");
  assert(sum_numbers(input7) == 0);

  auto input8 = json::parse(R"({})");
  assert(sum_numbers(input8) == 0);
}

std::string AocSolution::part1()
{
  auto input = json::parse(kInput);
  return std::to_string(sum_numbers(input));
}

void AocSolution::test_part2()
{
}

std::string AocSolution::part2()
{
  return "";
}
