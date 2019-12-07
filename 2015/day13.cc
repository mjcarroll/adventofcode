#include "aoc_solution.hh"

#include "spdlog/spdlog.h"

SOLUTION(2015, 13, "733", "725");

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

  spdlog::debug("{:<40} {} {} {}", line, prime, second, val);

  return std::make_tuple(prime, second, val);
}

using PeoplePair = std::pair<std::string, std::string>;
using PeopleMap = std::map<PeoplePair, int>;

int solve(PeopleMap people, std::set<std::string> names) {
  auto permNames = std::vector<std::string>(names.begin(), names.end());
  int max = 0;
  do {
    std::string str = "";
    for (size_t ii = 0; ii < permNames.size(); ++ii)
    {
      str += permNames[ii] + " ";
    }
    spdlog::debug("{}",str);

    auto compute_pos = [&](int ii) {
      auto left = (ii == 0) ? permNames.size() - 1 : ii - 1;
      auto right = (ii == permNames.size() - 1) ? 0 : ii + 1;

      auto val_left = people[std::make_pair(permNames[ii], permNames[left])];
      spdlog::debug("{} {} {}", permNames[ii], permNames[left], val_left);

      auto val_right = people[std::make_pair(permNames[ii], permNames[right])];
      spdlog::debug("{} {} {}", permNames[ii], permNames[right], val_right);

      return std::make_pair(val_left, val_right);
    };

    int sum = 0;
    for (size_t ii = 0; ii < permNames.size(); ++ii)
    {
      auto pos = compute_pos(ii);
      sum += pos.first + pos.second;
      spdlog::debug("{}: {} {}", permNames[ii], pos.first, pos.second);
    }

    if (sum > max)
      max = sum;
  } while (std::next_permutation(permNames.begin(), permNames.end()));

  return max;
}

void AocSolution::test_part1()
{
  auto input = split_lines(test_input);
  auto vals = map(input, parse);

  std::map<std::pair<std::string,std::string>,int> people;
  std::set<std::string> names;

  for (auto [prime, second, val] : vals)
  {
    people[std::make_pair(prime,second)] = val;
    names.insert(prime);
    names.insert(second);
  }
  assert(solve(people, names) == 330);
}

std::string AocSolution::part1()
{
  auto input = split_lines(kInput);
  auto vals = map(input, parse);
  std::map<std::pair<std::string,std::string>,int> people;
  std::set<std::string> names;

  for (auto [prime, second, val] : vals)
  {
    people[std::make_pair(prime,second)] = val;
    names.insert(prime);
    names.insert(second);
  }

  return std::to_string(solve(people, names));
}

void AocSolution::test_part2()
{
}

std::string AocSolution::part2()
{
  auto input = split_lines(kInput);
  auto vals = map(input, parse);
  std::map<std::pair<std::string,std::string>,int> people;
  std::set<std::string> names;

  for (auto [prime, second, val] : vals)
  {
    people[std::make_pair(prime,second)] = val;
    names.insert(prime);
    names.insert(second);
  }

  for (auto name : names)
  {
    people[std::make_pair("me",name)] = 0;
  }
  names.insert("me");

  return std::to_string(solve(people, names));
}
