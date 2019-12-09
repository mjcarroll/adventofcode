#include "aoc_solution.hh"

#include "int_code.hh"

SOLUTION(2019, 9, "2453265701");

void AocSolution::test_part1()
{
  {
    std::vector<long> prog1 = {
      109,1,204,-1,1001,100,1,100,1008,100,16,101,1006,101,0,99
    };
    auto cpu = IntCodeCpu(prog1);
    cpu.Execute();
  }
  {
    std::vector<long> prog1 = {
      1102,34915192,34915192,7,4,7,99,0
    };
    auto cpu = IntCodeCpu(prog1);
    cpu.Execute();
  }
  {
    std::vector<long> prog1 = {
      104,1125899906842624,99
    };
    auto cpu = IntCodeCpu(prog1);
    cpu.Execute();
  }
}

std::string AocSolution::part1()
{
  auto input = split_longs(kInput);
  auto cpu = IntCodeCpu(input);
  cpu.SetInput(1);
  cpu.Execute();
  return std::to_string(cpu.GetOutput());
}

void AocSolution::test_part2()
{
}

std::string AocSolution::part2()
{
  return "";
}
