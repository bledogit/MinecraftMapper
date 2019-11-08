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
#include <math.h> 
//#include <assert>

McpeBlock::McpeBlock(const leveldb::Slice& key, const leveldb::Slice& block)  
:  McpeBlock (key,block, false) {

    // Init colors
    for (int i =0; i < 256; i++)
        colorarr[i].c = 0xbabe*256+i;
    
    colorarr[0].c = 0x0;
    colorarr[2].c = 0x0000CC00; // grass
    colorarr[3].c = 0x00663300; // dirt
    colorarr[8].c = 0x000000ff; // water
    colorarr[9].c = 0x000000ff; // water
    colorarr[13].c = 0x00808080; //gravel
    colorarr[18].c = 0x00146d14; //leaves
    
    colorarr[12].c = 0x00FFE6B2; //sand
    colorarr[24].c = 0x00FFE6B2; //sandstone
    colorarr[128].c = 0x00FFE6B2; // stand stone stairs
    
    colorarr[78].c = 0x00ffffff; //snow cover
    colorarr[79].c = 0x0000CCFF; //ice
    colorarr[174].c = 0x0000CCFF; //ice apcked
    
    colorarr[27].c = 0x00FF3300; // rail
    colorarr[66].c = 0x00FF3300; // rail powered
    
    colorarr[42].c = 0x00FFFFFF; // iron
    
    
    colorarr[80].c = 0x00ffffff; //snow
    colorarr[20].c = 0x00befbf7; //glass
    colorarr[102].c = 0x00befbf7; //glass
    
    colorarr[1].c = 0x00808080; //stone
    colorarr[4].c = 0x00808080; // coblestone
    colorarr[48].c = 0x00808080; // moss stone
    colorarr[98].c = 0x00808080; //stone
    colorarr[109].c = 0x00808080; //stone stairs
    colorarr[43].c = 0x00808080; //stone
    colorarr[44].c = 0x00808080; //stone slab
    
    
    colorarr[5].c = 0x00754719; //stairs oak
    colorarr[53].c = 0x00754719; // oak
    colorarr[157].c = 0x00754719; // oak
    colorarr[158].c = 0x00754719; // oak
    colorarr[85].c = 0x00754719; // fence
    colorarr[107].c = 0x00754719; // fence
    colorarr[17].c = 0x00754719; // wood
    
    colorarr[163].c = 0x00FF6600; // acacia
    colorarr[163].c = 0x00FF6600; // acacia
    colorarr[163].c = 0x00FF6600; // acacia
    colorarr[163].c = 0x00FF6600; // acacia
    
    colorarr[164].c = 0x00542900; // dark
    colorarr[164].c = 0x00542900; // dark
    colorarr[164].c = 0x00542900; // dark
    colorarr[164].c = 0x00542900; // dark
    
    colorarr[134].c = 0x00291400; //stairs spruce
    colorarr[134].c = 0x00291400; //stairs spruce
    colorarr[134].c = 0x00291400; //stairs spruce
    colorarr[134].c = 0x00291400; //stairs spruce
    
    colorarr[135].c = 0x00EBD699; //stairs brich
    colorarr[135].c = 0x00EBD699; //stairs brich
    colorarr[135].c = 0x00EBD699; //stairs brich
    colorarr[135].c = 0x00EBD699; //stairs brich
    
    colorarr[136].c = 0x00A38566; //stairs jungle
    colorarr[136].c = 0x00A38566; //stairs jungle
    colorarr[136].c = 0x00A38566; //stairs jungle
    colorarr[136].c = 0x00A38566; //stairs jungle
    
    
    colorarr[112].c = 0x003D0F00; // neder
    colorarr[114].c = 0x003D0F00; // nether
    
    colorarr[172].c = 0x00B82E00; //clay
    colorarr[159].c = 0x00B82E00; // stained clay
    
    colorarr[89].c = 0x00FFFF00; // glowstone
    colorarr[50].c = 0x00FFFF00; // candle
    
    colorarr[141].c = 0x0000FF00; // crops
    colorarr[142].c = 0x0000FF00; // crops
    colorarr[244].c = 0x0000FF00; // crops
    colorarr[104].c = 0x0000FF00; // crops
    colorarr[105].c = 0x0000FF00; // crops
    colorarr[103].c = 0x0000FF00; // crops
    colorarr[83].c = 0x0000FF00; // crops
    colorarr[59].c = 0x0000FF00; // crops
    colorarr[81].c = 0x0000FF00; // crops
    
    
    colorarr[31].c = 0x0000CC00; // grass
    colorarr[37].c = 0x00deff00; // dandelion
    colorarr[175].c = 0x00deff00; // sunfl
    colorarr[38].c = 0x00ec0000; // poppy
    colorarr[40].c = 0x0000CC00; // moosh
    colorarr[100].c = 0x0000CC00; // moosh
    colorarr[32].c = 0x00ec6400; // deadbush
    colorarr[39].c = 0x00ec0006; // brownmush
    colorarr[99].c = 0x00ec0006; // brownmush
    colorarr[51].c = 0x00ff0000; // FIRE
    colorarr[51].c = 0x00a5a646; // hay
    
    colorarr[0xa1].c = 0x00175700; // some tree
    colorarr[0x6a].c = 0x00175700; // vines
    colorarr[0x39].c = 0x0000c9ff; // diamond
    colorarr[0x29].c = 0x00f0ff00; // gold
    colorarr[0x6e].c = 0x00504354; // mycelium
}

