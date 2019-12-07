#include "int_code.hh"

#include <iostream>

Instruction::Instruction(int instruction)
{
  auto mode_a = instruction/10000 == 1;
  instruction -= mode_a * 10000;
  auto mode_b = instruction/1000 == 1;
  instruction -= mode_b * 1000;
  auto mode_c = instruction/100 == 1;
  instruction -= mode_c * 100;

  op = static_cast<OpCode>(instruction);
  param1 = static_cast<ParamMode>(mode_c);
  param2 = static_cast<ParamMode>(mode_b);
  param3 = static_cast<ParamMode>(mode_a);
}

Instruction::Instruction(int opcode, bool mode_c, bool mode_b, bool mode_a):
    op {static_cast<OpCode>(opcode)},
    param1 {static_cast<ParamMode>(mode_c)},
    param2 {static_cast<ParamMode>(mode_b)},
    param3 {static_cast<ParamMode>(mode_a)}
{}

IntCodeCpu::IntCodeCpu() = default;

IntCodeCpu::IntCodeCpu(const std::vector<int> & program):
  program(program),
  memory(program)
{
}

void IntCodeCpu::SetMemory(size_t index, int value) {
  memory[index] = value;
}

int IntCodeCpu::GetMemory(size_t index) const {
  return memory[index];
}

void IntCodeCpu::SetInput(int input) {
  inputSet = true;
  paused = false;
  programInput = input;
}

int IntCodeCpu::GetOutput() {
  outputSet = false;
  return programOutput;
}

void IntCodeCpu::Execute() {
  if (paused) {
    std::cerr << "Tried to execute while paused!" << std::endl;
    return;
  }

  while(running)
  {
    auto instruction = Instruction(memory[instPointer]);

    if (instruction.op == OpCode::IN && !inputSet)
    {
      paused = true;
      return;
    }

    auto param1 = get_param(instruction.param1, instPointer + 1);
    auto param2 = get_param(instruction.param2, instPointer + 2);
    auto param3 = get_param(instruction.param3, instPointer + 3);
    bool jump = false;

    switch(instruction.op) {
      case OpCode::ADD:
        memory[param3] = memory[param1] + memory[param2];
        break;
      case OpCode::MULT:
        memory[param3] = memory[param1] * memory[param2];
        break;
      case OpCode::IN:
        memory[param1] = programInput;
        inputSet = false;
        break;
      case OpCode::OUT:
        programOutput = memory[param1];
        outputSet = true;
        break;
      case OpCode::JIT:
        if (memory[param1]) {
          instPointer = memory[param2];
          jump = true;
        }
        break;
      case OpCode::JIF:
        if (!memory[param1]) {
          instPointer = memory[param2];
          jump = true;
        }
        break;
      case OpCode::LT:
        memory[param3] = memory[param1] < memory[param2];
        break;
      case OpCode::EQ:
        memory[param3] = memory[param1] == memory[param2];
        break;
      case OpCode::TERM:
        running = false;
        break;
    }

    if (running && !jump)
    {
      instPointer += kInsSize[instruction.op];
    }
  }
}

void IntCodeCpu::Reset() {
  instPointer = 0;
  running = true;
  paused = false;
  inputSet = false;
  programInput = 0;
  outputSet = false;
  programOutput = 0;
  memory = {program.begin(), program.end()};
}

int IntCodeCpu::get_param(const ParamMode& mode, int arg)
{
  return mode == ParamMode::POSITION ? memory[arg] : arg;
}
