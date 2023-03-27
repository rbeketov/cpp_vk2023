#pragma once // NOLINT

#include "pars_movies.h"
#include "exceptions.h"

#include <gtest/gtest.h>

#include <sstream>
#include <filesystem>
#include <vector>
#include <memory>


namespace fs = std::filesystem;

extern fs::path glob_test_dir;