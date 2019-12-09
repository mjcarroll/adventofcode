#include "aoc_common.hh"

#include <fstream>
#include <iostream>
#include <sstream>

std::string read_string(const std::string& fname)
{
  std::ifstream ifs(fname);
  std::stringstream buffer;
  buffer << ifs.rdbuf();
  return buffer.str();
}

std::vector<std::string>
split_string(const std::string& input, char delim)
{
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(input);
  while (std::getline(tokenStream, token, delim))
  {
    tokens.push_back(token);
  }
  return tokens;
}

std::vector<std::string>
split_lines(const std::string& input)
{
  return split_string(input, '\n');
}

int toInt(const std::string& val) {
  return atoi(val.c_str());
}

long toLong(const std::string& val) {
  return atol(val.c_str());
}

std::vector<int>
split_ints(const std::string& input)
{
  return map(split_string(input, ','), toInt);
}

std::vector<long>
split_longs(const std::string& input)
{
  return map(split_string(input, ','), toLong);
}

