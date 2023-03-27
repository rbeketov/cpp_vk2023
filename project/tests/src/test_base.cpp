#include "utils.h"

#include "gtest/gtest.h"

using namespace parse;

TEST(ParseBaseSuite, TestCorrectOutputFirst) {
    std::vector<std::string> paths;

    for (auto& entry : fs::directory_iterator(glob_test_dir / "test_correct_1")) {
        std::cout << entry.path() << std::endl;
        paths.push_back(entry.path());
    }
    auto pathBas = std::make_shared<std::ifstream>(openFile(paths[1]));
    auto pathRat = std::make_shared<std::ifstream>(openFile(paths[2]));
    auto pathAkas = std::make_shared<std::ifstream>(openFile(paths[0]));
    ParseTSV testDump(pathBas, pathRat, pathAkas, 200);
    auto receivedResultVec = testDump.getTopCorrectMovie();
    std::string receivedResult = "";
    for (auto it : receivedResultVec) {
        receivedResult += it[0];
    }
    std::string expectedResult = "The Arrival of a TrainКарменситаПолная кружка пива";
    ASSERT_EQ(receivedResult, expectedResult);
}


TEST(ParseBaseSuite, TestCorrectOutputSecond) {
     std::vector<std::string> paths;

    for (auto& entry : fs::directory_iterator(glob_test_dir / "test_correct_2")) {
        paths.push_back(entry.path());
    }
    auto pathBas = std::make_shared<std::ifstream>(openFile(paths[1]));
    auto pathRat = std::make_shared<std::ifstream>(openFile(paths[2]));
    auto pathAkas = std::make_shared<std::ifstream>(openFile(paths[0]));
    ParseTSV testDump(pathBas, pathRat, pathAkas, 200);
    auto receivedResultVec = testDump.getTopCorrectMovie();

    ASSERT_TRUE(receivedResultVec.empty());
}


TEST(ParseBaseSuite, TestExceptFirst) {
    std::vector<std::string> paths;

    for (auto& entry : fs::directory_iterator(glob_test_dir / "test_except_1")) {
        paths.push_back(entry.path());
    }
    auto pathBas = std::make_shared<std::ifstream>(openFile(paths[1]));
    auto pathRat = std::make_shared<std::ifstream>(openFile(paths[2]));
    auto pathAkas = std::make_shared<std::ifstream>(openFile(paths[0]));
    ParseTSV testDump(pathBas, pathRat, pathAkas, 200);

    ASSERT_THROW(testDump.getTopCorrectMovie(), ParseException);
}
