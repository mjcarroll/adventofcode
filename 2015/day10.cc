#include "aoc_solution.hh"
#include "trim.hh"

SOLUTION(2015, 10, "360154", "5103798");

std::string transform(const std::string& input)
{
  std::string ret = "";
  for (size_t ii = 0; ii < input.size(); ++ii)
  {
    auto cur = input[ii];
    int rep = 1;
    for(size_t jj = ii+1; jj < input.size(); ++jj)
    {
      if(input[jj] == input[ii])
      {
        rep++;
        ii++;
      } 
      else
      {
        break;
      }
    }
    ret += std::to_string(rep) + input[ii]; 
  }
  return ret;
}

void AocSolution::test_part1()
{
  assert(transform("1") == "11");
  assert(transform("11") == "21");
  assert(transform("21") == "1211");
  assert(transform("1211") == "111221");
  assert(transform("111221") == "312211");
}

std::string AocSolution::part1()
{
  std::string input = trim_copy(kInput);
  std::string output;

  for (size_t ii = 0; ii < 40; ii++)
  {
    output = transform(input);
    input = output;
  }
  return std::to_string(output.length());
}

void AocSolution::test_part2()
{
}

std::string AocSolution::part2()
{
  std::string input = trim_copy(kInput);
  std::string output;

  for (size_t ii = 0; ii < 50; ii++)
  {
    output = transform(input);
    input = output;
  }
  return std::to_string(output.length());
}
