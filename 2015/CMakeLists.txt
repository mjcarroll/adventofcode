### 2015

register_solution(2015 01)
register_solution(2015 02)
register_solution(2015 03)
register_solution(2015 04)
register_solution(2015 05)
register_solution(2015 06)
register_solution(2015 07)
register_solution(2015 08)
#register_solution(2015 09)
register_solution(2015 10)

# Day 4 needs MD5
find_package(OpenSSL REQUIRED)
target_link_libraries(2015_04 ${OPENSSL_LIBRARIES})
