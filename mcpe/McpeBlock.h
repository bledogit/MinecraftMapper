//
//  McpeBlock.h
//  MineMapper
//
//  Created by Jose on 6/10/15.
//  Copyright (c) 2015 Jose. All rights reserved.
//

#ifndef __MineMapper__McpeBlock__
#define __MineMapper__McpeBlock__

#include "leveldb/db.h"

/*
// Key size:
// 9  | x: 32 | z: 32 | tag: 8 
// 10 | x: 32 | z: 32 | tag: 8 | (optional) subchunk id: 8 |
// 14 | x: 32 | z: 32 | dimension: 32 | tag: 8 | (optional) subchunk id: 8 |
// 18 ??
// Subchunk 3D data order is always sent in order XZY ((X << 8) | (Z << 4) | Y)


Payload content

1 byte: count of subchunks in the packet
    Subchunks:
        1 byte: subchunk format version (always 0 currently, useless byte)
        4096 bytes of block IDs (1 byte per entry, order XZY)
        2048 bytes of block data (4 bits per entry, order XZY)
        2048 bytes of sky light (4 bits per entry, order XZY)
        2048 bytes of block light (4 bits per entry, order XZY)
        512 bytes: heightmap data (1 short per entry, order unverified)
        256 bytes: biome id data (1 byte per entry, order unverified)
        1 byte: border block count
            Border blocks:
                1 byte containing chunk block XZ coordinates (unknown which way round, 4 bits for each
        1 signed varint: block extra data count
            Block extra data:
                1 signed varint: chunk block coords (XZY, 4 bits for each)
                1 short: block extra data value
        Here to the end of the buffer: tile NBT data (varint NBT)


*/

class McpeBlock {

public:
    int tag = -1;
    int dimension = -1;
    int subchunkid = -1;
    int x =-1;
    int y =-1;
    bool terrain = false;
    const char* blockData;
    int zmax = 1;
    
    McpeBlock(const leveldb::Slice& key, const leveldb::Slice& block);
    McpeBlock(const leveldb::Slice& key, const leveldb::Slice& block, bool debug);
    std::string tagName(char tag);
};


#endif


