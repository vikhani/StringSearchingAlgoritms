#include "pch.h"
#include "SearchingAlgorithms.h"
#include <numeric>


size_t Bernstein_hash(const string str, const size_t len, size_t pos)
{
  size_t hash = 5381;

  for (size_t i = pos; i < len; ++i)
    hash = hash * FastPower(33, str[i]);

  return hash;
}

size_t RabinKarpwithBernstein(const string haystack,
                 const size_t haystack_length,
                 const string needle,
                 const size_t needle_length)
{
  size_t needle_hash = Bernstein_hash(needle, needle_length, 0);

  for (size_t i = 0; i + needle_length - 1 < haystack_length; ++i)
  {
    size_t pos = i;
    size_t currentHayHash = Bernstein_hash(haystack, needle_length+pos , pos);

    if (currentHayHash == needle_hash && needle == string_view { haystack }.substr(pos, needle_length))
    {
      return pos;
    }
  }

  return -1;
}

bool Check(string_view s1, string_view s2, const size_t len)
{
  for (size_t i = 0; i < len; ++i)
  {
    if (s1[i] != s2[i])
    {
      return false;
    }
  }
  return true;
}

vector<size_t> RabinKarpwithRolling(string_view haystack,
                                    const vector<string> &needles,
                                    const vector<size_t> &needle_hash)
{
  vector<size_t> currentHayHash;
  currentHayHash.reserve(needles.size());
  
  std::transform(needles.begin(), needles.end(), back_inserter(currentHayHash),
                 [haystack](string_view needle)
                 {
                   if (haystack.size() < needle.size())
                     return size_t {};

                   size_t j = 0;
                   return std::accumulate(haystack.begin(), haystack.begin() + needle.size(), size_t {},
                                          [&j, needle](auto acc, size_t elem)
                                          {
                                            return acc + elem * FastPower(PRIME, needle.size() - j++ - 1);;
                                          });
                 });

  vector<size_t> result;

  for (size_t i = 0; i < needles.size(); ++i)
  {
    if (needle_hash[i] == currentHayHash[i])
    {
      result.push_back(0);
    }
  }

  for (size_t i = 0; i < needles.size(); ++i)
  {
    string_view needle = needles[i];
    for (size_t j = 1; j + needle.size() <= haystack.size(); ++j)
    {
      currentHayHash[i] -= haystack[j - 1] * FastPower(PRIME, needle.size() - 1);
      currentHayHash[i] = currentHayHash[i] * PRIME + haystack[j + needle.size() - 1];

      if (currentHayHash[i] == needle_hash[i] && haystack.substr(j, std::min(needle.size(), haystack.size() - j)) == needle)
      {
        result.push_back(j);
      }
    }
  }

  return result;
 }
