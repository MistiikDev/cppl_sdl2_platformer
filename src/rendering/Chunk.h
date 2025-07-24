#include <vector>
#include <map>
#include <iostream>

struct Chunk {
    unsigned int chunk_size_x = 32; // In terms of blocks
    
    std::map<int, int> chunkData; // chunkData[x][y]
};