#include "pch.h"
#include "SearchingAlgorithms.h"


size_t Bernstein_hash(const string str, const size_t len, size_t pos)
{
  size_t hash = 5381;

  for (size_t i = pos; i < len; ++i)
    hash = hash * pow(33, str[i]);

  return hash;
}

bool Check(const string &s1, const string &s2, const size_t len)
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

    if (currentHayHash == needle_hash && Check(needle, haystack.substr(pos, needle_length), needle_length))
    {
      return pos;
    }
  }

  return -1;
}

size_t RabinKarpwithRolling(const string &haystack,
                            const size_t haystack_length,
                            const vector<string> &needles,
                            const vector<size_t> needle_hash,
                            const vector<size_t> needle_length)
{
 // const int prime = 3;
  size_t needles_num = needles.size();
  vector<size_t> currentHayHash;

  for (size_t i = 0; i < needles.size(); i++)
  {
    currentHayHash.push_back(0);
  }

  for (size_t i = 0; i < needles_num; ++i)
  {
    for (size_t j = 0; j < needle_length[i]; j++)
    {
      currentHayHash[i] = currentHayHash[i] + (haystack[j]) * pow(PRIME, (needle_length[i] - j - 1));
    }
  }

  for (size_t i = 0; i < needles_num; i++)
  {
    if (needle_hash[i] == currentHayHash[i])
    {
      return 0;
    }
  }

  for (size_t i = 0; i < needles_num; ++i)
  {
    for (size_t j = 1; j + needle_length[i] + 1 < haystack_length; ++j)
    {
      currentHayHash[i] = currentHayHash[i] - haystack[j - 1] * pow(PRIME, (needle_length[i] - 1));
      currentHayHash[i] = currentHayHash[i] * PRIME + haystack[j + needle_length[i] - 1];
    //  currentHayHash[i] = currentHayHash[i] + haystack[j + needle_length[i] - 1];

      if (currentHayHash[i] == needle_hash[i] && Check(needles[i], haystack.substr(j, needle_length[i]), needle_length[i]))
      {
        return j;
      }
    }
  }

    return -1;
  }

