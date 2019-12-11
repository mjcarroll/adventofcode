#include "aoc_solution.hh"
#include "int_code.hh"

SOLUTION(2019, 2, "3224742", "7960");

void AocSolution::test_part1(){
};

int exec_with_args(const std::vector<long> & program, int arg1, int arg2)
{
  IntCodeCpu cpu(program);
  cpu.SetMemory(1, arg1);
  cpu.SetMemory(2, arg2);
  cpu.Execute();
  return cpu.GetMemory(0);
}

std::string AocSolution::part1()
{
  auto input = split_longs(kInput);
  return std::to_string(exec_with_args(input, 12, 2));
}

void AocSolution::test_part2(){};

std::string AocSolution::part2()
{
  auto input = split_longs(kInput);
  for (int noun = 0; noun <= 99; ++noun)
  {
    for (int verb = 0; verb <= 99; ++verb)
    {
      auto val = exec_with_args(input, noun, verb);
      if (val == 19690720)
        return std::to_string(100 * noun + verb);
    }
  }
  return "Failed";
}
