#include "pch.h"
#include "SearchingAlgorithms.h"


prefix_function PrefFunction(const char* needle, const size_t needle_length)
{
  prefix_function pFunc;
  pFunc.reserve(needle_length);
  pFunc.insert(pFunc.begin(), 0); 
  prefix_function::iterator it = pFunc.begin();
  size_t k = 0;
  for (int i = 1; i < /*(unsigned)*/needle_length; ++i) {
    while ((k > 0) && (needle[k] != needle[i]))
      k = pFunc[k - 1];
    if (needle[k] == needle[i])
      ++k;
    it += i;
    pFunc.insert(it, k);
    it = pFunc.begin();
  }
  return pFunc;
}

occtable_type OccTable(const char* needle, const size_t needle_length)
{
  occtable_type occTable(UCHAR_MAX + 1, -1);

  if (needle_length >= 1)
  {
    for (size_t a = 0; a < needle_length - 1; ++a)
      occTable[needle[a]] = needle_length - 1 - a;
  }
  return occTable;
}

int suffix_match(const char *needle, const size_t nlen, const size_t offset, const size_t suffixlen)
{
  if (offset > suffixlen)
  {
    return needle[offset - suffixlen - 1] != needle[nlen - suffixlen - 1]
           && memcmp(needle + nlen - suffixlen, needle + offset - suffixlen, suffixlen) == 0;
  }
  else
  {
    return memcmp(needle + nlen - offset, needle, offset) == 0;
  }
}

skiptable_type SkipTable(const char* needle, const size_t needle_length)
{
  skiptable_type skip_table(needle_length + 1, -1);
  std::vector<size_t> z(needle_length, 0);

  for (size_t j = 1, maxZidx = 0, maxZ = 0; j < needle_length; ++j)
  {
    if (j <= maxZ)
    {
      z[j] = min(maxZ - j + 1, z[j - maxZidx]);
    }

    while (   j + z[j] < needle_length
           && needle[needle_length - 1 - z[j]] == needle[needle_length - 1 - (j + z[j])])
    {
      z[j]++;
    }

    if (j + z[j] - 1 > maxZ)
    {
      maxZidx = j;
      maxZ = j + z[j] - 1;
    }
  }

  for (int j = needle_length - 1; j > 0; j--)
  {
    skip_table[needle_length - z[j]] = j;
  }

  for (int j = 1, r = 0; j <= needle_length - 1; j++)
  {
    if (j + z[j] == needle_length)
    {
      for (; r <= j; r++)
      {
        if (skip_table[r] == needle_length)
        {
          skip_table[r] = j;
        }
      }
    }
  }
  return skip_table;
}
