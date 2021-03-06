#include <config.h>
#include <audio/audio.h>

static int null_audio_init(void **audio_render, int samplerate, int channels, int format, int buffer, int is_capture)
{
    *audio_render = (void *)1;
    return 0;
}

static void null_audio_release(void *audio_render)
{
}

static void null_audio_play(void *audio_render, LVGSound *sound, int flags, int start_sample, int end_sample, int loops)
{
}

static void null_audio_stop_all(void *audio_render)
{
}

static void null_resample(void *audio_render, LVGSound *sound)
{
}

const audio_render null_audio_render =
{
    null_audio_init,
    null_audio_release,
    null_audio_play,
    null_audio_stop_all,
    null_resample
};
