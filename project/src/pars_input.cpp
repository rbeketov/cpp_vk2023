#include "pars_input.h"
#include "exceptions.h"
#include <getopt.h>
#include <iostream>
#include <memory>

static const char* kNumber = "0123456789";
static const int correctCntArgc = 5;

enum posArg {
    BASICS = 0,
    RATING = 1,
    AKAS = 2,
    MIN = 3,
};


std::unique_ptr<parse::ParseTSV> parseInput(int argc, char *argv[]) {
    std::string pathRating = "";
    std::string pathBasics = "";
    std::string pathAkas = "";
    size_t numMinut = 0;

    if (argc != correctCntArgc) {
        throw parse::InvalidArgumentsCnt(argc);
    }

    const option long_options[] = {
        { "basicsDump", required_argument, nullptr, 0},
        { "ratingsDump", required_argument, nullptr, 0},
        { "akasDump", required_argument, nullptr, 0},
        { "numMin", required_argument, nullptr, 0},
        { nullptr, no_argument, nullptr, 0}
    };

    for (int i = 0; i < argc-1; ++i) {
        int option_index = 0;
        if (getopt_long(argc, argv, "", long_options, &option_index)) {
            throw parse::InvalidArguments();
        }
        switch (option_index) {
        case BASICS: {
            pathBasics = optarg;
            break;
        }
        case RATING: {
            pathRating = optarg;
            break;
        }
        case AKAS: {
            pathAkas = optarg;
            break;
        }
        case MIN: {
            if ((static_cast<std::string>(optarg)).find_first_not_of(kNumber) != std::string::npos) {
                throw parse::InvalidArgumentsNum();
            }
            numMinut = std::stoul(static_cast<std::string>(optarg));
            break;
        }
        default:
            throw parse::InvalidArguments();
        }
    }

    auto tsvBasics = std::make_shared<std::ifstream>(parse::openFile(pathBasics));
    auto tsvRatings = std::make_shared<std::ifstream>(parse::openFile(pathRating));
    auto tsvAkas = std::make_shared<std::ifstream>(parse::openFile(pathAkas));

    return std::make_unique<parse::ParseTSV>(parse::ParseTSV(tsvBasics, tsvRatings, tsvAkas, numMinut));
}

