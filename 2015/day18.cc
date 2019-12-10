#include "aoc_solution.hh"

#include <iostream>
#include "spdlog/spdlog.h"

SOLUTION(2015, 18, "1061", "1006");

struct Grid {
  std::vector<std::vector<int>> grid;

  Grid(size_t size) {
    for (size_t ii = 0; ii < size; ++ii)
    {
      grid.push_back(std::vector<int>(size, 0));
    }
  }

  int sum() const
  {
    int s = 0;
    for (auto row: grid)
    {
      for (auto col: row)
      {
        s += col;
      }
    }
    return s;
  }

  void set(const std::vector<std::string>& lines)
  {
    int row = 0;
    for (auto line: lines)
    {
      int col = 0;
      for (auto c: line)
      {
        grid[row][col] = c == '#' ? 1 : 0;
        col++;
      }
      row++;
    }
  }

  int count_neighbors(int row, int col)
  {
    auto check = [&](auto row, auto col)
    {
      if (row < 0 || col < 0)
        return 0;
      if (row >= grid.size() || col >= grid.size())
        return 0;
      return grid[row][col];
    };

    return check(row-1, col-1) + check(row-1, col+0) + check(row-1, col+1) +
           check(row+0, col-1) +                       check(row+0, col+1) +
           check(row+1, col-1) + check(row+1, col+0) + check(row+1, col+1);
  }

  Grid step()
  {
    Grid g(grid.size());

    for (size_t ii = 0; ii < grid.size(); ++ii)
    {
      for (size_t jj = 0; jj < grid.size(); ++jj)
      {
        int neighbors = count_neighbors(ii, jj);
        if (grid[ii][jj] == 1)
        {
          if (neighbors == 2 || neighbors == 3)
          {
            g.grid[ii][jj] = 1;
          }
          else
          {
            g.grid[ii][jj] = 0;
          }
        }
        else
        {
          if (neighbors == 3)
          {
            g.grid[ii][jj] = 1;
          }
          else
          {
            g.grid[ii][jj] = 0;
          }
        }
      }
    }

    return g;
  }

  void print() const {
    for (auto row: grid)
    {
      std::string str = "";
      for (auto col: row)
      {
        str += col == 1 ? "#" : ".";
      }
      spdlog::debug("{}", str);
    }
  }

};

void AocSolution::test_part1()
{
  std::string init = R"(.#.#.#
...##.
#....#
..#...
#.#..#
####..)";

  auto lines = split_lines(init);

  Grid g(6);
  g.set(lines);
  g.print();

  auto next = g.step();
  next.print();

  next = next.step();
  next = next.step();

  assert(next.sum() == 4);
}

std::string AocSolution::part1()
{
  auto lines = split_lines(kInput);

  Grid g(100);
  g.set(lines);

  for (size_t ii = 0; ii < 100; ++ii)
  {
    g = g.step();
  }

  return std::to_string(g.sum());
}

void AocSolution::test_part2()
{
}

std::string AocSolution::part2()
{
  auto lines = split_lines(kInput);

  Grid g(100);
  g.set(lines);

  for (size_t ii = 0; ii < 100; ++ii)
  {
    g = g.step();
    g.grid[0][0] = 1;
    g.grid[0][99] = 1;
    g.grid[99][99] = 1;
    g.grid[99][0] = 1;
  }

  return std::to_string(g.sum());
}
