gcc -s -Os -flto -fno-stack-protector nanovg/nanovg.c svg.c lunzip.c -L. -I. -Inanovg -o svg -lm -lglfw -lGL -ltcc2 -ldl