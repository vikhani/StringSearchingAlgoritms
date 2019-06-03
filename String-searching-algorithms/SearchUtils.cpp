#include "pch.h"
#include "SearchingAlgorithms.h"

void SortingStrings(vector<string> &strings)
{
  struct compare {
    bool operator()(const std::string& first, const std::string& second) {
      return first.size() < second.size();
    }
  };
  
  compare comp;
  std::sort(strings.begin(), strings.end(), comp);
}