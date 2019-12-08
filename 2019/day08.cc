#include "aoc_solution.hh"

#include "spdlog/spdlog.h"

SOLUTION(2019, 8, "2562", "ZFLBY");

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

  cur_layer.push_back(cur_row);
  layers.push_back(cur_layer);

  return layers;
}

void print_layer(const Layer& layer, int width=25, int height=6)
{
  for (auto row: layer)
  {
    std::string str;
    for (size_t ii = 0; ii < width; ++ii)
    {
      str += std::to_string(row[ii]);
    }
    spdlog::debug("{}", str);
  }
}

std::string AocSolution::part1()
{
  auto layers = compute_layers(kInput, 25, 6);

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
  auto layers = compute_layers("0222112222120000", 2, 2);
  auto output = layers[0];

  for (size_t layer = 0; layer < layers.size(); ++layer)
  {
    print_layer(layers[layer], 2, 2);
    for (size_t row = 0; row < 2; ++row)
    {
      for (size_t column = 0; column < 2; ++column)
      {
        if (output[row][column] == 2)
        {
          output[row][column] = layers[layer][row][column];
        }
      }
    }
  }

  assert(output[0][0] == 0);
  assert(output[0][1] == 1);
  assert(output[1][0] == 1);
  assert(output[1][1] == 0);
}

std::string AocSolution::part2()
{
  auto layers = compute_layers(kInput, 25, 6);

  auto output = layers[0];
  for (size_t layer = 1; layer < layers.size(); ++layer)
  {
    for (size_t row = 0; row < 6; ++row)
    {
      for (size_t column = 0; column < 25; ++column)
      {
        if (output[row][column] == 2)
        {
          output[row][column] = layers[layer][row][column];
        }
      }
    }
  }

  std::string ret = "";
  for (auto row: output)
  {
    for (auto col: row)
    {
      ret += col == 1 ? "#" : " ";
    }
    ret += '\n';
  }


  spdlog::info(ret);

/*
 * #### #### #    ###  #   #
 *    # #    #    #  # #   #
 *   #  ###  #    ###   # # 
 *  #   #    #    #  #   #  
 * #    #    #    #  #   #  
 * #### #    #### ###    #  
 */
  return "ZFLBY";
}
