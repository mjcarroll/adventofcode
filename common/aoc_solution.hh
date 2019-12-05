#ifndef COMMON__AOC_SOLUTION_HH_
#define COMMON__AOC_SOLUTION_HH_

#include "aoc_common.hh"

#include <string>

class BaseSolution
{
public:
  BaseSolution(int year, int day, const std::string & part1, const std::string & part2);

  virtual void test_part1() {}
  virtual std::string part1() {return "";}

  virtual void test_part2() {}
  virtual std::string part2() {return "";}

  int year;
  int day;

  const std::string kInputPath;
  const std::string kInput;

  std::string part1_answer;
  std::string part2_answer;
};

class AocSolution: public BaseSolution {
public:
  AocSolution();
  void test_part1() override; \
  std::string part1() override; \
  void test_part2() override; \
  std::string part2() override; \
};

#define SOLUTION_2(YEAR, DAY) \
AocSolution::AocSolution() : BaseSolution(YEAR, DAY, "", "") {};

#define SOLUTION_3(YEAR, DAY, part1) \
AocSolution::AocSolution() : BaseSolution(YEAR, DAY, part1, "") {};

#define SOLUTION_4(YEAR, DAY, part1, part2) \
AocSolution::AocSolution() : BaseSolution(YEAR, DAY, part1, part2) {};

#define SOLUTION_X(x,A,B,C,D,FUNC, ...)  FUNC

#define SOLUTION(...) \
  SOLUTION_X(,##__VA_ARGS__,\
             SOLUTION_4(__VA_ARGS__),\
             SOLUTION_3(__VA_ARGS__),\
             SOLUTION_2(__VA_ARGS__))


#endif  // COMMON__AOC_SOLUTION_HH_
