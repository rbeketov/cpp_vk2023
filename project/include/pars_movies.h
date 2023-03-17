#pragma once // NOLINT

#include <cstring>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <iterator>

namespace parse {

    

    typedef std::unordered_map<std::string, std::vector<std::string> > Hash;
    
    typedef void (*comparator)(Hash&, std::vector<std::string>&);
    typedef bool (*checkCorrectComp)(std::vector<std::string>&);



    void compRating(Hash& corrMovies, std::vector<std::string>& words);
    void compBasics(Hash& corrMovies, std::vector<std::string>& words);
    void compAkas(Hash& corrMovies, std::vector<std::string>& words);

    bool checkBasics(std::vector<std::string>& words);
    bool checkRatings(std::vector<std::string>& words);
    bool checkAkas(std::vector<std::string>& words);

    std::vector<std::string> strToVec(std::string& buffer);
    std::ifstream openFile(std::string& path);
    void printTopMov(size_t sizeTop, std::vector<std::vector<std::string> >& data);

    class ParseTSV {
        private:
         std::string filePathBasics = "";
         std::string filePathRatings = "";
         std::string filePathAkas = "";
         static size_t numMinutes;

         void checkCorrect(std::string& path, checkCorrectComp comp);
         void parseDump(Hash& corrMovies, std::string& path, comparator comp);
         static std::vector<std::vector<std::string> > choiceCorrectRecord(const Hash& corrMovies);    

         friend void compBasics(Hash& corrMovies, std::vector<std::string>& words);     

        public:
         
         ParseTSV(std::string& fileBasics, std::string& fileRatings, std::string& fileAkas, size_t min);
         ParseTSV(const ParseTSV& rhs) = default;
         ParseTSV& operator=(const ParseTSV& rhs) = default;
         ~ParseTSV() = default;

         void showTopCorrectMovie();

    };
}  // namespace parse