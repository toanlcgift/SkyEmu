/*
 * Public API for the SkyEmu static iOS library.
 * This header is installed by CMake when BUILD_IOS_STATIC_LIB is ON.
 */
#ifndef SKYEMU_H
#define SKYEMU_H

#include <stdbool.h>
#include "sokol_app.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Initialise the core (settings, theme, etc.) */
void skyemu_core_init(void);

/* Load a ROM file – returns true on success */
bool skyemu_load_rom(const char *path);

/* Called once per frame – drives the emulator and renders */
void skyemu_frame(void);

/* Clean up all resources – call before app termination */
void skyemu_cleanup(void);

/* iOS‑specific helpers – forward to the existing implementation */
void skyemu_ios_set_documents_dir(void);
void skyemu_ios_open_file_picker(int num_ext, const char **ext);
void skyemu_ios_open_modal(const char *url);
void skyemu_ios_close_modal(void);

/* Return the sokol_app description that the host app must pass to
 * sapp_ios_init().  The library builds the same description that the
 * original sokol_main() would have returned.
 */
sapp_desc skyemu_sokol_desc(void);

#ifdef __cplusplus
}
#endif

#endif // SKYEMU_H
