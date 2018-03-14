//
//  McpeHandler.h
//  MineMapper
//
//  Created by Jose on 6/10/15.
//  Copyright (c) 2015 Jose. All rights reserved.
//

#ifndef __MineMapper__McpeHandler__
#define __MineMapper__McpeHandler__

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdio.h>

#include "leveldb/db.h"
#include "leveldb/zlib_compressor.h"

#ifndef MCPELOG
    #define MCPELOG(x) do { std::cerr << x << std::endl;} while (0)
#endif

typedef union Color
{
    unsigned int      c;
    struct argbTag
    {
        unsigned char b;
        unsigned char g;
        unsigned char r;
        unsigned char a;
    } argb;
} COLOR4B;

class BlockInfo {
    Color c;
    
};


typedef struct Key {
    int x;
    int y;
    char code;
} _Key;

typedef enum MapType {
    NORMAL = 0,
    TOPO = 1
} _MapType;



class McpeHandler {
    
    Color colorarr[256];

    
    int width;
    int height;
    int offX;
    int offY;
    int maxBlocks;
    
    int blocksize;
    int blocksize2;
    Color* map;
    std::string filename;
    leveldb::DB *db;
    leveldb::Options options;
    char layerCode = 48; //'0';
    
    void (*progress)(int, void*) = 0;
    void* progressContext = 0;
    
    void clear (int x1, int y1, int x2, int y2, char action);

public:
    McpeHandler();
    McpeHandler(std::string name);
    ~McpeHandler();
    
    void loadLevelDB(std::string name);
    void moveBlock(int z, const char* block, char* target, size_t size);

    void getBlock(const char* block, Color* map, int zmax);
    void getTopo(const char* block, Color* map);
    void findSizes();
    void loadMap(MapType type = NORMAL);
    void savePNM(char* filename);
    const char* getBitmap ();
    int getBitmapSize();
    int getBitmapWidth ();
    int getBitmapHeight ();
    int getOffsetW () { return offX;}
    int getOffsetH () { return offY;}
    
    void testMap(int width, int height);
    leveldb::DB *getDB();
    void addToMap(int x, int y, int z, McpeHandler& other);
    void crop (int x1, int y1, int x2, int y2);
    void erase (int x1, int y1, int x2, int y2);

    void getBlockInfo(int x, int y);
    void setProgressHanler(void (*progress)(int, void*), void* context);
    
    void compact ();


};



#endif /* defined(__MineMapper__McpeHandler__) */
