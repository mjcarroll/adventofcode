#include "aoc_solution.hh"
#include "trim.hh"

#include <openssl/md5.h>

#include <sstream>
#include <iomanip>
#include <iostream>

SOLUTION(2015, 4, "117946", "3938038");

const std::string digest(const std::string& msg)
{
  unsigned char result[MD5_DIGEST_LENGTH];
  MD5((unsigned char*)msg.data(), msg.size(), result);

  std::ostringstream sout;
  sout << std::hex << std::setfill('0');
  for (auto c: result) sout << std::setw(2) << (int) c;
  return sout.str();
}

int compute_part1(const std::string& value)
{
  int count = 0;
  bool found = false;

  while(!found)
  {
    auto msg = value + std::to_string(count);
    auto dig = digest(msg);

    if(dig[0] == '0' &&
       dig[1] == '0' &&
       dig[2] == '0' &&
       dig[3] == '0' &&
       dig[4] == '0')
    {
      found = true;
      break;
    }
    count++;
  }
  return count;
}

int compute_part2(const std::string& value)
{
  int count = 0;
  bool found = false;

  while(!found)
  {
    auto msg = value + std::to_string(count);
    auto dig = digest(msg);

    if(dig[0] == '0' &&
       dig[1] == '0' &&
       dig[2] == '0' &&
       dig[3] == '0' &&
       dig[4] == '0' &&
       dig[5] == '0')
    {
      found = true;
      break;
    }

    count++;
  }
  return count;
}

void AocSolution::test_part1()
{
  assert(compute_part1("abcdef") == 609043);
  assert(compute_part1("pqrstuv") == 1048970);
}

std::string AocSolution::part1()
{
  return std::to_string(compute_part1(trim_copy(kInput)));
}

void AocSolution::test_part2()
{
}

std::string AocSolution::part2()
{
  return std::to_string(compute_part2(trim_copy(kInput)));
}

