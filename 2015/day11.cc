#include "aoc_solution.hh"
#include "trim.hh"

#include "spdlog/spdlog.h"

SOLUTION(2015, 11, "vzbxxyzz");

std::string increment(const std::string& input)
{
  std::string ret(input.begin(), input.end());
    
  ret[input.size() - 1]++;
  bool needs_digit = false;

  for (int ii = input.size() - 1; ii >= 0; --ii)
  {
    if (ret[ii] > 'z')
    {
      ret[ii] -= 26;

      if (ii == 0)
      {
        needs_digit = true;
      } else {
        ret[ii-1]++;
      }
    }
  }

  if (needs_digit)
    ret = "a" + ret;

  return ret;
}

bool has_iol(const std::string& input)
{
  return input.find('i') != std::string::npos ||
         input.find('o') != std::string::npos ||
         input.find('l') != std::string::npos;
}

bool has_asc(const std::string& input)
{
  for(size_t ii = 0; ii < input.length(); ++ii)
  {
    if ((input[ii] + 1 == input[ii+1]) &&
        (input[ii] + 2 == input[ii+2]))
    {
      return true;
    }
  }
  return false;
}

bool has_doubles(const std::string& input)
{
  std::vector<int> pos;

  for (size_t ii = 0; ii < 26; ++ii)
  {
    auto check = 'a' + ii;
    auto search = std::string(2, check);
    auto it = input.find(search.c_str());

    if (it != std::string::npos) {
      pos.push_back(it);
    }
  }

  return pos.size() > 1;
}

bool passes(const std::string& input)
{
  return has_doubles(input) && has_asc(input) && !has_iol(input);
}

void AocSolution::test_part1()
{
  assert(increment("xx") == "xy");
  assert(increment("xy") == "xz");
  assert(increment("xz") == "ya");
  assert(increment("zzz") == "aaaa");

  assert(has_iol("asdfi") == true);
  assert(has_asc("abc") == true);
  assert(has_asc("abd") == false);
  assert(has_asc("xyz") == true);

  assert(has_doubles("aacd") == false);
  assert(has_doubles("aabb") == true);
  assert(has_doubles("aacdaa") == false);
  assert(has_doubles("aaa") == false);

  assert(passes("hijklmmn") == false);
  assert(passes("abbceffg") == false);
  assert(passes("abbcegjk") == false);

  assert(passes("abcdffaa") == true);
  assert(passes("ghjaabcc") == true);

  {
    auto password = std::string("abcdefgh");
    while(true)
    {
      password = increment(password);
      if(passes(password))
      {
        break;
      }
    }
    assert(password == "abcdffaa");
  }
  {
    auto password = std::string("ghijklmn");
    while(true)
    {
      password = increment(password);
      if(passes(password))
      {
        break;
      }
    }
    assert(password == "ghjaabcc");
  }
}


std::string AocSolution::part1()
{
  auto password = trim_copy(kInput);
  while(!passes(password))
  {
    password = increment(password);
  }

  return password;
}

void AocSolution::test_part2()
{

}

std::string AocSolution::part2()
{
  return "";
}
