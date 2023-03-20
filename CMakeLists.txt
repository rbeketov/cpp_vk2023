CMAKE_MINIMUM_REQUIRED(VERSION 3.10.0)
PROJECT(pars)

OPTION(WITH_MEMCHECK "Run with memcheck" OFF)

SET(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror \
                                                -fsanitize=address,undefined \
                                                -fno-sanitize-recover=all \
                                                -fsanitize-undefined-trap-on-error")
INCLUDE_DIRECTORIES(project/include)
ADD_EXECUTABLE(pars project/src/pars_movies.cpp project/src/main.cpp project/src/pars_input.cpp)

ENABLE_TESTING()

ADD_SUBDIRECTORY(project)
