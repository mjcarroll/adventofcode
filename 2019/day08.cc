#include "aoc_solution.hh"

#include "spdlog/spdlog.h"

SOLUTION(2019, 8, "2562");

using Row = std::vector<int>;
using Layer = std::vector<Row>;

void AocSolution::test_part1()
{
}

int count(const Layer& layer, int val)
{
  int sum = 0;
  for (auto row: layer) {
    for (auto pixel: row) {
      if (pixel == val)
        sum++;
    }
  }
  return sum;
}

auto compute_layers(const std::string& input, int width, int height)
{
  auto layers = std::vector<Layer>();
  auto cur_layer = Layer();
  auto cur_row = Row();
  for(size_t ii = 0; ii < input.size(); ++ii)
  {
    if (cur_row.size() == width)
    {
      if (cur_layer.size() == height)
      {
        layers.push_back(cur_layer);
        cur_layer = Layer();
      }
      cur_layer.push_back(cur_row);
      cur_row = Row();
    }

    cur_row.push_back(static_cast<int>(input[ii] -'0'));
  }

  return layers;
}

void print_layer(const Layer& layer)
{
  for (auto row: layer)
  {
    std::string str;
    for (size_t ii = 0; ii < 25; ++ii)
    {
      str += std::to_string(row[ii]);
    }
    spdlog::debug("{}", str);
  }
}

std::string AocSolution::part1()
{
  auto layers = compute_layers(kInput, 25, 6);

  for (auto layer: layers)
  {
    print_layer(layer);
    spdlog::debug("");
  }

  int min = 1e6;
  size_t minIdx = -1;
  for (size_t ii = 0; ii < layers.size(); ++ii)
  {
    auto zeros = count(layers[ii], 0);
    if (zeros < min)
    {
      min = zeros;
      minIdx = ii;
    }
  }

  return std::to_string(count(layers[minIdx], 1) * count(layers[minIdx], 2));
}

void AocSolution::test_part2()
{
}

std::string AocSolution::part2()
{
  return "";
}
