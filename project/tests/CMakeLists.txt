cmake_minimum_required(VERSION 3.10)
project(tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -O0")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

file(GLOB SOURCES *.cpp)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES}/src/)
target_include_directories(${PROJECT_NAME} PUBLIC ${LOGIC_INCLUDE_DIRS} ${NET_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${LOGIC_LIBRARIES} ${NET_LIBRARIES} GTest::gtest_main GTest::gmock)


SET(memcheck_command)

if (WITH_MEMCHECK)
    message("Memcheck enabled")
    set(memcheck_command "${CMAKE_SOURCE_DIR}/memtest.sh")
else()
    message("Memcheck disabled")
endif()

SET (TEST_COMMAND ${memcheck_command} ${CMAKE_BINARY_DIR}/project/tests/tests)

message("TEST_COMMAND = ${TEST_COMMAND}")

add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${TEST_COMMAND} ${CMAKE_SOURCE_DIR}/project/tests/)