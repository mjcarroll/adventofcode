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

int toInt(const std::string& str);

std::string
read_string(const std::string& fname);

std::vector<std::string>
split_string(const std::string& input, char delim);

std::vector<std::string>
split_lines(const std::string& input);

std::vector<int>
split_ints(const std::string& input);

#endif
