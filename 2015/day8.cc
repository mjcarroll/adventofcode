#include "aoc_common.hh"
#include "trim.hh"

static auto kINPUT = input_path(2015, 8);

auto encode(const std::string& input)
{
  auto stripped = input.substr(1, input.size() - 2);
  std::string output;

  for (auto it = stripped.begin(); it != stripped.end(); ++it)
  {
    auto c = *it;

    if (c == '\\')
    {
      auto next = *++it;
      if (next == 'x') {
        auto msb = *++it;
        auto lsb = *++it; 
        c = static_cast<char>((msb - '0') * 10 + (lsb - '0'));
      }
    }
    output += std::string(1,c);
  }

  return std::make_tuple(input.size(), output.size());
}

void part1()
{
  {
    auto [lit, mem] = encode(R"("")");
    assert(lit == 2);
    assert(mem == 0);
  }
  {
    auto [lit, mem] = encode(R"("abc")");
    assert(lit == 5);
    assert(mem == 3);
  }
  {
    auto [lit, mem] = encode(R"("aaa\"aaa")");
    assert(lit == 10);
    assert(mem == 7);
  }
  {
    auto [lit, mem] = encode(R"("\x27")");
    assert(lit == 6);
    assert(mem == 1);
  }
  {
    // Verify against python's eval.
    auto [lit, mem] = encode(R"("lhyjky\\m\"pvnm\\xmynpxnlhndmahjl")");
    assert(lit == 35);
    assert(mem == 30);
  }


  auto input = split(read_string(kINPUT), '\n');

  int lit_tot = 0;
  int mem_tot = 0;

  for(auto line: input) 
  {
    auto trim_line = trim_copy(line);
    auto [lit, mem] = encode(line);

    lit_tot += lit;
    mem_tot += mem;
  }

  std::cout << lit_tot - mem_tot << std::endl;
}

auto reencode(const std::string & input) {
  std::string encoded = "";
  encoded += '"';

  for (auto c: input) {
    if (c == '"' || c == '\\')
    {
      encoded += "\"";
    }
    encoded += std::string(1, c);
  }

  encoded += '"';
  return std::make_tuple(input.length(), encoded.length());
}


void part2()
{
  {
    auto [lit, mem] = reencode(R"("")");
    assert(lit == 2);
    assert(mem == 6);
  }
  {
    auto [lit, mem] = reencode(R"("abc")");
    assert(lit == 5);
    assert(mem == 9);
  }
  {
    auto [lit, mem] = reencode(R"("aaa\"aaa")");
    assert(lit == 10);
    assert(mem == 16);
  }
  {
    auto [lit, mem] = reencode(R"("\x27")");
    assert(lit == 6);
    assert(mem == 11);
  }

  auto input = split(read_string(kINPUT), '\n');

  int lit_tot = 0;
  int mem_tot = 0;

  for(auto line: input) 
  {
    auto trim_line = trim_copy(line);
    auto [lit, mem] = reencode(line);

    lit_tot += lit;
    mem_tot += mem;
  }

  std::cout << mem_tot - lit_tot << std::endl;

}

int main(int argc, char** argv)
{
  part1();
  part2();
  return 0;
}
