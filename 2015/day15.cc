#include "aoc_solution.hh"

#include "spdlog/spdlog.h"

SOLUTION(2015, 15, "21367368", "1766400");

const std::string test_input =
R"(Butterscotch: capacity -1, durability -2, flavor 6, texture 3, calories 8
Cinnamon: capacity 2, durability 3, flavor -2, texture -1, calories 3)";

struct Ingredient {
  std::string name;
  int capacity;
  int durability;
  int flavor;
  int texture;
  int calories;
};

Ingredient parse(const std::string& line)
{
  auto vals = split_string(line, ' ');

  return Ingredient {
    vals[0],
    toInt(vals[2]),
    toInt(vals[4]),
    toInt(vals[6]),
    toInt(vals[8]),
    toInt(vals[10])
  };
}

auto find_permutations(int n) {
  std::vector<std::vector<int>> ret;

  std::vector<int> current(n, 0);

  while (current.back() != 100) {
    current[0]++;

    for(size_t ii = 0; ii < n - 1; ++ii)
    {
      if(current[ii] == 100)
      {
        current[ii] = 0;
        current[ii+1]++;
      }
    }

    if (sum(current) == 100)
    {
      ret.push_back(current);
    }
  }
  return ret;
}

auto compute(const std::vector<Ingredient>& ingredients,
             const std::vector<int> vals)
{
  auto capacity = 0;
  auto durability = 0;
  auto flavor = 0;
  auto texture = 0;
  auto calories = 0;

  for (size_t ii = 0; ii < vals.size(); ++ii)
  {
    capacity += vals[ii] * ingredients[ii].capacity;
    durability += vals[ii] * ingredients[ii].durability;
    flavor += vals[ii] * ingredients[ii].flavor;
    texture += vals[ii] * ingredients[ii].texture;
    calories += vals[ii] * ingredients[ii].calories;
  }

  return std::make_tuple(capacity, durability, flavor, texture, calories);
}

auto find_max(const std::vector<std::string>& lines,
              int calories = -1)
{
  auto ingredients = map(lines, parse);

  spdlog::debug("Found {} ingredients", ingredients.size());
  for (auto ingredient: ingredients)
  {
    spdlog::debug("{} capacity {}, durability {}, flavor {}, texture {}, calories {}",
        ingredient.name,
        ingredient.capacity,
        ingredient.durability,
        ingredient.flavor,
        ingredient.texture,
        ingredient.calories);
  }

  auto perms = find_permutations(ingredients.size());
  spdlog::debug("Found {} permutations", perms.size());

  std::vector<int> scores;
  for (size_t ii = 0; ii < perms.size(); ++ii)
  {
    auto zero = [](auto& val){ if (val < 0) val = 0; };
    auto [c, d, f, t, cal] = compute(ingredients, perms[ii]);
    zero(c);
    zero(d);
    zero(f);
    zero(t);
    zero(cal);

    if (calories == -1 || (calories > -1 && cal == calories))
      scores.push_back(c * d * f * t);
  }
  return *std::max_element(scores.begin(), scores.end());
}

void AocSolution::test_part1()
{
  auto lines = split_lines(test_input);
  assert(find_max(lines) == 62842880);
}

std::string AocSolution::part1()
{
  auto lines = split_lines(kInput);
  return std::to_string(find_max(lines));
}

void AocSolution::test_part2()
{
  auto lines = split_lines(test_input);
  assert(find_max(lines, 500) == 57600000);
}

std::string AocSolution::part2()
{
  auto lines = split_lines(kInput);
  return std::to_string(find_max(lines, 500));
}
