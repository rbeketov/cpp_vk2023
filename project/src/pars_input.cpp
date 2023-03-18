#include "pars_input.h"
#include "exeption.h"

static const char* kNumber = "0123456789";
static const char* kUnsucEx = "Unsuccessful execution of a program";


parse::ParseTSV* parseInput(int argc, char *argv[]) {
    std::string pathRating = "";
    std::string pathBasics = "";
    std::string pathAkas = "";
    size_t numMinut = 0;
    try {
        if (argc != 5) {
            throw parse::InvalidArgumentsCnt(argc);
        }

        enum posArg {
            BASICS = 0,
            RATING = 1,
            AKAS = 2,
            MIN = 3,
        };

        const struct option long_options[] = {
            { "basicsDump", required_argument, 0, 0},
            { "ratingsDump", required_argument, 0, 0},
            { "akasDump", required_argument, 0, 0},
            { "numMin", required_argument, 0, 0},
            { NULL, no_argument, NULL, 0}
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
    } catch (const parse::ParseException& e) {
        std::cerr << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
    } catch (...) {
        std::cerr << kUnsucEx <<  std::endl;
        std::exit(EXIT_FAILURE);
    }

    parse::ParseTSV* tsvDump = new parse::ParseTSV(pathBasics, pathRating, pathAkas, numMinut);
    return tsvDump;
}

