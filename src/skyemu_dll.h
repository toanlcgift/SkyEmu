#ifndef SKYEMU_DLL_H
#define SKYEMU_DLL_H

/*
 * SkyEmu DLL API header
 *
 * When building the DLL, define SKYEMU_DLL_EXPORTS so that functions are
 * exported with __declspec(dllexport).  When consuming the DLL from C/C++
 * code, include this header without defining SKYEMU_DLL_EXPORTS so that
 * functions are imported with __declspec(dllimport).
 *
 * For non-MSVC compilers on Windows (MinGW/GCC) we use __attribute__((visibility("default"))).
 * On non-Windows platforms the macros expand to nothing.
 */

/*
 * SKYEMU_API expands to dllexport/dllimport only when SE_PLATFORM_WINDOWS_DLL
 * is defined.  In all other build configurations it expands to nothing so that
 * the existing executable/library builds are unaffected.
 */
#if defined(SE_PLATFORM_WINDOWS_DLL)
  #if defined(SKYEMU_DLL_EXPORTS)
    #define SKYEMU_API __declspec(dllexport)
  #else
    #define SKYEMU_API __declspec(dllimport)
  #endif
#else
  #define SKYEMU_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Load an HTML file (used for cloud/HTTP control) */
SKYEMU_API void se_load_html(const char *filename);

/* Load a ROM file by path */
SKYEMU_API void se_load_rom(const char *filename);

/* Show the emulator UI overlay */
SKYEMU_API void se_show_ui(void);

/* Hide the emulator UI overlay */
SKYEMU_API void se_hide_ui(void);

/* Set stretch-to-fit mode: 0 = off, 1 = on */
SKYEMU_API void se_stretch_to_fit(int fit);

#ifdef __cplusplus
}
#endif

#endif /* SKYEMU_DLL_H */