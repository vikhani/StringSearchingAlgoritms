#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <climits>
#include <fstream>
#include <string>
#include <time.h> 
#include <iomanip>
#include <experimental/filesystem>
#include <sstream>
#include <string_view>

using namespace std;

#define BASE 2

typedef vector<long> skiptable_type;
typedef vector<long> occtable_type;
typedef vector<size_t> z_function;
typedef vector<size_t> prefix_function;

const int k = 128, NMAX = 1000000;
struct bohrVertex {
  size_t nextVertex[k];
  size_t needleNumber;
  size_t suffLink;
  size_t suffGoodLink;
  size_t auto_move[k];
  size_t parent;
  bool flag;
  char symb;
};

vector<size_t> KnuthMorrisPratt(string &haystack,
                        const size_t haystack_length,
                        const vector<prefix_function>& pref_function,
                        const vector<string> &needle,
                        const vector<size_t> needle_length);

prefix_function PrefFunction(const string &needle, const size_t needle_length);

size_t BoyerMoore(const char* haystack,
                  const size_t haystack_length,
                  const occtable_type& occ,
                  const skiptable_type& skip,
                  const char* needle,
                  const size_t needle_length);

occtable_type OccTable(const char* needle, const size_t needle_length);

skiptable_type SkipTable(const char* needle, const size_t needle_length);

size_t BoyerMooreHorspool(const char* haystack,
                          size_t haystack_length,
                          const occtable_type& occTable,
                          const char* needle,
                          const size_t needle_length);

size_t BoyerMooreHorspoolRaita(const char* haystack,
                               size_t haystack_length,
                               const occtable_type& occTable,
                               const char* needle,
                               const size_t needle_length);

size_t NaiveSearch(const string haystack,
                   const size_t haystack_length,
                   const string needle,
                   const size_t needle_length);

inline size_t FastPower(size_t t, size_t k) // возведение t в степень k
{
  size_t res = 1;
  while (k)
  {
    if (k & 1)
      res *= t;
    t *= t;
    k >>= 1;
  }
  return res;
}

vector<size_t> RabinKarpwithBernstein(const string &haystack,
                              const size_t haystack_length,
                              const vector<string> &needle,
                              const vector<size_t> &needle_length);

vector<size_t> RabinKarpwithRolling(string_view haystack,
                                    const vector<string> &needles,
                                    const vector<size_t> &needle_hash);

size_t Bernstein_hash(const string &str, const size_t len, size_t pos);

void SortingStrings(vector<string> &strings);

//vector<size_t> CheckAhoCorWork(const vector<string> &s, const string &h);
void BohrIni(vector<bohrVertex> &bohr);
void AddingStringToBohr(const string& needle, vector<bohrVertex> &bohr);
vector<size_t> FindAllPositions(const string& haystack, vector<bohrVertex> &bohr, vector<size_t> &needleNums);

inline bool ReadingPatterns(string readPatterns, vector<string> &patterns)
{
  const string checkLine = "CVE##########";
  auto posBegin = readPatterns.find(checkLine);
  auto posEnd = posBegin == string::npos ? string::npos : readPatterns.substr(posBegin + checkLine.size(), readPatterns.size()).find(checkLine);

  if ( posEnd != string::npos)
  {
    //string CVEline = readPatterns.substr(posBegin + checkLine.size(), posEnd - 1);
    patterns.push_back(readPatterns.substr(posBegin + checkLine.size(), posEnd - 1));
  }
  else
  {
    return false;
  }
 // for (int i = posEnd + checkLine.size(); i < readPatterns.size();)
  while ( (posEnd + checkLine.size()) < readPatterns.size() )
  {
    readPatterns.erase(0, posEnd + checkLine.size());
    //posBegin = readPatterns.substr(posEnd + checkLine.size(), readPatterns.size()).find(checkLine);
    //if (posBegin != string::npos)
    //{
      posEnd = readPatterns.substr(checkLine.size(), readPatterns.size()).find(checkLine);

      //string CVEline = readPatterns.substr(posBegin + checkLine.size(), posEnd - 1);
      if (posEnd != string::npos && posEnd< readPatterns.size())
      {

        patterns.push_back(readPatterns.substr(checkLine.size(), posEnd - 1));
      }
      else
      {
        break;
      }
   // }
   // i += posEnd+ checkLine.size();
  }
  return true;
}
