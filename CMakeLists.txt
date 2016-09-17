project(libjwtpp)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_library(jwtpp SHARED
  src/jwt.cpp)
