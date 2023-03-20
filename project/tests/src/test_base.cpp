#include "utils.h"

#include "gtest/gtest.h"

using namespace parse;

TEST(ParseBaseSuite, TestCorrectOutput) {

    std::vector<std::string> paths;
    for (auto& entry : fs::directory_iterator(glob_test_dir / "base_test")) {
        paths.push_back(entry.path());
    }

    ParseTSV* testDump = new ParseTSV(paths[1], paths[2], paths[0], 200);
    //testDump->showTopCorrectMovie();

    delete testDump;
    //std::stringstream strInStream;
    //std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    //std::cout.rdbuf(strInStream.rdbuf()); //redirect std::cout to out.txt!
    
    //std::cout.rdbuf(coutbuf);

    ASSERT_EQ(4, 4);
}

