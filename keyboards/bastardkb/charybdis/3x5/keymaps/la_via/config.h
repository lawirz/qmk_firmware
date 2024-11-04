/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#ifdef VIA_ENABLE
/* VIA configuration. */
#    define DYNAMIC_KEYMAP_LAYER_COUNT 9
#endif // VIA_ENABLE

/* Disable unused features. */
#define NO_ACTION_ONESHOT

/* Charybdis-specific features. */

#ifdef POINTING_DEVICE_ENABLE
// Automatically enable the pointer layer when moving the trackball.  See also:
// - `CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS`
// - `CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD`
/* #define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE */
/* #define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 300 */
/* #define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 1 */
#endif // POINTING_DEVICE_ENABLE#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

// how long until tap becomes hold
#define TAPPING_TERM 140
/* #define TAPPING_TERM 150 */

// crossing over key-presses count as both keys seperate
/* #define PERMISSIVE_HOLD */

/* #define RETRO_TAPPING */

/* #define HOLD_ON_OTHER_KEY_PRESS */

// controlls time for tapping, then holding for repeat
/* #define QUICK_TAP_TERM 250 */


/* #define HOLD_ON_OTHER_KEY_PRESS_PER_KEY */
