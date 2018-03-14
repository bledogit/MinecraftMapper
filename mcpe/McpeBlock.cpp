//
//  McpeBlock.cpp
//  MineMapper
//
//  Created by Jose on 6/10/15.
//  Copyright (c) 2015 Jose. All rights reserved.
//

#include "McpeHandler.h"
#include "McpeBlock.h"


#include <iostream>
#include <fstream>
#include <iomanip>
//#include <assert>

McpeBlock::McpeBlock(const leveldb::Slice& key, const leveldb::Slice& block)  
:  McpeBlock (key,block, false) {
}

McpeBlock::McpeBlock(const leveldb::Slice& key, const leveldb::Slice& block, bool debug = false) {
    const char* data = key.data();
    
    x = *((int*)data);
    y = *((int*)(data+4));
    tag = (int)data[8]&0xff;

    if (key.size() == 9) {
        if (tag == 48) {
            terrain = true;
            zmax = 128;
            blockData = block.data();
        }
        if (tag == '0') dimension = 0; // legacy terrain data 
    } else if (key.size() == 10) {
        if (tag == 46) dimension = 0; // data 2d

        subchunkid = (int)data[9]&0xff; 
        if (tag == 47) {
            terrain = true;
            zmax = 16;
            blockData = block.data() + 1;
        }
    } else if (key.size() == 13) {     
        dimension = *((int*)(data+8));
        tag = (int)data[12]&0xff;
    } else if (key.size() == 14) {     
        dimension = *((int*)(data+8));
        tag = (int)data[12]&0xff;
        subchunkid = (int)data[13]&0xff;
    }

    

    if (debug) {
            MCPELOG("extended " << " (" << x << ", " << y << ") "  
                        << std::dec << " [" << ((int)tag&0XFF) << ", " 
                        << tagName(tag).c_str() 
                        << "] dimension=" << dimension << " " 
                        << "subchunkid=" << subchunkid << " " 
                        << "key_size=" << key.size() << " " 
                        << "data_size=" << block.size());
    }
}

std::string McpeBlock::tagName(char tag) {
    std::string name = "unknown";
    if (tag == 45)  name = "Data2D";
    if (tag == 46)  name = "Data2DLegacy";
    if (tag == 47)  name = "SubChunkPrefix";
    if (tag == 48)  name = "LegacyTerrain";
    if (tag == 49)  name = "BlockEntity";
    if (tag == 50)  name = "Entity";
    if (tag == 51)  name = "PendingTicks";
    if (tag == 52)  name = "BlockExtraData";
    if (tag == 53)  name = "BiomeState";
    if (tag == 54)  name = "FinalizedState";
    if (tag == 118)  name = "Version";
    return name;
}
