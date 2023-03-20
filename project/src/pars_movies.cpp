#include "pars_movies.h"
#include "exceptions.h"

static const char* kUnsucEx = "Unsuccessful execution of a program";
static const size_t kSizeTop = 10;
static const size_t kSizeResultVec = 10;


namespace parse {
  //  main_logic
    void ParseTSV::parseDump(Hash* corrMovies, const std::string& path, Comparator* comp) {
        std::ifstream data = openFile(path);
        std::string buffer = "";
        std::getline(data, buffer);
        while (std::getline(data, buffer)) {
            std::vector<std::string> words = strToVec(buffer);
            (*comp)(corrMovies, words);
        }
        data.close();
    }

    void ParseTSV::checkCorrect(const std::string& path, CheckComparator* comp) {
        std::ifstream data = openFile(path);
        std::string buffer = "";
        std::getline(data, buffer);
        std::vector<std::string> words = strToVec(buffer);
        if (!(*comp)(words)) {
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
            CheckBasicsComparator checkBasComp;
            checkCorrect(filePathBasics, &checkBasComp);
            CheckRatingsComparator checkRatingComp;
            checkCorrect(filePathRatings, &checkRatingComp);
            CheckAkasComparator checkAkasComp;
            checkCorrect(filePathAkas, &checkAkasComp);

            Hash corrMov;
            ComparBasics comparatorBasic(numMinutes);
            parseDump(&corrMov, filePathBasics, &comparatorBasic);
            ComparRating comparatorRating;
            parseDump(&corrMov, filePathRatings, &comparatorRating);
            ComparAkas comparatorAkas;
            parseDump(&corrMov, filePathAkas, &comparatorAkas);

            std::vector<std::vector<std::string> > data = choiceCorrectRecord(corrMov);

            std::sort(data.begin(), data.end(), [](std::vector<std::string> a, std::vector<std::string> b) {
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
    std::ifstream openFile(const std::string& path) {
        std::ifstream data(path);
        if (data.eof() || data.bad() || !data.is_open()) {
            throw InvalidPath(path);
        }
        return data;
    }

    std::vector<std::string> strToVec(const std::string& buffer) {
        std::vector<std::string> words;
        std::stringstream streamBuffer(buffer);
        std::string tmpBuffer = "";
        while (std::getline(streamBuffer, tmpBuffer, '\t')) {
            words.push_back(tmpBuffer);
        }
        return words;
    }

    void printTopMov(size_t sizeTop, const std::vector<std::vector<std::string> >& data) {
         for (size_t i = 0; i < data.size() && i < sizeTop; ++i) {
            std::cout << data[i][0] << std::endl;
        }
    }



  //  comparators
    void ComparRating::operator() (Hash* corrMovies, const std::vector<std::string>& words) {
        if (corrMovies->find(words[0]) != corrMovies->end() && std::stoul(words[2]) > NumVotesCorrVal) {
            (*corrMovies)[words[0]].push_back(words[1]);
        }
    }

    void ComparBasics::operator() (Hash* corrMovies, const std::vector<std::string>& words) {
        if (words[4] == FlagNonAdult
            && words[1] == Movie
            && words[7].find_first_not_of(Number) == std::string::npos
            && std::stoul(words[7]) <= min) {
                corrMovies->insert(std::pair<std::string, std::vector<std::string>>(words[0], words));
        }
    }

    void ComparAkas::operator() (Hash* corrMovies, const std::vector<std::string>& words) {
        if (corrMovies->find(words[0]) != corrMovies->end() && words[3] == ruTag) {
            (*corrMovies)[words[0]][2] = words[2];
        }
    }


  // checks
    bool CheckBasicsComparator::operator() (const std::vector<std::string>& words) {
        if (words.size() == sizeBasicsDump
            && words[0] == tconst
            && words[1] == titleType
            && words[2] == primaryTitle
            && words[3] == originalTitle
            && words[4] == isAdult
            && words[5] == startYear
            && words[6] == endYear
            && words[7] == runtimeMinutes
            && words[8] == genres) {
            return true;
        }
        return false;
    }

    bool CheckRatingsComparator::operator() (const std::vector<std::string>& words) {
        if (words.size() == sizeRatingsDump
            && words[0] == tconst
            && words[1] == averageRating
            && words[2] == numVotes) {
            return true;
        }
        return false;
    }

    bool CheckAkasComparator::operator() (const std::vector<std::string>& words) {
        if (words.size() == sizeAkasDump
            && words[0] == titleId
            && words[1] == ordering
            && words[2] == title
            && words[3] == region
            && words[4] == language
            && words[5] == types
            && words[6] == attributes
            && words[7] == isOriginalTitle) {
            return true;
        }
        return false;
    }

}  // namespace parse
