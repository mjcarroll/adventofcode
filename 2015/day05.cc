#include "aoc_solution.hh"

#include <algorithm>
#include <iomanip>

SOLUTION(2015, 5, "238", "69");

bool nice_string(const std::string& value)
{
  const std::string vowels= "aeiou";

  auto nVowels = std::count_if(value.begin(), value.end(),
      [=](char x){
        return vowels.find(x) != std::string::npos;
      });

  if (nVowels < 3)
    return false;

  if (value.find("ab") != std::string::npos ||
      value.find("cd") != std::string::npos ||
      value.find("pq") != std::string::npos ||
      value.find("xy") != std::string::npos)
  {
    return false;
  }

  bool double_found = false;
  for (size_t ii = 1; ii < value.length(); ++ii)
  {
    if (value[ii - 1] == value[ii])
    {
      double_found = true;
    }
  }

  return double_found;
}

bool two_pair(const std::string& value)
{
  bool two_pair = false;
  for (size_t ii = 1; ii < value.length(); ++ii)
  {
    std::string pair = {value[ii-1], value[ii]};
    auto found = value.find(pair, ii + 1);

    if (found != std::string::npos)
    {
      two_pair = true;
    }
  }
  return two_pair;
}

bool repeats(const std::string& value)
{
  bool repeats = false;
  for (size_t ii = 2; ii < value.length(); ++ii)
  {
    if (value[ii] == value[ii-2])
    {
      repeats = true;
    }
  }
  return repeats;
}

bool nice_string2(const std::string& value)
{
  return two_pair(value) && repeats(value);
}

void AocSolution::test_part1()
{
  assert(nice_string("ugknbfddgicrmopn") == true);
  assert(nice_string("aaa") == true);
  assert(nice_string("jchzalrnumimnmhp") == false);
  assert(nice_string("haegwjzuvuyypxyu") == false);
  assert(nice_string("dvszwmarrgswjxmb") == false);
}

std::string AocSolution::part1()
{
  auto input = split_lines(kInput);
  return std::to_string(std::count_if(input.begin(), input.end(), nice_string));
}

void AocSolution::test_part2()
{
  assert(two_pair("xyxy") == true);
  assert(two_pair("aabcdefgaa") == true);
  assert(two_pair("aaa") == false);

  assert(repeats("xyx") == true);
  assert(repeats("abcdefeghi") == true);
  assert(repeats("aaa") == true);

  assert(nice_string2("qjhvhtzxzqqjkmpb") == true);
  assert(nice_string2("xxyxx") == true);
  assert(nice_string2("uurcxstgmygtbstg") == false);
  assert(nice_string2("ieodomkazucvgmuy") == false);
}

std::string AocSolution::part2()
{
  auto input = split_lines(kInput);
  return std::to_string(std::count_if(input.begin(), input.end(), nice_string2));
}
