#include "aoc_common.hh"
#include "trim.hh"

static auto kINPUT = input_path(2015, 10);

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

void part1()
{
  assert(transform("1") == "11");
  assert(transform("11") == "21");
  assert(transform("21") == "1211");
  assert(transform("1211") == "111221");
  assert(transform("111221") == "312211");

  std::string input = trim_copy(read_string(kINPUT));
  std::string output;

  std::cout << input << std::endl;
  for (size_t ii = 0; ii < 40; ii++)
  {
    output = transform(input);
    input = output;
    std::cout << output.length() << std::endl;
  }
}

void part2()
{
  std::string input = trim_copy(read_string(kINPUT));
  std::string output;

  std::cout << input << std::endl;
  for (size_t ii = 0; ii < 50; ii++)
  {
    output = transform(input);
    input = output;
    std::cout << output.length() << std::endl;
  }
}

int main(int argc, char** argv)
{
  part1();
  part2();
  return 0;
}
