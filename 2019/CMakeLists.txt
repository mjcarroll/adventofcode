### 2019

register_solution(2019 01)
register_solution(2019 02)
register_solution(2019 03)
register_solution(2019 04)
register_solution(2019 05)
register_solution(2019 06)
register_solution(2019 07)
register_solution(2019 08)

# IntCode Computer from 2019
add_library(intcode int_code.cc)
add_executable(test_int_code test_int_code.cc)
target_link_libraries(test_int_code intcode)

# Link challenges that require the intcode cpu
target_link_libraries(2019_02 intcode)
target_link_libraries(2019_05 intcode)
target_link_libraries(2019_07 intcode)
