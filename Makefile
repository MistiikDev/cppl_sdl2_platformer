all:
	g++ main.cpp src/*.cpp -o game -Isrc/include -Lsrc/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image