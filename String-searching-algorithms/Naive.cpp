#include "pch.h"
#include "SearchingAlgorithms.h"

size_t NaiveSearch(const string haystack,
                   const size_t haystack_length,
                   const string needle,
                   const size_t needle_length)
{
  for (int i = 0; i < haystack_length-needle_length; i++)
  {
    int j;
    for (j = 0; j < needle_length; j++)
    {
      if (haystack[i + j] != needle[j])
        break;
    }
    if (j == (needle_length))
      return i;
  }
  return -1;
}