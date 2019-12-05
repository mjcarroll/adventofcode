#include "aoc_solution.hh"

#include <iostream>
#include <fstream>

SOLUTION(2019, 6);

struct Body {
  static int kId;
  int id;
  std::string name;
  Body* parent;
  std::vector<Body*> children;

  Body(const std::string& name): name(name), id(kId++) {}
};

int Body::kId = 0;

using Graph = std::map<std::string, Body>;

Graph build_graph(const std::vector<std::string> & orbits)
{
  Graph bodies;

  for (auto line: orbits)
  {
    auto vals = split_string(line, ')');

    auto find_or_insert = [&bodies](auto name){
      auto val = bodies.find(name);
      if (val == bodies.end())
      {
        bool success;
        std::tie(val, success) = bodies.insert({name, {name}});
      }
      return val;
    };

    auto parent = find_or_insert(vals[0]);
    auto child = find_or_insert(vals[1]);

    child->second.parent = &parent->second;
    parent->second.children.push_back(&child->second);
  }

  return bodies;
}

void graph_to_dot(const std::string& fname, Graph graph)
{
  std::ofstream f(fname);

  f << "digraph graphname {" << std::endl;
  // Verticies
  for (auto body: graph)
  {
    f << "  " << body.second.id << " [label=\"" << body.first << "\"];" << std::endl;
  }
  // Edges
  for (auto body: graph)
  {
    for (auto child: body.second.children) {
      f << "  " << body.second.id << " -> " << child->id<< ";" << std::endl;
    }
  }
  f << "}" << std::endl;
}

// Find the list of bodys between body -> root
auto find_path(Graph graph, const std::string& body, const std::string& root="COM")
{
  std::vector<std::string> path;
  Body* current = &(graph.find(body)->second);
  while (current->name != root) {
    current = current->parent;
    path.push_back(current->name);
  }
  return path;
}

// Find the length of the path between body -> root
int compute_depth(Graph graph, const std::string& body, const std::string& root="COM")
{
  Body* current = &(graph.find(body)->second);
  return find_path(graph, body, root).size();
}

// Find a common root body between two bodies.
auto find_common_root(Graph graph, const std::string& body1, const std::string& body2)
{
  auto body1_path = find_path(graph, body1);
  auto body2_path = find_path(graph, body2);

  std::string ret;
  for (auto jump: body1_path)
  {
    auto it = std::find(body2_path.begin(), body2_path.end(), jump);
    if (it != body2_path.end())
    {
      ret = jump;
      break;
    }
  }
  return ret;
}

std::string test_input = R"(COM)B
B)C
C)D
D)E
E)F
B)G
G)H
D)I
E)J
J)K
K)L)";

void AocSolution::test_part1(){
  auto input = split_lines(test_input);
  auto orbits = build_graph(input);
  graph_to_dot("2019_06_test.dot", orbits);

  assert(compute_depth(orbits, "D") == 3);
  assert(compute_depth(orbits, "L") == 7);
  assert(compute_depth(orbits, "COM") == 0);
};

std::string AocSolution::part1()
{
  auto input = split_lines(kInput);
  auto orbits = build_graph(input);

  graph_to_dot("2019_06.dot", orbits);

  std::vector<int> depths;
  for (auto body: orbits) {
    depths.push_back(compute_depth(orbits, body.first));
  }

  return std::to_string(std::accumulate(depths.begin(), depths.end(), 0));
}

std::string test_input2 = R"(COM)B
B)C
C)D
D)E
E)F
B)G
G)H
D)I
E)J
J)K
K)L
K)YOU
I)SAN)";

void AocSolution::test_part2(){
  auto input = split_lines(test_input2);
  auto orbits = build_graph(input);
  graph_to_dot("2019_06_test2.dot", orbits);

  assert(find_common_root(orbits, "YOU", "SAN") == "D");
  auto you = compute_depth(orbits, "YOU", "D") - 1;
  auto san = compute_depth(orbits, "SAN", "D") - 1;
  assert(you + san == 4);
};

std::string AocSolution::part2()
{
  auto input = split_lines(kInput);
  auto orbits = build_graph(input);
  auto root = find_common_root(orbits, "YOU", "SAN");
  auto you = compute_depth(orbits, "YOU", root) - 1;
  auto san = compute_depth(orbits, "SAN", root) - 1;
  return std::to_string(you + san);
}
