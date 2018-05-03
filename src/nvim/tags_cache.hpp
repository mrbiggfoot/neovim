#ifndef NVIM_TAGS_CACHE_H
#define NVIM_TAGS_CACHE_H

// Ignore tag names with length less than this.
#define MIN_TAG_NAME_LENTH 4

#ifdef __cplusplus
extern "C" {
#endif

// Start updating cache for the tag files.
void update_tags_cache_start(void);

// Update the cache with the specified file.
void update_tags_cache(const char *fname);

// Finish updating cache for the tag files.
void update_tags_cache_finish(void);

// Get fuzzy matches from the tags cache, based on the pattern to match.
// Not ordered. '*matches' needs to be freed, but not individual elements of
// that array.
void get_tags_cache_matches(const char *pattern,
                            const char ***matches,
                            int *num_matches,
                            bool ignore_case);

#ifdef __cplusplus
}
#endif

#endif // NVIM_TAGS_CACHE_H
