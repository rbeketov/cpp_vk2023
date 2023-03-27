#pragma once // NOLINT

#include "pars_movies.h"


std::unique_ptr<parse::ParseTSV> parseInput(int argc, char *argv[]);
