#include "aoc_solution.hh"

#include "spdlog/spdlog.h"

SOLUTION(2015, 14, "2696", "1084");

std::string test_input = R"(Comet can fly 14 km/s for 10 seconds, but then must rest for 127 seconds.
Dancer can fly 16 km/s for 11 seconds, but then must rest for 162 seconds.)";

struct Deer {
  std::string name;
  int speed;
  int dtFly;
  int dtRest;
  bool resting { false };
  int pos { 0 };
  int counter { 0 };
};

auto parse(const std::string& line) {
  auto vals = split_string(line, ' ');

  auto name = vals[0];
  auto speed = toInt(vals[3]);
  auto dtFly = toInt(vals[6]);
  auto dtRest = toInt(vals[13]);

  spdlog::debug("{:<15} {} {} {}", name, speed, dtFly, dtRest);
  return Deer{name, speed, dtFly, dtRest};
}

void propagate(std::vector<Deer>& deer, int t)
{
  for (int ii = 0; ii < t; ii++)
  {
    for (auto& d : deer)
    {
      if (d.resting) {
        d.counter++;
        if (d.counter == d.dtRest) {
          d.resting = false;
          d.counter = 0;
        }
      } else {
        d.pos += d.speed;
        d.counter++;
        if (d.counter == d.dtFly) {
          d.resting = true;
          d.counter = 0;
        }
      }
    }
  }
}

int calc_lead(std::vector<Deer>& deer, int t)
{
  std::map<std::string, int> lead;
  for (size_t ii = 0; ii < t; ++ii)
  {
    propagate(deer, 1);
    int max = 0;
    std::string max_name;
    for (auto d: deer)
    {
      if (d.pos > max) {
        max = d.pos;
        max_name = d.name;
      }
    }

    for (auto d: deer)
    {
      if (d.pos == max)
      {
        lead[d.name] += 1;
      }
    }
  }

  int max = 0;
  std::string max_name;
  for (auto [name, score] : lead) {
    spdlog::debug("{}: {}", name, score);
    if (score > max) {
      max = score;
      max_name = name;
    }
  }
  return max;
}

void AocSolution::test_part1()
{
  auto input = split_lines(test_input);
  {
    auto deer = map(input, parse);
    propagate(deer, 1);
    for (auto d: deer)
    {
      spdlog::debug("{} {} {}", d.name, d.pos, d.resting);
    }
  }
  {
    auto deer = map(input, parse);
    propagate(deer, 10);
    for (auto d: deer)
    {
      spdlog::debug("{} {} {}", d.name, d.pos, d.resting);
    }
  }
  {
    auto deer = map(input, parse);
    propagate(deer, 1000);
    for (auto d: deer)
    {
      spdlog::debug("{} {} {}", d.name, d.pos, d.resting);

      if (d.name == "Comet") {
        assert(d.pos == 1120);
        assert(d.resting);
      }

      if (d.name == "Dancer") {
        assert(d.pos == 1056);
        assert(d.resting);
      }
    }
  }
}

std::string AocSolution::part1()
{
  auto input = split_lines(kInput);
  auto deer = map(input, parse);
  propagate(deer, 2503);

  int max = 0;

  for (auto d: deer)
  {
    spdlog::debug("{} {} {}", d.name, d.pos, d.resting);
    if (d.pos > max)
      max = d.pos;
  }

  return std::to_string(max);
}

void AocSolution::test_part2()
{
  auto input = split_lines(test_input);
  auto deer = map(input, parse);
  assert(calc_lead(deer, 1000) == 689);
}

std::string AocSolution::part2()
{
  auto input = split_lines(kInput);
  auto deer = map(input, parse);
  return std::to_string(calc_lead(deer, 2503));
}
