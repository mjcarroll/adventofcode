#include "aoc_solution.hh"
#include "int_code.hh"

#include "spdlog/spdlog.h"

SOLUTION(2019, 7, "914828", "17956613");

int amp_chain(const std::vector<long>& prog,
              const std::vector<long>& phases)
{
  long input = 0;

  auto cpu = IntCodeCpu(prog);
  for(size_t ii = 0; ii < phases.size(); ++ii) {
    cpu.Reset();

    // Run until phase input
    cpu.SetInput(phases[ii]);
    cpu.Execute();

    cpu.SetInput(input);
    cpu.Execute();
    input = cpu.GetOutput()[0];
  }

  return input;
}

int feedback_amp_chain(const std::vector<long>& prog,
                       const std::vector<long>& phases)
{
  int input = 0;
  auto cpus = std::vector<IntCodeCpu>(5, {prog});

  for (size_t ii = 0; ii < 5; ++ii)
  {
    cpus[ii].SetInput(phases[ii]);
    cpus[ii].Execute();
  }

  bool running = true;
  while(running)
  {
    for (size_t ii = 0; ii < phases.size(); ++ii)
    {
      cpus[ii].SetInput(input);
      cpus[ii].Execute();
      auto output = cpus[ii].GetOutput();
      assert(output.size() == 1);
      input = output[0];
    }

    int nRunning = sum(map(cpus, [](auto cpu){ return cpu.running; }));
    running = nRunning == 5;
  }

  return input;
}

void AocSolution::test_part1()
{
  std::vector<long> prog1 = {
    3,15,3,16,1002,16,10,16,1,16,15,15,4,15,99,0,0
  };
  assert(amp_chain(prog1, {4,3,2,1,0}) == 43210);

  std::vector<long> prog2 = {
    3,23,3,24,1002,24,10,24,1002,23,-1,23,
    101,5,23,23,1,24,23,23,4,23,99,0,0
  };
  assert(amp_chain(prog2, {0,1,2,3,4}) == 54321);

  std::vector<long> prog3 = {
    3,31,3,32,1002,32,10,32,1001,31,-2,31,1007,31,0,33,
    1002,33,7,33,1,33,31,31,1,32,31,31,4,31,99,0,0,0
  };
  assert(amp_chain(prog3, {1,0,4,3,2}) == 65210);
}

std::string AocSolution::part1()
{
  auto input = split_longs(kInput);

  std::vector<long> vals {0,1,2,3,4};
  std::vector<long> outputs;

  long max = -1;
  do {
    auto output = amp_chain(input, vals);
    if (output > max)
      max = output;
  } while (std::next_permutation(vals.begin(), vals.end()));

  return std::to_string(max);
}

void AocSolution::test_part2()
{
  std::vector<long> prog1 = {
    3,26,1001,26,-4,26,3,27,1002,27,2,27,1,27,26,
    27,4,27,1001,28,-1,28,1005,28,6,99,0,0,5
  };
  assert(feedback_amp_chain(prog1, {9,8,7,6,5}) == 139629729);

  std::vector<long> prog2 = {
    3,52,1001,52,-5,52,3,53,1,52,56,54,1007,54,5,55,1005,55,26,1001,54,
    -5,54,1105,1,12,1,53,54,53,1008,54,0,55,1001,55,1,55,2,53,55,53,4,
    53,1001,56,-1,56,1005,56,6,99,0,0,0,0,10
  };
  assert(feedback_amp_chain(prog2, {9,7,8,5,6}) == 18216);
}

std::string AocSolution::part2()
{
  auto input = split_longs(kInput);

  std::vector<long> vals {5,6,7,8,9};
  std::vector<long> outputs;

  long max = -1;
  do {
    auto output = feedback_amp_chain(input, vals);
    if (output > max)
      max = output;
  } while (std::next_permutation(vals.begin(), vals.end()));

  return std::to_string(max);
}
