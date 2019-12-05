#include "aoc_common.hh"

#include <map>

static auto kINPUT = input_path(2019, 2);

int compute_part1(std::vector<int>& input)
{
  bool running = true;
  int ip = 0;

  while(running)
  {
    auto opcode = input[ip];
    auto pos1 = input[ip + 1];
    auto pos2 = input[ip + 2];
    auto pos3 = input[ip + 3];

    auto inst_size = 0;

    switch (opcode) {
      case 1:
        input[pos3] = input[pos1] + input[pos2];
        inst_size = 4;
        break;
      case 2:
        input[pos3] = input[pos1] * input[pos2];
        inst_size = 4;
        break;
      case 99:
        running = false;
        break;
      default:
        running = false;
        break;
    }

    if (running)
    {
      ip += inst_size;
    }
  }
}

void part1()
{
  {
    std::vector<int> tmp = {1,9,10,3,2,3,11,0,99,30,40,50};
    compute_part1(tmp);
    assert(tmp[0] == 3500);
  }

  {
    std::vector<int> tmp = {1,0,0,0,99};
    compute_part1(tmp);
    assert(tmp[0] == 2);
  }

  {
    std::vector<int> tmp = {2,3,0,3,99};
    compute_part1(tmp);
    assert(tmp[3] == 6);
  }

  auto input = read_csv_ints(kINPUT);
  input[1] = 12;
  input[2] = 2;
  compute_part1(input);
  std::cout << input[0] << std::endl;
}


std::pair<int, int> compute_part2()
{
  for (int ii = 0; ii <= 99; ++ii)
  {
    for (int jj = 0; jj <= 99; ++jj)
    {
      auto input = read_csv_ints(kINPUT);
      input[1] = ii;
      input[2] = jj;
      compute_part1(input);

      if(input[0] == 19690720)
        return {ii, jj};
    }
  }
}

void part2()
{
  auto vals = compute_part2();
  auto noun = vals.first;
  auto verb = vals.second;
  std::cout << "Noun: " << noun << std::endl;
  std::cout << "Verb: " << verb << std::endl;
  std::cout << "Ans: " << 100 * noun + verb << std::endl;
}

int main(int argc, char** argv)
{
  part1();
  part2();
  return 0;
}
