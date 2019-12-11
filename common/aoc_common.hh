#ifndef COMMON__AOC_COMMON_HH_
#define COMMON__AOC_COMMON_HH_

#include <cassert>

#include <algorithm>
#include <numeric>

#include <string>

#include <map>
#include <set>
#include <vector>

template <typename Container, typename Function>
auto map(const Container& container, Function rowOperation) {
    using ContainerType = typename decltype(container.begin())::value_type;
    using ReturnType = typename std::invoke_result_t<decltype(rowOperation), ContainerType>;
    std::vector<ReturnType> v;
    std::transform(container.begin(), container.end(), std::back_inserter(v), rowOperation);
    return v;
}

template <typename Container>
auto sum(const Container& container) {
  using ContainerType = typename decltype(container.begin())::value_type;
  return std::accumulate(container.begin(), container.end(), 0);
}

template <typename T>
auto make_grid(size_t rows, size_t cols, T init_val)
{
  std::vector<std::vector<T>> grid;
  for(size_t ii = 0; ii < rows; ++ii)
  {
    grid.push_back(std::vector<T>(cols, init_val));
  }
  return grid;
}

template<typename T, typename Function>
auto display_grid(const std::vector<std::vector<T>>& grid,
                  Function cellOperation)
{
  std::string ret;
  size_t rr = 0;
  for (auto row: grid)
  {
    size_t cc = 0;
    for (auto col: row)
    {
      ret += cellOperation(col, rr, cc);
      cc++;
    }
    rr++;
    ret += '\n';
  }
  return ret;
}

int toInt(const std::string& str);

std::string
read_string(const std::string& fname);

std::vector<std::string>
split_string(const std::string& input, char delim);

std::vector<std::string>
split_lines(const std::string& input);

std::vector<int>
split_ints(const std::string& input);

std::vector<long>
split_longs(const std::string& input);

#endif
