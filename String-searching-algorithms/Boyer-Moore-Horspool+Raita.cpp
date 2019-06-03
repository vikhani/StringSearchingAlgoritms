#include "pch.h"
#include "SearchingAlgorithms.h"

size_t BoyerMooreHorspoolRaita(const char* haystack,
                               size_t haystack_length,
                               const occtable_type& occTable,
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

  const unsigned char last_needle_char = needle[needle_length_minus_1];

  size_t haystack_position = 0;
  while (haystack_position <= haystack_length - needle_length)
  {
    const unsigned char occ_char = haystack[haystack_position + needle_length_minus_1];

    if (last_needle_char == occ_char
      && std::memcmp(needle, haystack + haystack_position, needle_length_minus_1) == 0) // оптимизация Райта 
    {
      return haystack_position;
    }
    if (occTable[occ_char] == (unsigned)-1)
      haystack_position += 1;
    else
      haystack_position += occTable[occ_char];
  }
  return haystack_length;
}
