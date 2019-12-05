#include "aoc_common.hh"

static auto kINPUT = input_path(2015, 1);

int compute(const std::string& input)
{
  int count = 0;
  for(auto val: input)
  {
    if (val == '(')
      count++;
    else 
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
    else 
      count--;

    if (count < 0)
    {
      break;
    }
    pos++;
  }
  return pos;
}


void part1()
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

  auto input = read_string(kINPUT);
  std::cout << compute(input) << std::endl;
}

void part2()
{
  assert(compute_pos(")") == 1);
  assert(compute_pos("()())") == 5);
  auto input = read_string(kINPUT);
  std::cout << compute_pos(input) << std::endl;
}

int main(int argc, char** argv)
{
  part1();
  part2();
  return 0;
}

