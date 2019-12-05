#include "aoc_solution.hh"

SOLUTION(2015, 3, "2572", "2631");

int compute_part1(const std::string& value)
{
  std::map<std::pair<int, int>, int> locations;

  std::pair<int, int> current_loc = {0, 0};
  locations[current_loc] = 1;

  for (auto v : value)
  {
    switch (v) {
      case 'v': current_loc.first -= 1; break;
      case '^': current_loc.first += 1; break;
      case '<': current_loc.second -= 1; break;
      case '>': current_loc.second += 1; break;
    }
    auto it = locations.find(current_loc);
    if(it == locations.end())
    {
      locations[current_loc] = 1;
    }
    else
    {
      it++;
    }
  }

  return locations.size();
}


int compute_part2(const std::string& value)
{
  std::map<std::pair<int, int>, int> locations;

  std::pair<int, int> current_loc1 = {0, 0};
  std::pair<int, int> current_loc2 = {0, 0};

  locations[current_loc1] = 1;

  bool is_santa = true;


  for (auto v : value)
  {
    std::pair<int, int> current_loc;
    if (is_santa)
    {
      current_loc = current_loc1;
    }
    else
    {
      current_loc = current_loc2;
    }

    switch (v) {
      case 'v': current_loc.first -= 1; break;
      case '^': current_loc.first += 1; break;
      case '<': current_loc.second -= 1; break;
      case '>': current_loc.second += 1; break;
    }
    auto it = locations.find(current_loc);
    if(it == locations.end())
    {
      locations[current_loc] = 1;
    }
    else
    {
      it++;
    }

    if (is_santa)
    {
      current_loc1 = current_loc;
    }
    else
    {
      current_loc2 = current_loc;
    }
    is_santa = !is_santa;
  }

  return locations.size();
}

void AocSolution::test_part1()
{
  assert(compute_part1(">") == 2);
  assert(compute_part1("^>v<") == 4);
  assert(compute_part1("^v^v^v^v^v") == 2);
}

std::string AocSolution::part1()
{
  return std::to_string(compute_part1(kInput));
}

void AocSolution::test_part2()
{
  assert(compute_part2("^v") == 3);
  assert(compute_part2("^>v<") == 3);
  assert(compute_part2("^v^v^v^v^v") == 11);
}

std::string AocSolution::part2()
{
  return std::to_string(compute_part2(kInput));
}
