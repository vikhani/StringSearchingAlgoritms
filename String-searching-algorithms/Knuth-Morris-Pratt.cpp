#include "pch.h"
#include "SearchingAlgorithms.h"

vector<size_t> KnuthMorrisPratt(string &haystack,
  const size_t haystack_length,
  const vector<prefix_function> &pref_function,
  const vector<string> &needles,
  const vector<size_t> needle_length)
{
  vector<size_t> result;
  result.reserve(needles.size() * 2);
  for (int j = 0; j< needles.size();++j)
  {
    // if (needle_length > haystack_length) return string::npos;
    for (size_t k = 0, i = 0; i < (unsigned)haystack_length; ++i)
    {
      while ((k > 0) && (needles[j][k] != haystack[i]))
      {
        k = pref_function[j][k - 1];
      }

      if (needles[j][k] == haystack[i])
      {
        k++;
      }

      if (k == needle_length[j])
      {
        result.push_back(i - needle_length[j] + 1);
      }
    }
  }
  return result;
}