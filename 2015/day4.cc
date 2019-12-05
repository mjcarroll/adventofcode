#include "aoc_common.hh"
#include "trim.hh"

#include <iomanip>

#include <openssl/md5.h>

static auto kINPUT = input_path(2015, 4);

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
      std::cout << value + std::to_string(count) << std::endl;
      std::cout << dig << std::endl; 
      break;
    }

    count++;

    /*
    if (count % 1000 == 0)
    {
      std::cout << count << std::endl;
    }
    */
  }
  return count;
}

void part1()
{
  assert(compute_part1("abcdef") == 609043);
  assert(compute_part1("pqrstuv") == 1048970);
  std::cout << compute_part1("ckczppom") << std::endl;
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
      std::cout << value + std::to_string(count) << std::endl;
      std::cout << dig << std::endl; 
      break;
    }

    count++;

    /*
    if (count % 1000 == 0)
    {
      std::cout << count << std::endl;
    }
    */
  }
  return count;
}

void part2()
{
  std::cout << compute_part2("ckczppom") << std::endl;
}

int main(int argc, char** argv)
{
  part1();
  part2();
  return 0;
}




