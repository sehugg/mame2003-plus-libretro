
#include "libretro.h"
#include <stdarg.h>
#include <stdio.h>

extern bool retro_callback_environment(unsigned cmd, void* data);
extern void retro_callback_video_refresh(const void* data, unsigned width, unsigned height, size_t pitch);
extern size_t retro_callback_audio_sample_batch(const int16_t* data, size_t frames);
extern void retro_callback_input_poll();
extern int16_t retro_callback_input_state(unsigned port, unsigned device, unsigned index, unsigned id);
extern void retro_callback_log(const char* str);

static void log_ext(enum retro_log_level level, const char* fmt, ...) {
    char buf[2048];
    (void)level;
    va_list va;
    va_start(va, fmt);
    vsprintf(buf, fmt, va);
    retro_callback_log(buf);
    va_end(va);
}

static bool env_cb(unsigned cmd, void* data) {
    switch (cmd) {
        case RETRO_ENVIRONMENT_GET_LOG_INTERFACE:
            ((struct retro_log_callback*)data)->log = log_ext;
            return true;
        default:
            return retro_callback_environment(cmd, data);
    }
}

int main(int argc, char** argv) {
    retro_set_environment(env_cb); //retro_callback_environment);
    retro_set_video_refresh(retro_callback_video_refresh);
    retro_set_audio_sample_batch(retro_callback_audio_sample_batch);
    retro_set_input_poll(retro_callback_input_poll);
    retro_set_input_state(retro_callback_input_state);
    return 0;
}
