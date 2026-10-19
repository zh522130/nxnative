// The four face buttons of a physical controller -> game keys: mapped by the letter printed on the button glyph (press whichever letter the
// button button legend shows). Pure function, used by the front end dm_gamepad.m, checked by the host unit test tests/t_padmap.c.
//   The four face buttons given by the system (GameController) are defined by position, not by the letter on the button glyph:
//   buttonA bottom, buttonB right, buttonX left, buttonY top.
//   - Nintendo controllers (Switch Pro, Joy-Con): the glyphs are right A, bottom B, top X, left Y -- identical to the Switch as is.
//   - PlayStation (DualSense, DualShock): no ABXY letters. The game draws Switch glyphs, so these use the same positions (bottom B, right A, top X, left Y).
//   - Xbox controllers: the glyphs are bottom A, right B, left X, top Y.
//   - Unrecognized types: laid out by the Xbox positions (bottom button = confirm).
//   The type is recognized from the two strings given by the system, product category and vendor name (case-insensitive):
//   switch / nintendo / joy-con, or dualsense / dualshock / playstation, are the Switch positions; anything else is Xbox.
//   (The vendor name of the Switch Pro is "Pro Controller", which has none of these words, so it must be recognized by the product category
//   "Switch Pro Controller"; that is why both strings are checked.)
#pragma once
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include "dm_input.h"
enum { DM_PADKIND_XBOX = 0, DM_PADKIND_NINTENDO = 1 };
static inline int dm_padmap_has(const char *s, const char *w) { size_t n = strlen(w); for (; s && *s; s++) if (!strncasecmp(s, w, n)) return 1; return 0; }
static inline int dm_padmap_kind(const char *category, const char *vendor) {
    static const char *const k[] = { "switch", "nintendo", "joy-con", "dualsense", "dualshock", "playstation" };
    for (unsigned i = 0; i < sizeof k / sizeof *k; i++) if (dm_padmap_has(category, k[i]) || dm_padmap_has(vendor, k[i])) return DM_PADKIND_NINTENDO;
    return DM_PADKIND_XBOX;
}
static inline uint64_t dm_padmap_face(int kind, int south, int east, int west, int north) {   // The four parameters = whether the bottom / right / left / top button is held
    if (kind == DM_PADKIND_NINTENDO) return (east ? DM_BTN_A : 0) | (south ? DM_BTN_B : 0) | (north ? DM_BTN_X : 0) | (west ? DM_BTN_Y : 0);
    return (south ? DM_BTN_A : 0) | (east ? DM_BTN_B : 0) | (west ? DM_BTN_X : 0) | (north ? DM_BTN_Y : 0);
}
