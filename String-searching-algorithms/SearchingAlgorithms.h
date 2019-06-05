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

#define PRIME 3

typedef vector<long> skiptable_type;
typedef vector<long> occtable_type;
typedef vector<size_t> z_function;
typedef vector<size_t> prefix_function;

const int k = 128, NMAX = 1000000;
struct bohrVertex {
  int nextVertex[k];
  int needleNumber;
  int suffLink;
  int suffGoodLink;
  int auto_move[k];
  int parent;
  bool flag;
  char symb;
};

void CheckAhoCorWork();

size_t KnuthMorrisPratt(const char* haystack,
                        const size_t haystack_length,
                        const prefix_function& pref_function,
                        const char* needle,
                        const size_t needle_length);

prefix_function PrefFunction(const char* needle, const size_t needle_length);

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

size_t RabinKarpwithBernstein(const string haystack,
                              const size_t haystack_length,
                              const string needle,
                              const size_t needle_length);

vector<size_t> RabinKarpwithRolling(string_view haystack,
                                    const vector<string> &needles,
                                    const vector<size_t> &needle_hash);

size_t Bernstein_hash(const string str, const size_t len, size_t pos);

void SortingStrings(vector<string> &strings);

vector<size_t> CheckAhoCorWork(const vector<string> &s, const string &h);

