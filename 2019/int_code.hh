#ifndef INT_CODE_HH_
#define INT_CODE_HH_

#include <map>
#include <vector>

enum class OpCode {
  ADD  = 1,
  MULT = 2,
  IN   = 3,
  OUT  = 4,
  JIT  = 5,
  JIF  = 6,
  LT   = 7,
  EQ   = 8,
  REL  = 9,
  TERM = 99
};

enum class ParamMode {
  POSITION = 0,
  IMMEDIATE = 1,
  RELATIVE = 2,
};

static std::map<OpCode, std::string> kInsName =
{
  { OpCode::ADD, "Add" },
  { OpCode::MULT, "Multiply" },
  { OpCode::IN, "Input" },
  { OpCode::OUT, "Output" },
  { OpCode::JIT, "Jump if True" },
  { OpCode::JIF, "Jump if False" },
  { OpCode::LT, "Less Than" },
  { OpCode::EQ, "Equal" },
  { OpCode::REL, "Relative Base" },
  { OpCode::TERM, "Terminate" }
};

static std::map<OpCode, size_t> kInsSize =
{
  { OpCode::ADD, 4 },
  { OpCode::MULT, 4 },
  { OpCode::IN, 2 },
  { OpCode::OUT, 2 },
  { OpCode::JIT, 3 },
  { OpCode::JIF, 3 },
  { OpCode::LT, 4 },
  { OpCode::EQ, 4 },
  { OpCode::REL, 2 },
  { OpCode::TERM, 0 }
};

struct Instruction {
  OpCode op {OpCode::TERM};
  ParamMode param1 {ParamMode::IMMEDIATE};
  ParamMode param2 {ParamMode::IMMEDIATE};
  ParamMode param3 {ParamMode::IMMEDIATE};

  Instruction(long instruction);
  Instruction(int opcode, int mode_c, int mode_b, int mode_a);
};

class IntCodeCpu
{
  public:
    IntCodeCpu();
    IntCodeCpu(const std::vector<long> & program);

    void SetMemory(size_t index, long value);
    long GetMemory(size_t index) const;
    void SetInput(long input);
    std::vector<long> GetOutput();
    void Execute();
    void Reset();

    long get_param(const ParamMode& mode, long arg);

    // Instruction pointer
    size_t instPointer { 0 };
    long relativeBase {0};

    bool running { true };
    bool paused { false };

    bool inputSet { false };
    long programInput { 0 };

    std::vector<long> programOutput;

    // Store original program for reset
    std::vector<long> program;

    // Mutable working memory
    std::vector<long> memory;
};

#endif
