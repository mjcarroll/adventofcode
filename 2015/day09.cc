#include "aoc_solution.hh"

#include "spdlog/spdlog.h"

#include <set>

SOLUTION(2015, 9, "117");

std::string test_input = R"(London to Dublin = 464
London to Belfast = 518
Dublin to Belfast = 141)";

struct Route {
  std::string src;
  std::string dst;
  int cost;
};

auto parse(const std::string& line)
{
  auto vals = split_string(line, ' ');
  Route r;
  r.src = vals[0];
  r.dst = vals[2];
  r.cost = atoi(vals[4].c_str());
  return r;
}

auto unique_verts(const std::vector<Route>& routes)
{
  std::set<std::string> verts;
  for (auto route: routes) {
    verts.insert(route.src);
    verts.insert(route.dst);
  }
  return verts;
}

int solve(const std::vector<Route> & routes)
{
  auto verts = unique_verts(routes);
  auto permVerts = std::vector<std::string>(verts.begin(), verts.end());

  auto find_route = [&](auto src, auto dst) -> const Route* {
    const Route* ret = nullptr;
    for (auto & route: routes)
    {
      if(route.src == src && route.dst == dst)
      {
        ret = &route;
      }
      else if(route.src == dst && route.dst == src)
      {
        ret = &route;
      }
    }
    return ret;
  };

  auto cost = [&](auto verts){
    int sum = 0;
    for (size_t ii = 0; ii < verts.size() - 1; ++ii)
    {
      auto it = find_route(verts[ii], verts[ii+1]);
      if (it)
        sum += find_route(verts[ii], verts[ii+1])->cost;
      else
        spdlog::error("Invalid route {} -> {}", verts[ii], verts[ii+1]);
    }
    return sum;
  };

  int min = 1e6;
  do {
    auto routeCost = cost(permVerts);
    spdlog::debug("{} {} {}", permVerts[0], permVerts.back(), routeCost);
    if (routeCost < min)
    {
      min = routeCost;
    }
  } while (std::next_permutation(permVerts.begin(), permVerts.end()));

  return min;
}

void AocSolution::test_part1()
{
  auto lines = split_lines(test_input);
  auto routes = map(lines, parse);
  assert(solve(routes) == 605);
}

std::string AocSolution::part1()
{
  auto lines = split_lines(kInput);
  auto routes = map(lines, parse);

  return std::to_string(solve(routes));
}

void AocSolution::test_part2()
{
}

std::string AocSolution::part2()
{
  return "";
}

