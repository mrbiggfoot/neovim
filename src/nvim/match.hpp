#ifndef NVIM_MATCH_H
#define NVIM_MATCH_H

#include "nvim/compl.h"

// Min length of the pattern to trigger custom matches with. Used for
// optimization to reduce the number of candidates in fuzzy search.
#define MIN_CUSTOM_PATTERN_LENGTH 0

// Max number of threads for match score calculation.
#define MAX_NUM_MATCH_THREADS 4

#ifdef __cplusplus
extern "C" {
#endif

bool has_custom_match(const char *needle, const char *haystack,
                      bool ignore_case);

void sort_custom_matches(const char *pattern, compl_T **first_match);

#ifdef __cplusplus
}
#endif

#endif  // NVIM_MATCH_H
