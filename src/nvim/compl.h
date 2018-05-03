#ifndef NVIM_COMPL_H
#define NVIM_COMPL_H

#include "nvim/types.h"

/*
 * Array indexes used for cptext argument of ins_compl_add().
 */
#define CPT_ABBR        0   // "abbr"
#define CPT_MENU        1   // "menu"
#define CPT_KIND        2   // "kind"
#define CPT_INFO        3   // "info"
#define CPT_USER_DATA   4   // "user data"
#define CPT_COUNT       5   // Number of entries

/*
 * Structure used to store one match for insert completion.
 */
typedef struct compl_S compl_T;
struct compl_S {
  compl_T     *cp_next;
  compl_T     *cp_prev;
  char_u      *cp_str;          /* matched text */
  char cp_icase;                /* TRUE or FALSE: ignore case */
  char_u      *(cp_text[CPT_COUNT]);    /* text for the menu */
  char_u      *cp_fname;        /* file containing the match, allocated when
                                 * cp_flags has FREE_FNAME */
  int cp_flags;                 /* ORIGINAL_TEXT, CONT_S_IPOS or FREE_FNAME */
  int cp_number;                /* sequence number */
  bool        has_match;        /* used in fuzzy matching */
};

#define ORIGINAL_TEXT   (1)   /* the original text when the expansion begun */
#define FREE_FNAME      (2)

#endif // NVIM_COMPL_H
