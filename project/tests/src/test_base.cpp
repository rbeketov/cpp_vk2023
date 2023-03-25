#include "utils.h"

#include "gtest/gtest.h"

using namespace parse;

TEST(ParseBaseSuite, TestCorrectOutputFirst) {
    std::vector<std::string> paths;

    for (auto& entry : fs::directory_iterator(glob_test_dir / "test_correct_1")) {
        paths.push_back(entry.path());
    }

    ParseTSV testDump(paths[1], paths[2], paths[0], 200);
    auto tmpCout  = std::cout.rdbuf();
    std::stringstream receivedResult;
    std::cout.rdbuf(receivedResult.rdbuf());
    testDump.showTopCorrectMovie();
    std::cout.rdbuf(tmpCout);
    std::string expectedResult = "The Arrival of a Train\nКарменсита\nПолная кружка пива\n";
    ASSERT_EQ(receivedResult.str(), expectedResult);
}


TEST(ParseBaseSuite, TestCorrectOutputSecond) {
    std::vector<std::string> paths;

    for (auto& entry : fs::directory_iterator(glob_test_dir / "test_correct_2")) {
        paths.push_back(entry.path());
    }

    ParseTSV testDump(paths[1], paths[2], paths[0], 200);
    auto tmpCout  = std::cout.rdbuf();
    std::stringstream receivedResult;
    std::cout.rdbuf(receivedResult.rdbuf());
    testDump.showTopCorrectMovie();
    std::cout.rdbuf(tmpCout);
    std::string expectedResult = "";
    ASSERT_EQ(receivedResult.str(), expectedResult);
}


TEST(ParseBaseSuite, TestExceptFirst) {
    std::vector<std::string> paths;

    for (auto& entry : fs::directory_iterator(glob_test_dir / "test_except_1")) {
        paths.push_back(entry.path());
    }

    ParseTSV testDump(paths[1], paths[2], paths[0], 200);
    ASSERT_NO_THROW(testDump.showTopCorrectMovie());
}


TEST(ParseBaseSuite, TestExceptSecond) {
    std::vector<std::string> paths;

    for (auto& entry : fs::directory_iterator(glob_test_dir / "test_except_1")) {
        paths.push_back(entry.path());
    }

    ParseTSV testDump(paths[1], paths[2], paths[0], 200);
    auto tmpCout = std::cerr.rdbuf();
    std::stringstream receivedResult;
    std::cerr.rdbuf(receivedResult.rdbuf());
    testDump.showTopCorrectMovie();
    std::cerr.rdbuf(tmpCout);
    std::string expectedResult = "Invalid dump: " + paths[1] + "\n";
    ASSERT_EQ(receivedResult.str(), expectedResult);
}
