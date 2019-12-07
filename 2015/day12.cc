#include "aoc_solution.hh"

#include "json.hpp"

#include <iostream>
using json = nlohmann::json;

SOLUTION(2015, 12, "111754", "65402");

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

int sum_numbers2(json input)
{
  int sum = 0;

  if (input.is_object()) {
    for (auto it = input.begin(); it != input.end(); ++it)
    {
      if (it->is_string() && it->get<std::string>() == "red")
      {
        return 0;
      }
    }
  }

  for (json::iterator it = input.begin(); it != input.end(); ++it)
  {
    if (it->is_object())
    {
      bool use = true;
      for (auto it2 = it->begin(); it2 != it->end(); ++it2)
      {
        if (it2->is_string() && it2->get<std::string>() == "red")
        {
          use = false;
        }
      }

      if (use) sum += sum_numbers2(*it);
    }
    else if(it->is_array())
    {
      sum += sum_numbers2(*it);
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
  auto input1 = json::parse("[1,2,3]");
  assert(sum_numbers2(input1) == 6);

  auto input2 = json::parse(R"([1,{"c":"red","b":2},3])");
  assert(sum_numbers2(input2) == 4);

  auto input3 = json::parse(R"({"d":"red","e":[1,2,3,4],"f":5})");
  assert(sum_numbers2(input3) == 0);

  auto input4 = json::parse(R"([1, "red", 5])");
  assert(sum_numbers2(input4) == 6);
}

std::string AocSolution::part2()
{
  auto input = json::parse(kInput);
  return std::to_string(sum_numbers2(input));
}
