add_executable(2019_day1 day1.cc)
add_executable(2019_day2 day2.cc)
add_executable(2019_day3 day3.cc)

find_package(OpenCV REQUIRED)

target_link_libraries(2019_day3 ${OpenCV_LIBRARIES})

add_executable(2019_day4 day4.cc)
add_executable(2019_day5 day5.cc)

