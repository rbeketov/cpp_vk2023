#include "pars_movies.h"
#include "pars_input.h"


int main(int argc, char *argv[]) {
    parse::ParseTSV* dump = parseInput(argc, argv);
    dump->showTopCorrectMovie();

    delete dump;

    return 0;
}
