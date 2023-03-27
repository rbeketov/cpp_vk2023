CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(tests_parse)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -fPIC -O0")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )


FILE(GLOB SOURCES *.cpp)

INCLUDE(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

INCLUDE_DIRECTORIES(include ../include)

SET(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

FIND_PACKAGE(GTest REQUIRED)

ADD_EXECUTABLE(
        ${PROJECT_NAME}
        src/main.cpp
        src/test_base.cpp
        ../src/pars_input.cpp
        ../src/pars_movies.cpp
)


TARGET_LINK_LIBRARIES(${PROJECT_NAME} GTest::gtest_main GTest::gmock)


SET(memcheck_command)

IF (WITH_MEMCHECK)
        MESSAGE("Memcheck enabled")
        SET(memcheck_command ${CMAKE_SOURCE_DIR}/memtest.sh)
ELSE()
        MESSAGE("Memcheck disabled")
ENDIF()

SET (TEST_COMMAND ${memcheck_command} ${CMAKE_BINARY_DIR}/project/tests/tests_parse)

ADD_TEST(
        NAME BaseTest
        COMMAND ${TEST_COMMAND} ${CMAKE_SOURCE_DIR}/project/tests/data
)