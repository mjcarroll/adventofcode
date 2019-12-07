#ifndef INT_CODE_HH_
#define INT_CODE_HH_

#include <map>
#include <vector>

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

enum class ParamMode {
  POSITION = 0,
  IMMEDIATE = 1
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
  { OpCode::TERM, 0 }
};

struct Instruction {
  OpCode op {OpCode::TERM};
  ParamMode param1 {ParamMode::IMMEDIATE};
  ParamMode param2 {ParamMode::IMMEDIATE};
  ParamMode param3 {ParamMode::IMMEDIATE};

  Instruction(int instruction);
  Instruction(int opcode, bool mode_c, bool mode_b, bool mode_a);
};

class IntCodeCpu
{
  public:
    IntCodeCpu();
    IntCodeCpu(const std::vector<int> & program);
    void SetMemory(size_t index, int value);
    int GetMemory(size_t index) const;
    void SetInput(int input);
    int GetOutput();
    void Execute();
    void Reset();

    int get_param(const ParamMode& mode, int arg);

    // Instruction pointer
    size_t instPointer { 0 };
    bool running { true };
    bool paused { false };

    bool inputSet { false };
    int programInput { 0 };

    bool outputSet { false };
    int programOutput { 0 };

    // Store original program for reset
    std::vector<int> program;

    // Mutable working memory
    std::vector<int> memory;
};

#endif
