all:
	g++ main.cpp src/**/*.cpp -o game \
    -Isrc/core -Isrc/rendering -Isrc/game -Isrc/input -Isrc/assets -Isrc/util -Isrc/include \
    -Llib \
    -lmingw32 -lSDL2main -lSDL2 -lSDL2_image