#include "aoc_common.hh"
#include "trim.hh"

#include <cassert>

static auto kINPUT = input_path(2019, 5);

enum class OpCode {
  ADD = 1,
  MULT = 2,
  IN = 3,
  OUT = 4,
  JIT = 5,
  JIF = 6,
  LT = 7,
  EQ = 8,
  TERM = 99
};

auto opcode_mode(int opcode)
{
  auto mode_a = opcode/10000 == 1;
  opcode -= mode_a * 10000;
  auto mode_b = opcode/1000 == 1;
  opcode -= mode_b * 1000;
  auto mode_c = opcode/100 == 1;
  opcode -= mode_c * 100;

  return std::make_tuple(opcode, mode_c, mode_b, mode_a);
}

static int program_in = 0;
static int program_out = 0;

int compute_part1(std::vector<int> & input)
{
  bool running = true;
  int ip = 0;

  while(running)
  {
    auto instruction = input[ip];
    auto [opcode, mode_c, mode_b, mode_a] = opcode_mode(instruction);

    auto pos1 = mode_c ? ip + 1 : input[ip + 1];
    auto pos2 = mode_b ? ip + 2 : input[ip + 2];
    auto pos3 = mode_a ? ip + 3 : input[ip + 3];
    auto inst_size = 0;

    switch (static_cast<OpCode>(opcode)) {
      case OpCode::ADD:
        input[pos3] = input[pos1] + input[pos2];
        inst_size = 4;
        break;
      case OpCode::MULT:
        input[pos3] = input[pos1] * input[pos2];
        inst_size = 4;
        break;
      case OpCode::IN:
        input[pos1] = program_in;
        inst_size = 2;
        break;
      case OpCode::OUT:
        program_out = input[pos1];
        inst_size = 2;
        break;
      case OpCode::TERM:
        running = false;
        break;
      default:
        std::cerr << "Unknown OP" << std::endl;
        running = false;
    }

    if (running)
    {
      ip += inst_size;
    }

  }
}

void part1()
{
  assert(opcode_mode(11100) == std::make_tuple(0, true, true, true));
  assert(opcode_mode(10020) == std::make_tuple(20, false, false, true));
  assert(opcode_mode(0) == std::make_tuple(0, false, false, false));

  auto input = read_csv_ints(kINPUT);
  program_in = 1;
  compute_part1(input);
  std::cout << program_out << std::endl;
}

int compute_part2(std::vector<int> & input)
{
  bool running = true;
  int ip = 0;

  while(running)
  {
    auto instruction = input[ip];
    auto [opcode, mode_c, mode_b, mode_a] = opcode_mode(instruction);

    auto pos1 = mode_c ? ip + 1 : input[ip + 1];
    auto pos2 = mode_b ? ip + 2 : input[ip + 2];
    auto pos3 = mode_a ? ip + 3 : input[ip + 3];
    auto inst_size = 0;
    auto jump = false;

    switch (static_cast<OpCode>(opcode)) {
      case OpCode::ADD:
        input[pos3] = input[pos1] + input[pos2];
        inst_size = 4;
        break;
      case OpCode::MULT:
        input[pos3] = input[pos1] * input[pos2];
        inst_size = 4;
        break;
      case OpCode::IN:
        input[pos1] = program_in;
        inst_size = 2;
        break;
      case OpCode::OUT:
        program_out = input[pos1];
        inst_size = 2;
        break;
      case OpCode::JIT:
        if (input[pos1])
        {
          ip = input[pos2];
          jump = true;
        }
        inst_size = 3;
        break;
      case OpCode::JIF:
        if (!input[pos1])
        {
          ip = input[pos2];
          jump = true;
        }
        inst_size = 3;
        break;
      case OpCode::LT:
        input[pos3] = input[pos1] < input[pos2];
        inst_size = 4;
        break;
      case OpCode::EQ:
        input[pos3] = input[pos1] == input[pos2];
        inst_size = 4;
        break;
      case OpCode::TERM:
        running = false;
        break;
      default:
        std::cerr << "Unknown OP" << std::endl;
        running = false;
    }

    if (running && !jump)
    {
      ip += inst_size;
    }
  }
}

void part2()
{
  auto input = read_csv_ints(kINPUT);
  program_in = 5;
  compute_part2(input);
  std::cout << program_out << std::endl;
}

int main(int argc, char** argv)
{
  part1();
  part2();
  return 0;
}
