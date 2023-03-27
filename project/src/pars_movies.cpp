#include "pars_movies.h"
#include "exceptions.h"

static const char kSeparator = '\t';
static const size_t kNumOfPrimaryTitle = 0;
static const size_t kNumOfTitleId = 0;
static const size_t kNumOfRatings = 1;
static const size_t kSizeResultVec = 2;
static const size_t kNumOfRuTitle = 2;
static const size_t kNumOfPrimaryTitleBasics = 2;

static const std::string kRuTag = "RU";
static const std::string kFlagNonAdult = "0";
static const std::string kMovie = "movie";
static const std::string kNumber = "0123456789";
static const size_t kNumVotesCorrVal = 1000;

static const size_t kSizeBasicsDump = 9;
static const std::string kTconst = "tconst";
static const std::string kTitleType = "titleType";
static const std::string kPrimaryTitle = "primaryTitle";
static const std::string kOriginalTitle = "originalTitle";
static const std::string kIsAdult = "isAdult";
static const std::string kStartYear = "startYear";
static const std::string kEndYear = "endYear";
static const std::string kRuntimeMinutes = "runtimeMinutes";
static const std::string kGenres = "genres";

static const size_t kSizeRatingsDump = 3;
static const std::string kAverageRating = "averageRating";
static const std::string kNumVotes = "numVotes";

static const size_t kSizeAkasDump = 8;
static const std::string kTitleId = "titleId";
static const std::string kOrdering = "ordering";
static const std::string kTitle = "title";
static const std::string kRegion = "region";
static const std::string kLanguage = "language";
static const std::string kTypes = "types";
static const std::string kAttributes = "attributes";
static const std::string kIsOriginalTitle = "isOriginalTitle";

namespace parse {
  // comparators
    auto comparRating = [](Hash& corrMovies, const std::vector<std::string>& words) {
        if (corrMovies.find(words[kNumOfTitleId]) != corrMovies.end() && std::stoul(words[2]) > kNumVotesCorrVal) {
            corrMovies[words[kNumOfTitleId]].push_back(words[kNumOfRatings]);
        }
    };


    auto comparAkas = [](Hash& corrMovies, const std::vector<std::string>& words) {
        if (corrMovies.find(words[kNumOfTitleId]) != corrMovies.end() && words[3] == kRuTag) {
            corrMovies[words[kNumOfTitleId]][kNumOfPrimaryTitle] = words[kNumOfRuTitle];
        }
    };
  // checks
    auto checkBasicsComparator = [](const std::vector<std::string>& words) {
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
    };

    auto checkRatingsComparator = [](const std::vector<std::string>& words) {
        if (words.size() == kSizeRatingsDump
            && words[0] == kTconst
            && words[1] == kAverageRating
            && words[2] == kNumVotes) {
            return true;
        }
        return false;
    };

    auto checkAkasComparator = [](const std::vector<std::string>& words) {
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
    };

  //  main_logic
    ParseTSV::ParseTSV(iStreamPtr tsvBasics, iStreamPtr tsvRatings, iStreamPtr tsvAkas, size_t min)
    : tsvBasics_(tsvBasics), tsvRatings_(tsvRatings), tsvAkas_(tsvAkas), numMinutes(min) {}

    void ParseTSV::parseDump(Hash& corrMovies, std::istream& stream, Comparator comp) {
        std::string buffer = "";
        while (std::getline(stream, buffer)) {
            auto words = strToVec(buffer);
            comp(corrMovies, words);
        }
    }

    void ParseTSV::checkCorrect(std::istream& stream, CheckComparator comp) {
        std::string buffer = "";
        std::getline(stream, buffer);
        auto words = strToVec(buffer);
        if (!comp(words)) {
            throw InvalidDumpTitle();
        }
    }

    std::vector<std::vector<std::string> > ParseTSV::choiceCorrectRecord(const Hash& corrMovies) {
        std::vector<std::vector<std::string> > result;
        for (auto it : corrMovies) {
            if (it.second.size() == kSizeResultVec) {
                std::vector<std::string> tmpVec = {it.second};
                result.push_back(tmpVec);
            }
        }
        return result;
        }

    std::vector<std::vector<std::string> > ParseTSV::getTopCorrectMovie() {
        checkCorrect(*tsvBasics_, checkBasicsComparator);
        checkCorrect(*tsvRatings_, checkRatingsComparator);
        checkCorrect(*tsvAkas_, checkAkasComparator);

        Hash corrMov;
        parseDump(corrMov, *tsvBasics_, [this](Hash& corrMovies, const std::vector<std::string>& words) {
            if (words[4] == kFlagNonAdult
                && words[1] == kMovie
                && words[7].find_first_not_of(kNumber) == std::string::npos
                && std::stoul(words[7]) <= numMinutes) {
                    corrMovies.insert(std::pair<std::string, std::vector<std::string>>(words[kNumOfTitleId], {words[kNumOfPrimaryTitleBasics]}));
            }
        });

        parseDump(corrMov, *tsvRatings_, comparRating);
        parseDump(corrMov, *tsvAkas_,  comparAkas);

        auto data = choiceCorrectRecord(corrMov);

        std::sort(data.begin(), data.end(), [](std::vector<std::string> a, std::vector<std::string> b) {
                                                    return std::stod(a[1]) > std::stod(b[1]);
                                                });
        return data;
    }

  // supp_func
    std::ifstream openFile(const std::string& path) {
        std::ifstream data(path);
        if (!data) {
            throw InvalidPath(path);
        }
        return data;
    }

    std::vector<std::string> strToVec(const std::string& buffer) {
        std::vector<std::string> words;
        std::stringstream streamBuffer(buffer);
        std::string tmpBuffer = "";
        while (std::getline(streamBuffer, tmpBuffer, kSeparator)) {
            words.push_back(tmpBuffer);
        }
        return words;
    }

    void printTopMov(size_t sizeTop, const std::vector<std::vector<std::string> >& data) {
         for (size_t i = 0; i < data.size() && i < sizeTop; ++i) {
            std::cout << data[i][0] << std::endl;
        }
    }

}  // namespace parse
