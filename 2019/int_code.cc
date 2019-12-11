#include "int_code.hh"
#include "spdlog/spdlog.h"

#include <iostream>

Instruction::Instruction(long instruction)
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

IntCodeCpu::IntCodeCpu(const std::vector<long> & program):
  program(program),
  memory(100000,0)
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

std::vector<long> IntCodeCpu::GetOutput() {
  auto ret = programOutput;
  programOutput = {};
  return ret;
}

void IntCodeCpu::Execute() {
  if (paused) {
    std::cerr << "Tried to execute while paused!" << std::endl;
    return;
  }

  while(running)
  {
    auto instruction = Instruction(memory[instPointer]);

    auto param1 = get_param(instruction.param1, instPointer + 1);
    auto param2 = get_param(instruction.param2, instPointer + 2);
    auto param3 = get_param(instruction.param3, instPointer + 3);
    spdlog::debug("Instruction: {} {} {} {}", kInsName[instruction.op], param1, param2, param3);

    if (instruction.op == OpCode::IN && !inputSet)
    {
      paused = true;
      return;
    }

    bool jump = false;

    auto val1 = param1 < memory.size() ? memory[param1] : -1e6;
    auto val2 = param2 < memory.size() ? memory[param2] : -1e6;

    switch(instruction.op) {
      case OpCode::ADD:
        memory[param3] = memory[param1] + memory[param2];
        spdlog::debug("[{}] <= {} + {} ({})", param3, val1, val2, memory[param3]);
        break;
      case OpCode::MULT:
        memory[param3] = memory[param1] * memory[param2];
        spdlog::debug("[{}] <= {} * {} ({})", param3, val1, val2, memory[param3]);
        break;
      case OpCode::IN:
        memory[param1] = programInput;
        spdlog::debug("{} <= {}", param1, programInput);
        inputSet = false;
        break;
      case OpCode::OUT:
        programOutput.push_back(memory[param1]);
        spdlog::debug("{} => [] ({})", memory[param1], programOutput.size());
        break;
      case OpCode::JIT:
        if (memory[param1]) {
          instPointer = memory[param2];
          spdlog::debug("instPointer: {}", instPointer);
          jump = true;
        }
        break;
      case OpCode::JIF:
        if (!memory[param1]) {
          instPointer = memory[param2];
          spdlog::debug("instPointer: {}", instPointer);
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

    if (paused)
      return;
  }
}

void IntCodeCpu::Reset() {
  instPointer = 0;
  running = true;
  paused = false;
  inputSet = false;
  programInput = 0;
  programOutput = {};
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

