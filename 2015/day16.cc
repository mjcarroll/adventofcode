#include "aoc_solution.hh"

#include "spdlog/spdlog.h"

SOLUTION(2015, 16, "213", "323");

struct Sue {
  int id;
  int children {0};
  int cats {0};
  int samoyeds {0};
  int pomeranians {0};
  int akitas {0};
  int vizslas {0};
  int goldfish {0};
  int trees {0};
  int cars {0};
  int perfumes {0};

  void set(const std::string& key, int val)
  {
    if (key == "children") children = val;
    if (key == "cats") cats = val;
    if (key == "samoyeds") samoyeds = val;
    if (key == "pomeranians") pomeranians = val;
    if (key == "akitas") akitas = val;
    if (key == "vizslas") vizslas = val;
    if (key == "goldfish") goldfish = val;
    if (key == "trees") trees = val;
    if (key == "cars") cars = val;
    if (key == "perfumes") perfumes = val;
  }
};

auto cmp(const Sue& sue, const Sue& ref)
{
  int nMatch = 0;
  if (sue.children == ref.children) nMatch++;
  if (sue.cats == ref.cats) nMatch++;
  if (sue.samoyeds == ref.samoyeds) nMatch++;
  if (sue.pomeranians == ref.pomeranians) nMatch++;
  if (sue.akitas == ref.akitas) nMatch++;
  if (sue.vizslas == ref.vizslas) nMatch++;
  if (sue.goldfish == ref.goldfish) nMatch++;
  if (sue.trees == ref.trees) nMatch++;
  if (sue.cars == ref.cars) nMatch++;
  if (sue.perfumes == ref.perfumes) nMatch++;
  return nMatch;
}

auto cmp2(const Sue& sue, const Sue& ref)
{
  int nMatch = 0;
  if (sue.children == ref.children) nMatch++;
  if (sue.cats > ref.cats) nMatch++;
  if (sue.samoyeds == ref.samoyeds) nMatch++;
  if (sue.pomeranians < ref.pomeranians) nMatch++;
  if (sue.akitas == ref.akitas) nMatch++;
  if (sue.vizslas == ref.vizslas) nMatch++;
  if (sue.goldfish < ref.goldfish) nMatch++;
  if (sue.trees > ref.trees) nMatch++;
  if (sue.cars == ref.cars) nMatch++;
  if (sue.perfumes == ref.perfumes) nMatch++;
  return nMatch;
}

Sue parse(const std::string& line)
{
  auto vals = split_string(line, ' ');

  Sue s;
  s.id = toInt(vals[1].substr(0, vals[1].size() - 1));

  for (size_t ii = 2; ii < vals.size(); ii += 2)
  {
    auto key = vals[ii].substr(0, vals[ii].size() - 1);
    auto val = toInt(vals[ii + 1]);
    s.set(key, val);
  }
  return s;
}

void AocSolution::test_part1()
{
}

std::string AocSolution::part1()
{
  auto lines = split_lines(kInput);
  auto sues = map(lines, parse);

  auto ref = Sue({-1, 3, 7, 2, 3, 0, 0, 5, 3, 2, 1});

  int id = -1;
  int max = 0;
  for (auto sue: sues) {
    auto val = cmp(sue, ref);
    if (val > max)
    {
      id = sue.id;
      max = val;
    }
  }
  return std::to_string(id);
}

void AocSolution::test_part2()
{
}

std::string AocSolution::part2()
{
  auto lines = split_lines(kInput);
  auto sues = map(lines, parse);

  auto ref = Sue({-1, 3, 7, 2, 3, 0, 0, 5, 3, 2, 1});

  int id = -1;
  int max = 0;
  for (auto sue: sues) {
    auto val = cmp2(sue, ref);
    if (val >= max)
    {
      id = sue.id;
      max = val;
    }
  }
  return std::to_string(id);
}
