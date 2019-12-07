#include "aoc_solution.hh"

SOLUTION(2015, 13);

std::string test_input = R"(Alice would gain 54 happiness units by sitting next to Bob.
Alice would lose 79 happiness units by sitting next to Carol.
Alice would lose 2 happiness units by sitting next to David.
Bob would gain 83 happiness units by sitting next to Alice.
Bob would lose 7 happiness units by sitting next to Carol.
Bob would lose 63 happiness units by sitting next to David.
Carol would lose 62 happiness units by sitting next to Alice.
Carol would gain 60 happiness units by sitting next to Bob.
Carol would gain 55 happiness units by sitting next to David.
David would gain 46 happiness units by sitting next to Alice.
David would lose 7 happiness units by sitting next to Bob.
David would gain 41 happiness units by sitting next to Carol.)";

auto parse(const std::string& line) {

  auto vals = split_string(line, ' ');

  auto prime = vals[0];
  auto sign = vals[2];
  auto val = atoi(vals[3].c_str());
  auto second = vals[10];
  second = second.substr(0, second.size() - 1);

  if (sign == "lose") 
  {
    val *= -1;
  }

  return std::make_tuple(prime, second, val);
}

void AocSolution::test_part1()
{
  auto input = split_lines(test_input);
  auto vals = map(input, parse);

  std::set<std::string> names;
  for (auto [prime, second, val] : vals)
  {
    names.insert(prime);
    names.insert(second);
  }
}

std::string AocSolution::part1()
{
  auto input = split_lines(kInput);
  auto vals = map(input, parse);

  return "";
}

void AocSolution::test_part2()
{
}

std::string AocSolution::part2()
{
  return "";
}
