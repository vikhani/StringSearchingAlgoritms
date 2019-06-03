#include "pch.h"
#include "SearchingAlgorithms.h"

size_t KnuthMorrisPratt(const char* haystack,
                        const size_t haystack_length,
                        const prefix_function& pref_function,
                        const char* needle,
                        const size_t needle_length)
{
  if (needle_length > haystack_length) return haystack_length;
  if (needle_length == 1)
  {
    const unsigned char* result = (const unsigned char*)std::memchr(haystack, *needle, haystack_length);
    return result ? size_t(result - (unsigned)haystack) : haystack_length;
  }

  for (size_t k = 0, i = 0; i < (unsigned)haystack_length; ++i)
  {
    while ((k > 0) && (needle[k] != haystack[i]))
      k = pref_function[k - 1];

    if (needle[k] == haystack[i])
      k++;

    if (k == needle_length)
      return (i - needle_length + 1); 
  }
  return (string::npos);
}