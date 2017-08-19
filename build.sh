gcc -s -Os -flto -Wall -fno-stack-protector nanovg/nanovg.c adpcm.c lvg_audio.c lvg.c svgb.c swf.c lunzip.c \
swftools/lib/*.c swftools/lib/modules/*.c swftools/lib/as3/*.c mp3/minimp3.c \
video/ffmpeg/ffmpeg_dec.c \
-L. -I. -Inanovg -Iswftools/lib -Imp3 -DNDEBUG -D_GNU_SOURCE -o lvg -lm -lglfw -lGL -ltcc2 -ldl -lSDL2 -lavcodec -lavutil
upx -9 ./lvg