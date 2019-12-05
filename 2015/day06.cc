#include "aoc_solution.hh"

#include <iostream>

SOLUTION(2015, 6, "569999", "17836115");

enum class Instruction { ON, OFF, TOGGLE };

struct Entry
{
  Instruction ins;
  std::pair<int, int> start;
  std::pair<int, int> stop;
};

std::pair<int, int> parse_coords(const std::string & entry)
{
  auto vals = split_string(entry, ',');
  assert(vals.size() == 2);
  int xx = atoi(vals[0].c_str());
  int yy = atoi(vals[1].c_str());
  return {xx, yy};
}

auto parse_entry(const std::string & entry)
{
  Entry ret;
  auto vals = split_string(entry, ' ');

  if (entry.find("turn on") != std::string::npos) {
    ret.ins = Instruction::ON;
    vals.erase(vals.begin(), vals.begin() + 2);
  } else if (entry.find("turn off") != std::string::npos) {
    ret.ins = Instruction::OFF;
    vals.erase(vals.begin(), vals.begin() + 2);
  } else {
    ret.ins = Instruction::TOGGLE;
    vals.erase(vals.begin(), vals.begin() + 1);
  }

  ret.start = parse_coords(vals[0]);
  ret.stop = parse_coords(vals[2]);
  return ret;
}

void AocSolution::test_part1()
{
  {
    auto v = parse_entry("turn on 0,0 through 999,999");
    assert(v.ins == Instruction::ON);
  }
  {
    auto v = parse_entry("toggle 0,0 through 999,0");
    assert(v.ins == Instruction::TOGGLE);
  }
  {
    auto v = parse_entry("turn off 499,499 through 500,500");
    assert(v.ins == Instruction::OFF);
  }
}

std::string AocSolution::part1()
{
  auto input = split_lines(kInput);
  auto entries = map(input, parse_entry);
  bool lights[1000][1000] = {false};

  for (auto entry: entries) {
    for (size_t ii = entry.start.first;
      ii <= entry.stop.first;
      ++ii)
    {
      for (size_t jj = entry.start.second;
        jj <= entry.stop.second;
        ++jj)
      {
        switch (entry.ins) {
          case Instruction::ON:
            lights[ii][jj] = true;
            break;
          case Instruction::OFF:
            lights[ii][jj] = false;
            break;
          case Instruction::TOGGLE:
            lights[ii][jj] = !lights[ii][jj];
            break;
        }
      }
    }
  }

  int sum = 0;
  for (size_t ii = 0; ii < 1000; ++ii) {
    for (size_t jj = 0; jj < 1000; ++jj) {
      sum += lights[ii][jj];
    }
  }

  return std::to_string(sum);
}

void AocSolution::test_part2()
{
}

std::string AocSolution::part2()
{
  auto input = split_lines(kInput);
  auto entries = map(input, parse_entry);
  int lights[1000][1000] = {0};

  for (auto entry: entries) {
    for (size_t ii = entry.start.first;
      ii <= entry.stop.first;
      ++ii)
    {
      for (size_t jj = entry.start.second;
        jj <= entry.stop.second;
        ++jj)
      {
        switch (entry.ins) {
          case Instruction::ON:
            lights[ii][jj] += 1;
            break;
          case Instruction::OFF:
            lights[ii][jj] = std::max(lights[ii][jj] - 1, 0);
            break;
          case Instruction::TOGGLE:
            lights[ii][jj] += 2;
            break;
        }
      }
    }
  }

  int sum = 0;
  for (size_t ii = 0; ii < 1000; ++ii) {
    for (size_t jj = 0; jj < 1000; ++jj) {
      sum += lights[ii][jj];
    }
  }

  return std::to_string(sum);
}
