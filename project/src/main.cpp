#include "pars_movies.h"
#include "pars_input.h"
#include "exceptions.h"

static const std::string kUnsucEx = "Unsuccessful execution of a program";
static const size_t kSizeTop = 10;

int main(int argc, char *argv[]) {
    try {
        auto dump = parseInput(argc, argv);
        auto data = dump->getTopCorrectMovie();
        parse::printTopMov(kSizeTop, data);

    } catch (const parse::ParseException& e) {
        std::cerr << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << kUnsucEx <<  std::endl;
    }
    return 0;
}
