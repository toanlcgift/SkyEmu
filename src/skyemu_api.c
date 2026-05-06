#include "skyemu.h"
#include "main.c" // bring in internal functions (init, frame, cleanup, etc.)

/* Public API wrappers */
void skyemu_core_init(void) {
    se_init();
}

bool skyemu_load_rom(const char *path) {
    se_load_rom(path);
    return emu_state.rom_loaded;
}

void skyemu_frame(void) {
    frame();
}

void skyemu_cleanup(void) {
    cleanup();
}

void skyemu_ios_set_documents_dir(void) {
    se_ios_set_documents_working_directory();
}

void skyemu_ios_open_file_picker(int num_ext, const char **ext) {
    se_ios_open_file_picker(num_ext, ext);
}

void skyemu_ios_open_modal(const char *url) {
    se_ios_open_modal(url);
}

void skyemu_ios_close_modal(void) {
    se_ios_close_modal();
}

sapp_desc skyemu_sokol_desc(void) {
    // reuse the existing sokol_main implementation
    return sokol_main(0, NULL);
}
