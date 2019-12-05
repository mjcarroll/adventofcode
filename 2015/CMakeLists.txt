add_executable(2015_day1 day1.cc)
add_executable(2015_day2 day2.cc)
add_executable(2015_day3 day3.cc)
add_executable(2015_day4 day4.cc)
find_package(OpenSSL REQUIRED)
target_link_libraries(2015_day4 ${OPENSSL_LIBRARIES})

add_executable(2015_day5 day5.cc)
add_executable(2015_day6 day6.cc)
add_executable(2015_day7 day7.cc)
add_executable(2015_day8 day8.cc)
add_executable(2015_day9 day9.cc)

add_executable(2015_day10 day10.cc)
