set -e

scripts/build-sdl.sh macos
scripts/build-ffmpeg-pc.sh macos
. build_src.sh

gcc -Os -flto -std=gnu99 -Wall -fno-stack-protector -ffunction-sections -fdata-sections -Wl,-dead_strip $SRC \
-I. -Isrc -Inanovg -Iswf/swftools/lib \
-LSDL/build-macos -ISDL/include -I. \
-Ivideo/ffmpeg/FFmpeg -Ivideo/ffmpeg/FFmpeg/build-macos -Lvideo/ffmpeg/FFmpeg/build-macos/libavcodec -Lvideo/ffmpeg/FFmpeg/build-macos/libavutil \
-DNDEBUG -D_GNU_SOURCE -DLVG_INTERPOLATE -o lvg_macos -lm -ldl -liconv -lSDL2 -lavcodec -lavutil \
-framework Foundation -framework AVFoundation -framework CoreAudio -framework CoreVideo -framework CoreMedia -framework CoreGraphics -framework CoreServices -framework VideoToolbox \
-framework OpenGL -framework AudioToolbox -framework IOKit -framework AppKit -framework ForceFeedback -framework Carbon -framework Cocoa
upx --best --ultra-brute ./lvg_macos
if [ "$TRAVIS" = "true" ]; then
    zip -9 -u lvg_macos.zip lvg_macos
fi
