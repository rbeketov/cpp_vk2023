INCLUDE_DIRECTORIES(include)
ADD_EXECUTABLE(pars src/pars_movies.cpp src/main.cpp src/pars_input.cpp)

ADD_SUBDIRECTORY(tests)