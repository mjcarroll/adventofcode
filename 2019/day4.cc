#include "aoc_common.hh"
#include "trim.hh"

#include <cassert>

static auto kINPUT = input_path(2019, 4);

bool has_repeating(const std::string& input)
{
  for (size_t ii = 1; ii < input.length(); ++ii)
  {
    if (input[ii-1] == input[ii])
    {
      return true;
    }
  }
  return false;
}

bool ascending(const std::string& input)
{
  for (size_t ii = 1; ii < input.length(); ++ii)
  {
    if (input[ii-1] > input[ii])
    {
      return false;
    }
  }
  return true;
}

bool valid(int input)
{
  auto as_str = std::to_string(input);
  return has_repeating(as_str) && ascending(as_str);
}

void part1()
{
  assert(valid(111111) == true);
  assert(valid(223450) == false);
  assert(valid(123789) == false);

  int bottom = 356261;
  int top = 846303;

  std::vector<int> passes;
  for (int ii = bottom; ii < top; ++ii)
  {
    if (valid(ii))
    {
      passes.push_back(ii);
    }
  }
  std::cout << passes.size() << std::endl;
}

bool rule2(int input)
{
  auto as_str = std::to_string(input);

  std::vector<int> adj;

  for (size_t ii = 0; ii < as_str.length(); ++ii)
  {
    auto cmp = as_str[ii];
    auto count = 1;

    for (size_t jj = ii + 1; jj < as_str.length(); ++jj)
    {
      if (as_str[jj] == cmp)
      {
        ii++;
        count++;
      }
      else
      {
        break;
      }
    }

    if (count == 2)
    {
      return true;
    }
  }
  return false;
}

void part2()
{
  assert(rule2(112233) == true);
  assert(rule2(123444) == false);
  assert(rule2(111122) == true);

  int bottom = 356261;
  int top = 846303;

  std::vector<int> passes;
  for (int ii = bottom; ii < top; ++ii)
  {
    if (valid(ii))
    {
      passes.push_back(ii);
    }
  }

  int count = 0;
  for (auto pass: passes)
  {
    if(rule2(pass)) count++;
  }
  std::cout << count << std::endl;
}

int main(int argc, char** argv)
{
  part1();
  part2();
  return 0;
}
