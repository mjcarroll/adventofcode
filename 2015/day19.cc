#include "aoc_solution.hh"

#include "spdlog/spdlog.h"

#include <queue>

SOLUTION(2015, 19, "518", "200");

std::string test_input1 =
R"(H => OH
H => HO
O => HH

HOH)";

std::string test_input2 =
R"(H => OH
H => HO
O => HH

HOHOHO)";

std::string test_input3 =
R"(Ca => CaCa
Al => ThF

HBFCaAlFBAl)";

auto parse(const std::string& line) {
  auto it = line.find("=>");
  auto p1 = line.substr(0, it - 1);
  auto p2 = line.substr(it+3, line.size() - (it + 3));
  return std::make_pair(p1, p2);
}

// Really lazy, do the same parse but reverse args
auto parse2(const std::string& line) {
  auto it = line.find("=>");
  auto p1 = line.substr(0, it - 1);
  auto p2 = line.substr(it+3, line.size() - (it + 3));
  return std::make_pair(p2, p1);
}

auto make_substituions(const std::string& molecule,
                       std::vector<std::pair<std::string, std::string>> subs)
{
  std::set<std::string> molecules;
  for (auto sub: subs)
  {
    std::string out;
    auto it = molecule.find(sub.first);

    while (it != std::string::npos)
    {
      auto pre = molecule.substr(0, it);
      auto post = molecule.substr(it + sub.first.size(), molecule.size() - sub.first.size() - pre.size());
      out = pre + sub.second + post;
      molecules.insert(out);
      it = molecule.find(sub.first, it+1);
    }
  }
  return molecules;
}

void AocSolution::test_part1()
{
  {
    auto lines = split_lines(test_input1);
    auto molecule = lines.back();
    lines.resize(lines.size() - 2);
    auto subs = map(lines, parse);
    auto molecules = make_substituions(molecule, subs);
    assert(molecules.size() == 4);
  }
  {
    auto lines = split_lines(test_input2);
    auto molecule = lines.back();
    lines.resize(lines.size() - 2);
    auto subs = map(lines, parse);
    auto molecules = make_substituions(molecule, subs);
    assert(molecules.size() == 7);
  }
  {
    auto lines = split_lines(test_input3);
    auto molecule = lines.back();
    lines.resize(lines.size() - 2);
    auto subs = map(lines, parse);
    auto molecules = make_substituions(molecule, subs);
    assert(molecules.size() == 3);
  }
}

std::string AocSolution::part1()
{
  auto lines = split_lines(kInput);
  auto molecule = lines.back();
  lines.resize(lines.size() - 2);
  auto subs = map(lines, parse);
  auto molecules = make_substituions(molecule, subs);
  return std::to_string(molecules.size());
}

struct Check {
  std::string cur;
  std::vector<std::string> pre;

  bool operator<(const Check& other) const {
    return this->cur.length() < other.cur.length();
  }
};


Check find_inverse(const std::string& molecule,
                   const std::vector<std::pair<std::string, std::string>>& subs)
{
  std::vector<std::pair<std::string, std::string>> subs2{subs.begin(), subs.end()};
  std::sort(subs2.begin(), subs2.end(), [](auto sub1, auto sub2){ return sub1.first.size() > sub2.first.size(); });

  // Don't check seen things again
  std::set<std::string> visited;
  visited.insert(molecule);

  Check to_check { molecule, {} };

  while(true)
  {
    Check to_check_next;
    for (auto sub: subs2)
    {
      auto valid_subs = make_substituions(to_check.cur, {sub});
      for (auto valid : valid_subs)
      {
        if (visited.count(valid))
          continue;
        to_check_next.cur = valid;
        to_check_next.pre = to_check.pre;
        to_check_next.pre.push_back(to_check.cur);
        visited.insert(valid);
        break;
      }
      if(valid_subs.size() > 0)
        break;
    }

    to_check = to_check_next;

    if (to_check.cur.size() == 1)
    {
      break;
    }
  }

  to_check.pre.push_back(to_check.cur);
  return to_check;
}


void AocSolution::test_part2()
{
  auto lines = split_lines(test_input1);
  auto molecule = lines.back();
  lines.resize(lines.size() - 2);

  auto subs = map(lines, parse2);
  subs.push_back({"H", "e"});
  subs.push_back({"O", "e"});

  auto sol = find_inverse(molecule, subs);
  assert(sol.pre.size() == 3);
  size_t ii = 0;
  for (auto pre: sol.pre)
  {
    spdlog::debug("{} {}", ii++, pre);
  }

  auto sol2 = find_inverse("HOHOHO", subs);
  assert(sol2.pre.size() == 6);
  ii = 0;
  for (auto pre: sol2.pre)
  {
    spdlog::debug("{} {}", ii++, pre);
  }
}

std::string AocSolution::part2()
{
  auto lines = split_lines(kInput);
  auto molecule = lines.back();
  lines.resize(lines.size() - 2);
  auto subs = map(lines, parse2);

  auto sol = find_inverse(molecule, subs);
  size_t ii = 0;
  /*
  for (auto pre: sol.pre)
  {
    spdlog::debug("{} {}", ii++, pre);
  }
  */
  return std::to_string(sol.pre.size()-1);
}
