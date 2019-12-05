#include "int_code.hh"

#include <cassert>

void day5pt1() {
  IntCodeCpu cpu;

  // From day 5, adding parameter modes
  {
    auto ins = Instruction(11101);
    assert(ins.op == OpCode::ADD);
    assert(ins.param1 == ParamMode::IMMEDIATE);
    assert(ins.param2 == ParamMode::IMMEDIATE);
    assert(ins.param3 == ParamMode::IMMEDIATE);
  }
  {
    auto ins = Instruction(1);
    assert(ins.op == OpCode::ADD);
    assert(ins.param1 == ParamMode::POSITION);
    assert(ins.param2 == ParamMode::POSITION);
    assert(ins.param3 == ParamMode::POSITION);
  }
  {
    auto ins = Instruction(1002);
    assert(ins.op == OpCode::MULT);
    assert(ins.param1 == ParamMode::POSITION);
    assert(ins.param2 == ParamMode::IMMEDIATE);
    assert(ins.param3 == ParamMode::POSITION);
  }
}

void day5pt2() {
  {
    // Using position mode, consider whether the input is equal to 8;
    // output 1 (if it is) or 0 (if it is not).
    std::vector<int> program = {3,9,8,9,10,9,4,9,99,-1,8};
    IntCodeCpu cpu(program);
    cpu.SetInput(8);
    cpu.Execute();
    assert(cpu.GetOutput() == 1);

    cpu.Reset();
    cpu.SetInput(9);
    cpu.Execute();
    assert(cpu.GetOutput() == 0);
  }

  {
    // The above example program uses an input instruction to ask for a single number.
    // The program will then output 999 if the input value is below 8,
    // output 1000 if the input value is equal to 8, or
    // output 1001 if the input value is greater than 8.
    std::vector<int> program = {
      3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,
      1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,
      999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99};

    IntCodeCpu cpu(program);
    cpu.SetInput(8);
    cpu.Execute();
    assert(cpu.GetOutput() == 1000);

    cpu.Reset();
    cpu.SetInput(7);
    cpu.Execute();
    assert(cpu.GetOutput() == 999);

    cpu.Reset();
    cpu.SetInput(9);
    cpu.Execute();
    assert(cpu.GetOutput() == 1001);
  }
}

int main(int argc, char** argv)
{
  day5pt1();
  day5pt2();
}
