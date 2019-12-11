#include "aoc_solution.hh"

#include "int_code.hh"
#include "point.hh"

#include "spdlog/spdlog.h"

SOLUTION(2019, 11, "2594", "AKERJFHK");

enum class Direction {
  UP = 0,
  LEFT = 1,
  DOWN = 2,
  RIGHT = 3
};


void AocSolution::test_part1()
{
  auto grid = make_grid<int>(6,6,0);
  auto pose = Point(3,3);
  auto dir = Direction::UP;

  auto disp_fn = [&] (auto val, auto row, auto col) {
    if (row == pose.y && col == pose.x)
    {
      switch (dir)
      {
        case Direction::UP: return '^';
        case Direction::LEFT: return '<';
        case Direction::DOWN: return 'V';
        case Direction::RIGHT: return '>';
      }
    }
    else
    {
      return val == 0 ? '.' : '#';
    }
  };

  auto turn_fn = [&](auto turn)
  {
    switch (dir)
    {
      case Direction::UP:
        dir = (turn == 0)? Direction::LEFT : Direction::RIGHT;
        break;
      case Direction::LEFT:
        dir = (turn == 0)? Direction::DOWN: Direction::UP;
        break;
      case Direction::DOWN:
        dir = (turn == 0)? Direction::RIGHT: Direction::LEFT;
        break;
      case Direction::RIGHT:
        dir = (turn == 0)? Direction::UP: Direction::DOWN;
        break;
    }
  };

  auto move_fn = [&]()
  {
    switch (dir)
    {
      case Direction::UP:
        pose += {0, -1};
        break;
      case Direction::LEFT:
        pose += {-1, 0};
        break;
      case Direction::DOWN:
        pose += {0, 1};
        break;
      case Direction::RIGHT:
        pose += {1, 0};
        break;
    }
  };

  std::vector<std::pair<int, int>> inputs = {
    {1, 0}, {0, 0}, {1, 0}, {1, 0}, {0, 1}, {1,0}, {1,0}
  };

  std::set<Point> painted;
  for (auto input: inputs) {
    grid[pose.y][pose.x] = input.first;
    painted.insert(pose);
    turn_fn(input.second);
    move_fn();
    spdlog::debug(display_grid(grid, disp_fn));
  }
  assert(painted.size() == 6);
}

std::string AocSolution::part1()
{
  auto program = split_longs(kInput);
  IntCodeCpu cpu(program);

  auto grid = make_grid<int>(200,200,0);
  auto pose = Point(100,100);
  auto dir = Direction::UP;

  auto disp_fn = [&] (auto val, auto row, auto col) {
    if (row == pose.y && col == pose.x)
    {
      switch (dir)
      {
        case Direction::UP: return '^';
        case Direction::LEFT: return '<';
        case Direction::DOWN: return 'V';
        case Direction::RIGHT: return '>';
      }
    }
    else
    {
      return val == 0 ? '.' : '#';
    }
  };
  spdlog::debug(display_grid(grid, disp_fn));


  auto turn_fn = [&](auto turn)
  {
    switch (dir)
    {
      case Direction::UP:
        dir = (turn == 0)? Direction::LEFT : Direction::RIGHT;
        break;
      case Direction::LEFT:
        dir = (turn == 0)? Direction::DOWN: Direction::UP;
        break;
      case Direction::DOWN:
        dir = (turn == 0)? Direction::RIGHT: Direction::LEFT;
        break;
      case Direction::RIGHT:
        dir = (turn == 0)? Direction::UP: Direction::DOWN;
        break;
    }
  };

  auto move_fn = [&]()
  {
    switch (dir)
    {
      case Direction::UP:
        pose += {0, -1};
        break;
      case Direction::LEFT:
        pose += {-1, 0};
        break;
      case Direction::DOWN:
        pose += {0, 1};
        break;
      case Direction::RIGHT:
        pose += {1, 0};
        break;
    }
  };

  std::set<Point> painted;

  while (cpu.running)
  {
    spdlog::debug("Setting current color: {}", grid[pose.y][pose.x]);
    cpu.SetInput(grid[pose.y][pose.x]);
    cpu.Execute();
    if(!cpu.running) break;
    auto output = cpu.GetOutput();
    assert(output.size() == 2);

    spdlog::debug("Next color: {}", output[0]);
    painted.insert(pose);
    grid[pose.y][pose.x] = output[0];
    spdlog::debug("Next move: {}", output[1]);
    turn_fn(output[1]);
    move_fn();
    //spdlog::debug(display_grid(grid, disp_fn));
  }
  return std::to_string(painted.size());
}

void AocSolution::test_part2()
{
}

std::string AocSolution::part2()
{
  auto program = split_longs(kInput);
  IntCodeCpu cpu(program);

  auto grid = make_grid<int>(8,50,0);
  auto pose = Point(0,0);
  auto dir = Direction::UP;

  grid[pose.y][pose.x] = 1;

  auto disp_fn = [&] (auto val, auto row, auto col) {
    if (row == pose.y && col == pose.x)
    {
      switch (dir)
      {
        case Direction::UP: return '^';
        case Direction::LEFT: return '<';
        case Direction::DOWN: return 'V';
        case Direction::RIGHT: return '>';
      }
    }
    else
    {
      return val == 0 ? '.' : '#';
    }
  };
  spdlog::debug(display_grid(grid, disp_fn));


  auto turn_fn = [&](auto turn)
  {
    switch (dir)
    {
      case Direction::UP:
        dir = (turn == 0)? Direction::LEFT : Direction::RIGHT;
        break;
      case Direction::LEFT:
        dir = (turn == 0)? Direction::DOWN: Direction::UP;
        break;
      case Direction::DOWN:
        dir = (turn == 0)? Direction::RIGHT: Direction::LEFT;
        break;
      case Direction::RIGHT:
        dir = (turn == 0)? Direction::UP: Direction::DOWN;
        break;
    }
  };

  auto move_fn = [&]()
  {
    switch (dir)
    {
      case Direction::UP:
        pose += {0, -1};
        break;
      case Direction::LEFT:
        pose += {-1, 0};
        break;
      case Direction::DOWN:
        pose += {0, 1};
        break;
      case Direction::RIGHT:
        pose += {1, 0};
        break;
    }
  };

  std::set<Point> painted;

  size_t ii = 0;

  while (cpu.running)
  {
    spdlog::debug("Setting current color: {}", grid[pose.y][pose.x]);
    cpu.SetInput(grid[pose.y][pose.x]);
    cpu.Execute();
    if(!cpu.running) break;
    auto output = cpu.GetOutput();
    assert(output.size() == 2);

    spdlog::debug("Next color: {}", output[0]);
    painted.insert(pose);
    grid[pose.y][pose.x] = output[0];
    spdlog::debug("Next move: {}", output[1]);
    turn_fn(output[1]);
    move_fn();
    spdlog::debug(display_grid(grid, disp_fn));
    ii++;
  }

  spdlog::info(display_grid(grid, disp_fn));
  return "AKERJFHK";
}
