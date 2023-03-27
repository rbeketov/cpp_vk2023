#pragma once // NOLINT

#include <locale>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <functional>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <iterator>
#include <memory>

using Hash = std::unordered_map<std::string, std::vector<std::string> >;
using Comparator = std::function<void(Hash&, const std::vector<std::string>& words)>;
using CheckComparator = std::function<bool(const std::vector<std::string>&)>;
using iStreamPtr = std::shared_ptr<std::istream>;


namespace parse {

std::vector<std::string> strToVec(const std::string& buffer);
std::ifstream openFile(const std::string& path);
void printTopMov(size_t sizeTop, const std::vector<std::vector<std::string> >& data);

class ParseTSV {
 public:
  ParseTSV(iStreamPtr tsvBasics, iStreamPtr tsvRatings, iStreamPtr tsvAkas, size_t min);
  
  std::vector<std::vector<std::string> > getTopCorrectMovie();

 private:
  iStreamPtr tsvBasics_;
  iStreamPtr tsvRatings_;
  iStreamPtr tsvAkas_;
  size_t numMinutes;

  void checkCorrect(std::istream& stream, CheckComparator comp);
  void parseDump(Hash& corrMovies, std::istream& stream, Comparator comp);
  static std::vector<std::vector<std::string> > choiceCorrectRecord(const Hash& corrMovies);
};
}  // namespace parse
