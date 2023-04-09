FIND_PACKAGE(GTest REQUIRED)
FIND_PACKAGE(Threads REQUIRED)

INCLUDE_DIRECTORIES(include)

ADD_EXECUTABLE(
        tests
        src/main.cpp
)
TARGET_LINK_LIBRARIES(tests ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${CALC_LIBRARIES} -lstdc++fs)

SET(memcheck_command)

if (WITH_MEMCHECK)
        message("Memcheck enabled")
        SET(memcheck_command ${CMAKE_SOURCE_DIR}/memtest.sh)
else()
        message("Memcheck disabled")
endif()

SET (TEST_COMMAND ${memcheck_command} ${CMAKE_BINARY_DIR}/project/tests/tests)

ADD_TEST(
        NAME BaseTest
        COMMAND ${TEST_COMMAND} ${CMAKE_SOURCE_DIR}/project/tests/data --gtest_filter=-*Extra*
)
ADD_TEST(
        NAME ExtraTest
        COMMAND ${TEST_COMMAND} ${CMAKE_SOURCE_DIR}/project/tests/data --gtest_filter=*Extra*
)