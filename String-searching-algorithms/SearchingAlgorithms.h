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

using namespace std;

#define PRIME 3

typedef vector<long> skiptable_type;
typedef vector<long> occtable_type;
typedef vector<size_t> z_function;
typedef vector<size_t> prefix_function;

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

size_t RabinKarpwithBernstein(const string haystack,
                              const size_t haystack_length,
                              const string needle,
                              const size_t needle_length);

size_t RabinKarpwithRolling(const string &haystack,
                            const size_t haystack_length,
                            const vector<string> &needles,
                            const vector<size_t> needle_hash,
                            const vector<size_t> needle_length);

size_t Bernstein_hash(const string str, const size_t len, size_t pos);

bool Check(const string &s1, const string &s2, const size_t len);

void SortingStrings(vector<string> &strings);
