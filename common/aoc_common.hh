#ifndef AOC_COMMON_HH_
#define AOC_COMMON_HH_

#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <vector>

#include "trim.hh"
#include "aoc_config.hh"

auto input_path(int year, int day)
{
  std::string inp{AOC_PROJECT_DIR};
  inp += "/"
      + std::to_string(year)
      + "/input/"
      + std::to_string(day)
      + ".txt";
  return inp;
}


auto read_ints(const std::string& fname)
{
  std::vector<int> v;
  std::ifstream ifs(fname);
  if (ifs)
  {
    std::copy(std::istream_iterator<int>(ifs),
              std::istream_iterator<int>(),
              std::back_inserter(v));
  }
  return v;
}

auto read_string(const std::string& fname)
{
  std::ifstream ifs(fname);
  std::stringstream buffer;
  buffer << ifs.rdbuf();
  return buffer.str();
}

auto read_strings(const std::string& fname)
{
  std::vector<std::string> v;
  std::ifstream ifs(fname);
  if (ifs)
  {
    std::copy(std::istream_iterator<std::string>(ifs),
              std::istream_iterator<std::string>(),
              std::back_inserter(v));
  }
  return v;
}

std::vector<std::string> split(const std::string& s, char delimiter)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}

auto read_csv_ints(const std::string& fname)
{
  auto s = read_string(fname);
  auto vals = split(s, ',');
  std::vector<int> output;
  for (auto val: vals) 
  {
    output.push_back(atoi(val.c_str()));
  }
  return output;
}

auto read_lines(const std::string& fname)
{
  auto str = read_string(fname);
  auto lines = split(str, '\n');

  std::vector<std::string> output;
  for (auto line: lines)
  {
    trim(line);
    output.push_back(line);
  }
  return output;
}


#endif
