#include "pars_movies.h"
#include "exeption.h"

const static std::string kUnsucEx = "Unsuccessful execution of a program";
const static std::string kFlagNonAdult = "0";
const static std::string kMovie = "movie";
const static std::string kNumber = "0123456789";
const static size_t kNumVotesCorrVal = 1000;
const static std::string kRu = "RU";
const static size_t kSizeTop = 10;
const static size_t kSizeResultVec = 10;

const static size_t kSizeBasicsDump = 9;
const static size_t kSizeRatingsDump = 3;
const static size_t kSizeAkasDump = 8;

const static std::string kTconst = "tconst";
const static std::string kTitleType = "titleType";
const static std::string kPrimaryTitle = "primaryTitle";
const static std::string kOriginalTitle = "originalTitle";
const static std::string kIsAdult = "isAdult";
const static std::string kStartYear = "startYear";
const static std::string kEndYear = "endYear";
const static std::string kRuntimeMinutes = "runtimeMinutes";
const static std::string kGenres = "genres";
const static std::string kAverageRating = "averageRating";
const static std::string kNumVotes = "numVotes";
const static std::string kTitleId = "titleId";
const static std::string kOrdering = "ordering";
const static std::string kTitle = "title";
const static std::string kRegion = "region";
const static std::string kLanguage = "language";
const static std::string kTypes = "types";
const static std::string kAttributes = "attributes";
const static std::string kIsOriginalTitle = "isOriginalTitle";


namespace parse {
        
 //  main_logic  
    ParseTSV::ParseTSV(std::string& fileBasics, std::string& fileRatings, std::string& fileAkas, size_t min)
    : filePathBasics(fileBasics), filePathRatings(fileRatings), filePathAkas(fileAkas) {
        ParseTSV::numMinutes = min;
    }

    void ParseTSV::parseDump(Hash& corrMovies, std::string& path, comparator comp) {
        
        std::ifstream data = openFile(path);
        std::string buffer = "";
        std::getline(data, buffer);
        while(std::getline(data, buffer)) {
            std::vector<std::string> words = strToVec(buffer);
            comp(corrMovies, words);
        }
        data.close();

    }

    void ParseTSV::checkCorrect(std::string& path, checkCorrectComp comp) {
        std::ifstream data = openFile(path);
        std::string buffer = "";
        std::getline(data, buffer);
        std::vector<std::string> words = strToVec(buffer);
        if (!comp(words)) {
            throw InvalidDumpTitle(path);
        }
    }

    std::vector<std::vector<std::string> > ParseTSV::choiceCorrectRecord(const Hash& corrMovies) {
        std::vector<std::vector<std::string> > result;
        for (auto it : corrMovies) {   
            if (it.second.size() == kSizeResultVec) {
                std::vector<std::string> tmpVec;
                tmpVec.clear();
                tmpVec.push_back(it.second[2]);
                tmpVec.push_back(it.second[9]);
                result.push_back(tmpVec);
            }
        }
        return result;
    }

    void ParseTSV::showTopCorrectMovie() {
        try {
            checkCorrect(filePathBasics, checkBasics);
            checkCorrect(filePathRatings, checkRatings);
            checkCorrect(filePathAkas, checkAkas);

            Hash corrMov;
            parseDump(corrMov, filePathBasics, compBasics);
            parseDump(corrMov, filePathRatings, compRating);
            parseDump(corrMov, filePathAkas, compAkas);

            std::vector<std::vector<std::string> > data = choiceCorrectRecord(corrMov);

            std::sort(data.begin(), data.end(), [](std::vector<std::string> a, std::vector<std::string> b)
                                                  {
                                                      return std::stod(a[1]) > std::stod(b[1]);
                                                  });
            printTopMov(kSizeTop, data);

        } catch (const ParseException& e) {
            std::cerr << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        } catch (...) {
            std::cerr << kUnsucEx <<  std::endl;
            std::exit(EXIT_FAILURE);
        }
    }

    

 // supp_func
    std::ifstream openFile(std::string& path) {
        std::ifstream data(path);
        if (data.eof() || data.bad() || !data.is_open()) {
            throw InvalidPath();
        }
        return data;
    }

    std::vector<std::string> strToVec(std::string& buffer) { 
        std::stringstream streamBuffer(buffer);
        std::istream_iterator<std::string> begin(streamBuffer);
        std::istream_iterator<std::string> end;
        std::vector<std::string> words(begin, end);
        return words;
    }

    void printTopMov(size_t sizeTop, std::vector<std::vector<std::string> >& data) {
         for (size_t i = 0; i < data.size() && i < sizeTop; ++i) {
            std::cout << data[i][0] << std::endl;
        }
    }



 //  comparators
    void compRating(Hash& corrMovies, std::vector<std::string>& words) {
        if (corrMovies.find(words[0]) != corrMovies.end() && std::stoul(words[2]) > kNumVotesCorrVal) {
            corrMovies[words[0]].push_back(words[1]);
        }
    }

    void compBasics(Hash& corrMovies, std::vector<std::string>& words) {
        if (words[4] == kFlagNonAdult
            && words[1] == kMovie 
            && words[7].find_first_not_of(kNumber) == std::string::npos
            && std::stoul(words[7]) <= ParseTSV::numMinutes) {
                corrMovies.insert(std::pair<std::string, std::vector<std::string>>(words[0], words));
        }
    }

    void compAkas(Hash& corrMovies, std::vector<std::string>& words) {
        if (corrMovies.find(words[0]) != corrMovies.end() && words[3] == kRu) {
            corrMovies[words[0]][2] = words[2];
        }
    }



 //  checks
    bool checkBasics(std::vector<std::string>& words) {
        if (words.size() == kSizeBasicsDump 
            && words[0] == kTconst
            && words[1] == kTitleType
            && words[2] == kPrimaryTitle
            && words[3] == kOriginalTitle
            && words[4] == kIsAdult
            && words[5] == kStartYear
            && words[6] == kEndYear
            && words[7] == kRuntimeMinutes
            && words[8] == kGenres) {
            return true;
        }
        return false;
        
    }
    bool checkRatings(std::vector<std::string>& words) {
        if (words.size() == kSizeRatingsDump
            && words[0] == kTconst
            && words[1] == kAverageRating
            && words[2] == kNumVotes) {
            return true;
        }
        return false;
    }
    bool checkAkas(std::vector<std::string>& words) {
        if (words.size() == kSizeAkasDump
            && words[0] == kTitleId
            && words[1] == kOrdering
            && words[2] == kTitle
            && words[3] == kRegion
            && words[4] == kLanguage
            && words[5] == kTypes
            && words[6] == kAttributes
            && words[7] == kIsOriginalTitle) {
            return true;
        }
        return false;
    }


}  // namespace parse