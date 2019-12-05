#include "aoc_common.hh"
#include "trim.hh"

#include <set>

static auto kINPUT = input_path(2015, 9);

std::string test_input = R"(London to Dublin = 464
London to Belfast = 518
Dublin to Belfast = 141)";

struct Route {
  std::string src;
  std::string dst;
  int cost;

  std::string str() const {
    return src + " to " + dst + " = " + std::to_string(cost);
  }
};

auto parse(const std::string& line)
{
  auto vals = split(line, ' ');
  Route r;
  r.src = vals[0];
  r.dst = vals[2];
  r.cost = atoi(vals[4].c_str());
  return r;
}

void part1()
{
  auto lines = read_lines(kINPUT);
  std::vector<Route> routes;
  for (auto line: lines) { routes.push_back(parse(line)); }

  std::set<std::string> verts;
  for (auto route: routes) {
    verts.insert(route.src);
    verts.insert(route.dst);
  }

  // This reveals that the graph is complete, so let's just permute.
  std::cout << verts.size() << std::endl;
  std::cout << routes.size() << std::endl;


}

void part2()
{
}

int main(int argc, char** argv)
{
  part1();
  part2();
  return 0;
}
