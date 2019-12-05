#include "aoc_solution.hh"
#include "int_code.hh"

SOLUTION(2019, 5, "15508323", "9006327");

void AocSolution::test_part1(){
};

std::string AocSolution::part1()
{
  auto input = split_ints(kInput);
  IntCodeCpu cpu(input);
  cpu.SetInput(1);
  cpu.Execute();
  return std::to_string(cpu.GetOutput());
}

void AocSolution::test_part2(){};

std::string AocSolution::part2()
{
  auto input = split_ints(kInput);
  IntCodeCpu cpu(input);
  cpu.SetInput(5);
  cpu.Execute();
  return std::to_string(cpu.GetOutput());
}
