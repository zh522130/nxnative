// Real-audio decision (dm_audio_real.h). Calls dm_audio_real(); the four cases set the environment and check the return.
#include <stdio.h>
#include <stdlib.h>
#include "../dm_audio_real.h"
static int checks, fails;
#define CHECK(c, ...) do { checks++; if (c) printf("  ✓ "); else { fails++; printf("  ✗ "); } printf(__VA_ARGS__); printf("\n"); } while (0)
int main(void) {
    setenv("DM_WINDOW", "1", 1); unsetenv("DM_AUDIO");
    CHECK(dm_audio_real() == 1, "DM_WINDOW set and DM_AUDIO unset → 1");
    unsetenv("DM_WINDOW"); unsetenv("DM_AUDIO");
    CHECK(dm_audio_real() == 0, "both unset → 0");
    setenv("DM_WINDOW", "1", 1); setenv("DM_AUDIO", "0", 1);
    CHECK(dm_audio_real() == 0, "DM_AUDIO=0 with DM_WINDOW set → 0");
    unsetenv("DM_WINDOW"); setenv("DM_AUDIO", "1", 1);
    CHECK(dm_audio_real() == 1, "DM_AUDIO=1 and DM_WINDOW unset → 1");
    printf("== %d 项，失败 %d ==\n", checks, fails);
    return fails != 0;
}
