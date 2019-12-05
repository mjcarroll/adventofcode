#include "aoc_common.hh"

#include <algorithm>
#include <iomanip>
#include <map>
#include <set>

static auto kINPUT = input_path(2015, 7);

enum class GateType {
  CONST,
  AND, 
  OR, 
  NOT, 
  LSHIFT, 
  RSHIFT
};


struct Gate
{
  int id;
  GateType type;
  int val;
  std::string wire_a;
  std::string wire_b;
  std::string wire_o;

  auto str() const {
    std::string ret;
    ret = std::to_string(id) + ": ";

    switch(type) {
      case GateType::CONST:
        ret += wire_a + " -> " + wire_o;
        break;
      case GateType::AND:
        ret += wire_a + " AND " + wire_b + " -> " + wire_o;
        break;
      case GateType::OR:
        ret += wire_a + " OR " + wire_b + " -> " + wire_o;
        break;
      case GateType::NOT:
        ret += "NOT " + wire_a + " -> " + wire_o;
        break;
      case GateType::LSHIFT:
        ret += wire_a + " LSHIFT " + std::to_string(val) + " -> " + wire_o ;
        break;
      case GateType::RSHIFT:
        ret += wire_a + " RSHIFT " + std::to_string(val) + " -> " + wire_o ;
        break;
    }

    return ret;
  }
};

struct Wire
{
  std::string name;
  bool ready {false};
  uint16_t value {0};
  Gate* input {nullptr};
  std::vector<Gate*> outputs;
};

void compute_graph(const std::vector<std::string>& input,
                   std::vector<Gate>& gates,
                   std::map<std::string, Wire>& wires)
{
  std::set<std::string> wire_names;

  int count = 0;

  for (auto inp: input) {
    Gate g;
    g.id = count++;
    auto args = split(inp, ' ');

    if (inp.find("AND") != std::string::npos)
    {
      g.type = GateType::AND;
      g.wire_a = args[0];
      g.wire_b = args[2];
      g.wire_o = args[4];
    }
    else if (inp.find("OR") != std::string::npos)
    {
      g.type = GateType::OR;
      g.wire_a = args[0];
      g.wire_b = args[2];
      g.wire_o = args[4];
    }
    else if (inp.find("NOT") != std::string::npos)
    {
      g.type = GateType::NOT;
      g.wire_a = args[1];
      g.wire_o = args[3];
    } 
    else if (inp.find("LSHIFT") != std::string::npos)
    {
      g.type = GateType::LSHIFT;
      g.wire_a = args[0];
      g.wire_o = args[4];
      g.val = atoi(args[2].c_str());
    }
    else if (inp.find("RSHIFT") != std::string::npos)
    {
      g.type = GateType::RSHIFT;
      g.wire_a = args[0];
      g.wire_o = args[4];
      g.val = atoi(args[2].c_str());
    }
    else 
    {
      g.type = GateType::CONST;
      g.wire_a = args[0];
      g.wire_o = args[2];
    }

    if (!g.wire_a.empty())
      wire_names.insert(g.wire_a);
    if (!g.wire_b.empty())
      wire_names.insert(g.wire_b);
    if (!g.wire_o.empty())
      wire_names.insert(g.wire_o);

    gates.push_back(g);
  }

  for (auto wire_name: wire_names)
  {
    Wire w;
    w.name = wire_name;
    auto all_alpha = std::find_if(w.name.begin(), 
        w.name.end(), [](char c){ return !std::isalpha(c); }) == w.name.end();

    if (!all_alpha) {
      w.ready = true;
      w.value = atoi(w.name.c_str());
    }

    wires[wire_name] = w;
  }

  for (auto & g: gates) 
  {
    if (!g.wire_o.empty())
    {
      wires[g.wire_o].input = &g;
    }
    if (!g.wire_a.empty())
    {
      wires[g.wire_a].outputs.push_back(&g);
    }
    if (!g.wire_b.empty())
    {
      wires[g.wire_a].outputs.push_back(&g);
    }
  }
}


