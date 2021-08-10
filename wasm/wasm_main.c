
#include "libretro.h"

extern bool retro_callback_environment(unsigned cmd, void* data);
extern void retro_callback_video_refresh(const void* data, unsigned width, unsigned height, size_t pitch);
extern size_t retro_callback_audio_sample_batch(const int16_t* data, size_t frames);
extern void retro_callback_input_poll();
extern int16_t retro_callback_input_state(unsigned port, unsigned device, unsigned index, unsigned id);

int main(int argc, char** argv) {
    retro_set_environment(retro_callback_environment);
    retro_set_video_refresh(retro_callback_video_refresh);
    retro_set_audio_sample_batch(retro_callback_audio_sample_batch);
    retro_set_input_poll(retro_callback_input_poll);
    retro_set_input_state(retro_callback_input_state);
    return 0;
}
