#include "aoc_common.hh"

static auto kINPUT = input_path(2015, 2);

int compute(const std::string& value)
{
  auto dims = split(value, 'x');
  auto l = atoi(dims[0].c_str());
  auto w = atoi(dims[1].c_str());
  auto h = atoi(dims[2].c_str());

  auto smallest = std::min(l*w, std::min(w*h, h*l));
  return 2*l*w + 2*w*h + 2*h*l + smallest;
}

void part1()
{
  assert(compute("2x3x4") == 58);
  assert(compute("1x1x10") == 43);

  auto input = read_strings(kINPUT);

  std::vector<int> vals;
  for(auto inp: input)
  {
    vals.push_back(compute(inp));
  }

  std::cout << std::accumulate(vals.begin(), vals.end(), 0) << std::endl;
}


int compute_part2(const std::string& value)
{
  auto dims = split(value, 'x');
  auto l = atoi(dims[0].c_str());
  auto w = atoi(dims[1].c_str());
  auto h = atoi(dims[2].c_str());

  auto smallest = std::min(2*l + 2*w, std::min(2*w + 2*h, 2*h + 2*l));
  auto cuft = l * w * h;

  std::cout << value << ": " << smallest << ", " << cuft << ", " << smallest + cuft << std::endl;
  return smallest + cuft;
}

void part2()
{
  assert(compute_part2("2x3x4") == 34);
  assert(compute_part2("1x1x10") == 14);

  auto input = read_strings(kINPUT);
  std::vector<int> vals;
  for(auto inp: input)
  {
    vals.push_back(compute_part2(inp));
  }
  std::cout << std::accumulate(vals.begin(), vals.end(), 0) << std::endl;
}

int main(int argc, char** argv)
{
  part1();
  part2();
  return 0;
}


