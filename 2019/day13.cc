#include "aoc_solution.hh"

#include "spdlog/spdlog.h"
#include "int_code.hh"

SOLUTION(2019, 13, "412", "20940");

struct Tile {
  long x;
  long y;
  long id;
};


void AocSolution::test_part1()
{
}

std::string AocSolution::part1()
{
  auto program = split_longs(kInput);
  IntCodeCpu cpu(program);

  cpu.Execute();

  auto output = cpu.GetOutput();
  std::vector<Tile> tiles;
  long max_x = 0;
  long max_y = 0;
  for(size_t ii = 0; ii < output.size(); ii += 3)
  {
    tiles.push_back({output[ii], output[ii+1], output[ii+2]});
    max_x = std::max(max_x, output[ii]);
    max_y = std::max(max_y, output[ii]);
  }

  auto grid = make_grid(max_y+1, max_x+1, 0);

  for (auto tile: tiles)
  {
    grid[tile.y][tile.x] = tile.id;
  }

  spdlog::debug(display_grid(grid, [](auto cell, auto rr, auto cc){
      switch(cell)
      {
        case 0: return " ";
        case 1: return "#";
        case 2: return "=";
        case 3: return "-";
        case 4: return "*";
        default: return " ";
      }
  }));

  int s = 0;
  for (auto row: grid)
    for (auto col: row)
      if (col == 2)
        s++;

  return std::to_string(s);
}

void AocSolution::test_part2()
{
}

std::string AocSolution::part2()
{
  auto program = split_longs(kInput);
  IntCodeCpu cpu(program);
  cpu.SetMemory(0, 2);

  long score = 0;
  long ball_x = 0;
  long paddle_x = 0;

  while(cpu.running)
  {
    cpu.SetInput(std::clamp<long>(ball_x - paddle_x, -1, 1));
    cpu.Execute();
    auto output = cpu.GetOutput();
    std::vector<Tile> tiles;
    for(size_t ii = 0; ii < output.size(); ii += 3)
    {
      tiles.push_back({output[ii], output[ii+1], output[ii+2]});
    }

    for (auto tile: tiles)
    {
      if (tile.id == 4)
      {
        ball_x = tile.x;
      }
      if (tile.id == 3)
      {
        paddle_x = tile.x;
      }
      if (tile.x == -1 && tile.y == 0)
      {
        score = tile.id;
      }
    }
  }

  return std::to_string(score);
}
