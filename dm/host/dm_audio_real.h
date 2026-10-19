// Speakers are on when DM_AUDIO is set to a non-zero value, otherwise on iPhone, otherwise when a Mac window (DM_WINDOW) is open.
#pragma once
#include <stdlib.h>
#include <TargetConditionals.h>
static inline int dm_audio_real(void) {
    const char *e = getenv("DM_AUDIO");
    if (e) return atoi(e) != 0;
    if (TARGET_OS_IPHONE) return 1;
    return getenv("DM_WINDOW") != NULL;
}