void McpeBlock::render(Color* map, int stride)
{
            switch(version) {
                case 8:
                    // version 8
                   // The format is [version:byte][num_storages:byte][block storage1]...[blockStorageN]
                    renderV8(map,stride);
                    break;
                default:
                    // versions 2-7
                    // Format: [version:byte][16x16x16 blocks][16x16x16 data]
                    renderL(map,stride);
            }
}

void McpeBlock::renderV8(Color* map, int stride) 
{   //[version:byte][num_storages:byte][block storage1]...[blockStorageN]

    const unsigned int* word = (const unsigned int*)blockData;
    int air = 0;
    bool isRuntime = (palette & 1) != 0;
    int bitsPerBlock = palette >> 1;
    int blocksPerWord = (int) floor(32 / bitsPerBlock);
    int wordCount = (int ) ceil(4096.0 / blocksPerWord);
    Color color;
    color.c = 0x00654321;
    int blocksize = 16;
    int position = 0;


    const unsigned int* pal = word + wordCount;
    MCPELOG("renderV8 " << "(" << x << ", " << y << ") " 
                        << "chunk=" << subchunkid << " "
                        << "palette=" << palette << " " 
                        << "wordCount=" << wordCount << " " 
                        << "byteCount=" << wordCount*4 << " " 
                        << "size=" << size<< " " 
                        << "other=" << size - wordCount*4 << " " 
                        );
    
    for (int i = 0; i < size/4 - wordCount; i++)
        MCPELOG( "bytes=" << std::hex << (*pal++) << std::dec << " " );
    //for (int palletId = 0; palletId < localPallete.size(); palletId++) {
    //                       localPallete.put(palletId, NBTTagSerializer.readTag(bytes));
    //                   }

    for (int wordi = 0; wordi < wordCount; wordi++) {
        int lastz[16][16];

        for (int i = 0; i < 16; i++)
            for (int j = 0; j < 16; j++)
                lastz[i][j] = 0;

        for (int block = 0; block < blocksPerWord; block++) {
            int state = ((*word) >> ((position % blocksPerWord) * bitsPerBlock)) & ((1 << bitsPerBlock) - 1);
            int x = (position >> 8) & 0xF;
            int z = position & 0xF;
            int y = (position >> 4) & 0xF; 
            position++;
            int pos = x + y * stride * blocksize;

            unsigned int value = state & 0xff;


            if (map) {
                int subc = color.argb.a;
                if ((subc <= subchunkid) && (z >= lastz[x][y])) {
                    if (value != air) {
                        color.c = colorarr[value].c & 0xfffff;
                        color.argb.a = subchunkid;
                        map[pos] = color ;
                        lastz[x][y] = z;
                    }
                }
            }

            
                MCPELOG("word " << "palette=" << palette << " " 
                        << "wordCount=" << wordCount << " " 
                        << "byteCount=" << wordCount*4 << " " 
                        << "(" << x << ", " 
                        << y << ", " 
                        << z << ") " 
                        << std::hex << state << std::dec << " " 
                        );
        }
        word++;
    }
}

void McpeBlock::renderL(Color* map, int stride)
{
    int air = 0;
    int blocksize = 16;
    
    Color color;
    color.c = 0x00654321;
            
    const unsigned char* col = (const unsigned char*)blockData;
    for (int x = 0; x < blocksize; x++) {
        for (int y = 0; y < blocksize; y++) {

            int pos = x + y * stride * blocksize;
            
            color = map[pos]; //<---- default
            
            for (int c = zmax - 1 ; c >= 0; c--) {
                unsigned int value = col[c];
                
                
                if (value != air) {
                    color.c = 0xff000000 | colorarr[value].c;
                    break;
                }
                
            }
            
            col = col + zmax;
            
            if (map) map[pos] = color;
        }
    }
    
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
            version = (int)block.data()[0]; 

            switch(version) {
                case 8:
                    // version 8
                   // The format is [version:byte][num_storages:byte][block storage1]...[blockStorageN]
                    storages = (int)block.data()[1]; 
                    palette = (int)block.data()[2]; 
                    blockData = block.data() + 2;  
                    size = block.size() - 2;
                case 1:
                    storages = 1;
                    blockData = block.data() + 1;   
                    size = block.size() - 1;
                default:
                    // versions 2-7
                    // Format: [version:byte][16x16x16 blocks][16x16x16 data]
                    blockData = block.data() + 1;  
                    size = block.size() - 1;
            }
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
                        << "version=" << version << " " 
                        << "storages=" << storages << " " 
                        << "palette=" << palette << " " 
                        << "key_size=" << key.size() << " " 
                        << "data_size=" << block.size() << " "

                        );
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
