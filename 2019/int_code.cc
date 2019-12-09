#include "int_code.hh"
#include "spdlog/spdlog.h"

#include <iostream>

Instruction::Instruction(int instruction)
{
  auto mode_a = instruction/10000;
  instruction -= mode_a * 10000;
  auto mode_b = instruction/1000;
  instruction -= mode_b * 1000;
  auto mode_c = instruction/100;
  instruction -= mode_c * 100;

  op = static_cast<OpCode>(instruction);
  param1 = static_cast<ParamMode>(mode_c);
  param2 = static_cast<ParamMode>(mode_b);
  param3 = static_cast<ParamMode>(mode_a);
}

Instruction::Instruction(int opcode, int mode_c, int mode_b, int mode_a):
    op {static_cast<OpCode>(opcode)},
    param1 {static_cast<ParamMode>(mode_c)},
    param2 {static_cast<ParamMode>(mode_b)},
    param3 {static_cast<ParamMode>(mode_a)}
{}

IntCodeCpu::IntCodeCpu() = default;

IntCodeCpu::IntCodeCpu(const std::vector<int> & program):
  program(program.begin(), program.end()),
  memory(10000,0)
{
  for (size_t ii = 0; ii < program.size(); ++ii)
  {
    memory[ii] = program[ii];
  }
}

IntCodeCpu::IntCodeCpu(const std::vector<long> & program):
  program(program),
  memory(10000,0)
{
  for (size_t ii = 0; ii < program.size(); ++ii)
  {
    memory[ii] = program[ii];
  }
}

void IntCodeCpu::SetMemory(size_t index, long value) {
  memory[index] = value;
}

long IntCodeCpu::GetMemory(size_t index) const {
  return memory[index];
}

void IntCodeCpu::SetInput(long input) {
  inputSet = true;
  paused = false;
  programInput = input;
}

long IntCodeCpu::GetOutput() {
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

    /*
    spdlog::debug("{} {}: {} ({}) {} ({}) {} ({})",
        memory[instPointer],
        kInsName[instruction.op],
        param1, memory[param1],
        param2, memory[param2],
        param2, memory[param3]
    );
    */

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
        spdlog::debug("{}", programOutput);
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
      case OpCode::REL:
        relativeBase += memory[param1];
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

long IntCodeCpu::get_param(const ParamMode& mode, long arg)
{
  long ret = 0;
  switch(mode) {
    case ParamMode::IMMEDIATE:
      ret = arg;
      break;
    case ParamMode::POSITION:
      ret = memory[arg];
      break;
    case ParamMode::RELATIVE:
      ret = relativeBase + memory[arg];
      break;
  }
  return ret;
}

