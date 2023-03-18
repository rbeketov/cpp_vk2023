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

typedef bool (*checkCorrectComp)(const std::vector<std::string>&);


// Comparator
class Comparator {
 public:
  virtual void operator()(Hash* corrMovies, const std::vector<std::string>& words) = 0;
};

class ComparRating: public Comparator {
 public:
  void operator() (Hash* corrMovies, const std::vector<std::string>& words) override;
 private:
  const size_t NumVotesCorrVal = 1000;
};

class ComparBasics: public Comparator {
 public:
  explicit ComparBasics(size_t minutes):  min(minutes) {}
  void operator() (Hash* corrMovies, const std::vector<std::string>& words) override;
 private:
  const std::string FlagNonAdult = "0";
  const std::string Movie = "movie";
  const std::string Number = "0123456789";
  size_t min = 0;
};

class ComparAkas: public Comparator {
 public:
  void operator() (Hash* corrMovies, const std::vector<std::string>& words) override;
 private:
  const std::string ruTag = "RU";
};

// CheckComparator
class CheckComparator {
 public:
  virtual bool operator() (const std::vector<std::string>& words) = 0;
};

class CheckBasicsComparator: public CheckComparator {
 public:
  bool operator() (const std::vector<std::string>& words) override;
 private:
  const size_t sizeBasicsDump = 9;
  const std::string tconst = "tconst";
  const std::string titleType = "titleType";
  const std::string primaryTitle = "primaryTitle";
  const std::string originalTitle = "originalTitle";
  const std::string isAdult = "isAdult";
  const std::string startYear = "startYear";
  const std::string endYear = "endYear";
  const std::string runtimeMinutes = "runtimeMinutes";
  const std::string genres = "genres";
};

class CheckRatingsComparator: public CheckComparator {
 public:
  bool operator() (const std::vector<std::string>& words) override;
 private:
  const size_t sizeRatingsDump = 3;
  const std::string tconst = "tconst";
  const std::string averageRating = "averageRating";
  const std::string numVotes = "numVotes";
};

class CheckAkasComparator: public CheckComparator {
 public:
  bool operator() (const std::vector<std::string>& words) override;
 private:
  const size_t sizeAkasDump = 8;
  const std::string titleId = "titleId";
  const std::string ordering = "ordering";
  const std::string title = "title";
  const std::string region = "region";
  const std::string language = "language";
  const std::string types = "types";
  const std::string attributes = "attributes";
  const std::string isOriginalTitle = "isOriginalTitle";
};

std::vector<std::string> strToVec(const std::string& buffer);
std::ifstream openFile(const std::string& path);
void printTopMov(size_t sizeTop, const std::vector<std::vector<std::string> >& data);

class ParseTSV {
 public:
  ParseTSV(const std::string& fileBasics, const std::string& fileRatings, const std::string& fileAkas, size_t min)
    : filePathBasics(fileBasics), filePathRatings(fileRatings), filePathAkas(fileAkas), numMinutes(min) {}
  ParseTSV(const ParseTSV& rhs) = default;
  ParseTSV& operator=(const ParseTSV& rhs) = default;
  ~ParseTSV() = default;

  void showTopCorrectMovie();

 private:
  std::string filePathBasics = "";
  std::string filePathRatings = "";
  std::string filePathAkas = "";
  size_t numMinutes = 0;

  void checkCorrect(const std::string& path, CheckComparator* comp);
  void parseDump(Hash* corrMovies, const std::string& path, Comparator* comp);
  static std::vector<std::vector<std::string> > choiceCorrectRecord(const Hash& corrMovies);
};
}  // namespace parse
