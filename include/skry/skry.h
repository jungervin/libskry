/*
libskry - astronomical image stacking
Copyright (C) 2016 Filip Szczerek <ga.software@yahoo.com>

This file is part of libskry.

Libskry is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Libskry is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with libskry.  If not, see <http://www.gnu.org/licenses/>.

File description:
    Libskry main header.
*/

#ifndef LIB_STACKISTRY_MAIN_HEADER
#define LIB_STACKISTRY_MAIN_HEADER

/*
    Usage notes:

    1. If a function returns a non-const pointer, it is the caller's responsibility
       to free its memory with free() or with an appropriate 'SKRY_free_' function.

    2. All pointer parameters must not be null unless noted otherwise in a comment.

    3. All processing phases operate on the 'SKRY_ImgSequence' object which is
       specified in a call to SKRY_init_img_alignment(). As long as processing is not
       completed, this object must not be modified elsewhere, i.e. no function can be
       called that accepts a non-const pointer to it.

    4. After a call to a XXX_step() function, the current image of the associated
       image sequence is the one that has been just used for processing inside XXX_step().
       That is, the functions perform a "seek next" operation in the img. sequence
       as they start, not as they finish.

    5. All functions that satisfy both the conditions:
         - do not take a 'SKRY_ImgSequence' parameter
         - take an "image index" parameter

       treat the image index as referring only to the active images subset
       of the associated image sequence. E.g. when an image sequence contains 500 images,
       of which only 300 are active, the function:

         SKRY_quality_t SKRY_get_area_quality(const SKRY_QualityEstimation *qual_est,
                                              size_t area_idx, size_t img_idx);

       expects that 0 <= img_idx < 300. The indexing ignores all non-active images
       (even if active ones are not sequential).
*/

#include "defs.h"
#include "image.h"
#include "img_align.h"
#include "imgseq.h"
#include "quality.h"
#include "ref_pt_align.h"
#include "stacking.h"


#define LIBSKRY_MAJOR_VERSION    0
#define LIBSKRY_MINOR_VERSION    0
#define LIBSKRY_SUBMINOR_VERSION 1

/// Must be called before using libskry
enum SKRY_result SKRY_initialize(void);

/// Must be called after finished using libskry
void SKRY_deinitialize(void);

/// Provides a callback for messages generated by libskry.
/** The string pointer and the string's contents passed to the callback
    are valid only for the duration of callback's execution. */
void SKRY_set_logging(unsigned log_event_type_mask,
                      SKRY_log_callback_fn callback_func);

/** Provides a timer function used for timing of processing phases;
    if not used, a default timer is used (with 1-second resolution). */
void SKRY_set_clock_func(SKRY_clock_sec_fn clock_func);

/// May return null
const char *SKRY_get_error_message(enum SKRY_result error);

#endif // LIB_STACKISTRY_MAIN_HEADER
