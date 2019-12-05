#include "aoc_solution.hh"

SOLUTION(2015, 1, "74", "1795");

int compute(const std::string& input)
{
  int count = 0;
  for(auto val: input)
  {
    if (val == '(')
      count++;
    else if (val == ')')
      count--;
  }
  return count;
}

int compute_pos(const std::string& input)
{
  int count = 0;
  int pos = 1;
  for(auto val: input)
  {
    if (val == '(')
      count++;
    else if (val == ')')
      count--;

    if (count < 0)
    {
      break;
    }
    pos++;
  }
  return pos;
}

void AocSolution::test_part1()
{
  assert(compute("(())") == 0);
  assert(compute("()()") == 0);
  assert(compute("(((") == 3);
  assert(compute("(()(()(") == 3);
  assert(compute("))(((((") == 3);
  assert(compute("())") == -1);
  assert(compute("))(") == -1);
  assert(compute(")))") == -3);
  assert(compute(")())())") == -3);
}

std::string AocSolution::part1()
{
  return std::to_string(compute(kInput));
}

void AocSolution::test_part2()
{
  assert(compute_pos(")") == 1);
  assert(compute_pos("()())") == 5);
}

std::string AocSolution::part2()
{
  return std::to_string(compute_pos(kInput));
}