void part1()
{
  auto input = split(read_string(kINPUT), '\n');
  std::vector<Gate> gates;
  std::map<std::string, Wire> wires;
  compute_graph(input, gates, wires);

  bool running = true;
  while(running)
  {
    int sum = 0;
    for (auto & wire: wires) {
      if (wire.second.ready)
      {
        sum++;
      }
    }
    std::cout << "Wires ready: " << sum << " of " << wires.size() << std::endl;

    if (sum == wires.size())
    {
      running = false;
      break;
    }

    for (auto & gate: gates) {
      if (gate.type == GateType::CONST &&
          wires[gate.wire_a].ready) {
        wires[gate.wire_o].value = wires[gate.wire_a].value;
        wires[gate.wire_o].ready = true; 
      }
      else if (gate.type == GateType::NOT &&
          wires[gate.wire_a].ready) {
        wires[gate.wire_o].value = ~wires[gate.wire_a].value;
        wires[gate.wire_o].ready = true;
      }
      else if (gate.type == GateType::AND &&
          wires[gate.wire_a].ready &&
          wires[gate.wire_b].ready) {
        auto val = wires[gate.wire_a].value & wires[gate.wire_b].value;
        wires[gate.wire_o].value = val;
        wires[gate.wire_o].ready = true;
      }
      else if (gate.type == GateType::OR &&
          wires[gate.wire_a].ready &&
          wires[gate.wire_b].ready) {
        auto val = wires[gate.wire_a].value | wires[gate.wire_b].value;
        wires[gate.wire_o].value = val;
        wires[gate.wire_o].ready = true;
      }
      else if (gate.type == GateType::LSHIFT &&
          wires[gate.wire_a].ready) {
        auto val = wires[gate.wire_a].value << gate.val;
        wires[gate.wire_o].value = val;
        wires[gate.wire_o].ready = true;
      }
      else if (gate.type == GateType::RSHIFT &&
          wires[gate.wire_a].ready) {
        auto val = wires[gate.wire_a].value >> gate.val;
        wires[gate.wire_o].value = val;
        wires[gate.wire_o].ready = true;
      }
    }
  }

  std::cout << wires["a"].value << std::endl;
}

void part2()
{
  auto input = split(read_string(kINPUT), '\n');
  std::vector<Gate> gates;
  std::map<std::string, Wire> wires;
  compute_graph(input, gates, wires);

  wires["14146"].value = 956;

  bool running = true;
  while(running)
  {
    int sum = 0;
    for (auto & wire: wires) {
      if (wire.second.ready)
      {
        sum++;
      }
    }
    std::cout << "Wires ready: " << sum << " of " << wires.size() << std::endl;

    if (sum == wires.size())
    {
      running = false;
      break;
    }

    for (auto & gate: gates) {
      if (gate.type == GateType::CONST &&
          wires[gate.wire_a].ready) {
        wires[gate.wire_o].value = wires[gate.wire_a].value;
        wires[gate.wire_o].ready = true; 
      }
      else if (gate.type == GateType::NOT &&
          wires[gate.wire_a].ready) {
        wires[gate.wire_o].value = ~wires[gate.wire_a].value;
        wires[gate.wire_o].ready = true;
      }
      else if (gate.type == GateType::AND &&
          wires[gate.wire_a].ready &&
          wires[gate.wire_b].ready) {
        auto val = wires[gate.wire_a].value & wires[gate.wire_b].value;
        wires[gate.wire_o].value = val;
        wires[gate.wire_o].ready = true;
      }
      else if (gate.type == GateType::OR &&
          wires[gate.wire_a].ready &&
          wires[gate.wire_b].ready) {
        auto val = wires[gate.wire_a].value | wires[gate.wire_b].value;
        wires[gate.wire_o].value = val;
        wires[gate.wire_o].ready = true;
      }
      else if (gate.type == GateType::LSHIFT &&
          wires[gate.wire_a].ready) {
        auto val = wires[gate.wire_a].value << gate.val;
        wires[gate.wire_o].value = val;
        wires[gate.wire_o].ready = true;
      }
      else if (gate.type == GateType::RSHIFT &&
          wires[gate.wire_a].ready) {
        auto val = wires[gate.wire_a].value >> gate.val;
        wires[gate.wire_o].value = val;
        wires[gate.wire_o].ready = true;
      }
    }
  }

  std::cout << wires["a"].value << std::endl;
}

int main(int argc, char** argv)
{
  part1();
  part2();
  return 0;
}




