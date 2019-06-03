#include "pch.h"
#include "SearchingAlgorithms.h"

size_t backwards_match_len(const char* ptr1,
                           const char* ptr2,
                           const size_t strlen,
                           const size_t maxlen,
                           const size_t minlen)
{
  size_t result = minlen;
  while (result < maxlen && ptr1[strlen - 1 - result] == ptr2[strlen - 1 - result])
    ++result;
  return result;
}

size_t BoyerMoore(const char* haystack,
                  const size_t haystack_length,
                  const occtable_type& occ,
                  const skiptable_type& skip,
                  const char* needle,
                  const size_t needle_length)
{
  if (needle_length > haystack_length) return haystack_length;

  if (needle_length == 1)
  {
    const unsigned char* result = (const unsigned char*)std::memchr(haystack, *needle, haystack_length);
    return result ? size_t(result - (unsigned)haystack) : haystack_length;
  }

  const size_t needle_length_minus_1 = needle_length - 1;

  size_t haystack_position = 0;
  while (haystack_position <= haystack_length - needle_length)
  {
    const size_t match_len = backwards_match_len(needle,
                                                 haystack + haystack_position,
                                                 needle_length, 
                                                 needle_length, 
                                                 0);
    if (match_len == needle_length && Check(needle, haystack+haystack_position, needle_length)) return haystack_position;

    const size_t mismatch_position = needle_length_minus_1 - match_len;

    const unsigned char occ_char = haystack[haystack_position + mismatch_position];
    const size_t bcShift = (occ[occ_char] == -1 || occ[occ_char] < match_len) ? match_len : (occ[occ_char] - match_len);  // -- фризится на скобке
    const size_t gcShift = (skip[mismatch_position] == -1) ? 1 : skip[mismatch_position];
    size_t shift = max(gcShift, bcShift);

    haystack_position += shift;
  }
  return haystack_length;
}
