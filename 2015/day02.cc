#include "aoc_solution.hh"

SOLUTION(2015, 2, "1588178", "3783758");

int compute(const std::string& value)
{
  auto dims = split_string(value, 'x');
  auto l = atoi(dims[0].c_str());
  auto w = atoi(dims[1].c_str());
  auto h = atoi(dims[2].c_str());

  auto smallest = std::min(l*w, std::min(w*h, h*l));
  return 2*l*w + 2*w*h + 2*h*l + smallest;
}

int compute_part2(const std::string& value)
{
  auto dims = split_string(value, 'x');
  auto l = atoi(dims[0].c_str());
  auto w = atoi(dims[1].c_str());
  auto h = atoi(dims[2].c_str());
  auto smallest = std::min(2*l + 2*w, std::min(2*w + 2*h, 2*h + 2*l));
  auto cuft = l * w * h;
  return smallest + cuft;
}

void AocSolution::test_part1()
{
  assert(compute("2x3x4") == 58);
  assert(compute("1x1x10") == 43);
}

std::string AocSolution::part1()
{
  auto input = split_lines(kInput);

  std::vector<int> vals;
  for(auto inp: input)
  {
    vals.push_back(compute(inp));
  }

  int sum = std::accumulate(vals.begin(), vals.end(), 0);

  return std::to_string(sum);
}

void AocSolution::test_part2()
{
  assert(compute_part2("2x3x4") == 34);
  assert(compute_part2("1x1x10") == 14);
}

std::string AocSolution::part2()
{
  auto input = split_lines(kInput);
  std::vector<int> vals;
  for(auto inp: input)
  {
    vals.push_back(compute_part2(inp));
  }
  int sum = std::accumulate(vals.begin(), vals.end(), 0);

  return std::to_string(sum);
}
