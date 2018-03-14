//
//  McpeHandler.cpp
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



McpeHandler::McpeHandler() {
    
    blocksize = 16;
    blocksize2 = blocksize*blocksize;
    map = 0;
    db = 0;
    
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

McpeHandler::McpeHandler(std::string name) : McpeHandler() {

    loadLevelDB(name);
}

McpeHandler::~McpeHandler()  {
    if (db != 0) {
        delete db;
        db=0;
    }
    
}

void McpeHandler::loadLevelDB(std::string name) {
    
    filename = name;
    blocksize = 16;
    blocksize2 = blocksize*blocksize;
    map = 0;
    
    MCPELOG("Database path: " << filename );
    
    if (db != 0) {
        delete db;
        db=0;
    }
    options.compressors[0] = new leveldb::ZlibCompressor();
    options.create_if_missing = false;
    leveldb::Status status = leveldb::DB::Open(options, filename, &db);
    
    MCPELOG("Status = " << status.ToString().c_str() );
    assert(status.ok());
}

void McpeHandler::getBlock(const char* block, Color* map, int zmax)
{
    int air = 0;
    
    Color color;
    color.c = 0x00654321;
    
    	    
    const unsigned char* col = (const unsigned char*)block;
    for (int x = 0; x < blocksize; x++) {
        for (int y = 0; y < blocksize; y++) {

            int pos = x + y * width * blocksize;
            
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

void McpeHandler::moveBlock(int z, const char* block, char* target, size_t size)
{
    unsigned char* temp = new unsigned char[size];

    const unsigned char* scol = (const unsigned char*)block;
    unsigned char* tcol = temp;
    
    memcpy(temp, block, size);

    while (z > 0) {

        // block -> temp
        for (int c = 0; c < blocksize2; c++) {
            memcpy(tcol, scol+1, 127);
            tcol += 128;
            scol += 128;
        }

        for (int c = 0; c < blocksize2; c++) {
            for (int i = 0; i < 63; i++) {
                tcol[i] =((scol[i]>>4)&0xf) | (0xf0&( scol[i+1] << 4));
            }
            tcol[63] = ((scol[63]>>4)&0xf) | (0xf0&( scol[63] << 4)); 
    
            tcol += 64;
            scol += 64;
        }


        for (int c = 0; c < blocksize2; c++) {
            for (int i = 0; i < 63; i++) {
                tcol[i] =((scol[i]>>4)&0xf) | (0xf0&( scol[i+1] << 4));
            }
            tcol[63] = ((scol[63]>>4)&0xf) | (0xf0&( scol[63] << 4));

            tcol += 64;
            scol += 64;
        }


        for (int c = 0; c < blocksize2; c++) {
            for (int i = 0; i < 63; i++) {
                tcol[i] =((scol[i]>>4)&0xf) | (0xf0&( scol[i+1] << 4));
            }
            tcol[63] = ((scol[63]>>4)&0xf) | (0xf0&( scol[63] << 4));

            tcol += 64;
            scol += 64;
        } 


        scol = (const unsigned char*)target;
        tcol = (unsigned char*)temp;

        memcpy(target, temp, size);

        z--;
    }

}

void McpeHandler::getTopo(const char* block, Color* map)
{
    int air = 0;
    //int water[] = {8,9,79,174};
    
    int zmax = 128;
    
    Color color;
    color.c = 0x00654321;
    
    
    
    const unsigned char* col = (const unsigned char*)block;
    for (int x = 0; x < blocksize; x++) {
        for (int y = 0; y < blocksize; y++) {
            
            int pos = x + y * width * blocksize;
            
            for (int c = zmax - 1 ; c >= 0; c--) {
                
                color.c = 0;
                unsigned int value = col[c];
                if ((value != air)
                    and (value != 8)
                    and (value != 9)
                    and (value != 79)
                    and (value != 175))
                {
                    if (c > 110) {
                        color.argb.r = 51.0 + 102.0*(c - 110)/18.0;
                        color.argb.g =  36.0 + 72.0*(c - 110)/18.0;
                    } else if (c > 64) {
                            color.argb.g = 255.0 * (128 - c) / 64.0;
                        } else {
                        color.argb.b = 255.0 * c / 64.0;
                    }
                    color.c = 0xff000000 | color.c;
                    break;
                }
                
            }
            
            col = col + zmax;
            
            map[pos] = color;
        }
    }
}

void McpeHandler::findSizes() {
    
    MCPELOG("Find Map Dimentions" );

    leveldb::Status status;
    leveldb::ReadOptions ropts;
    leveldb::Iterator *it =  db->NewIterator(ropts);
    
    it->SeekToFirst();
    
    
    int minX = 0;
    int minY = 0;
    int maxX = 0;
    int maxY = 0;
    
    maxBlocks = 0;
    
    for (it->SeekToFirst(); it->Valid(); it->Next()) {
        
        status = it->status();
        //MCPELOG("Status = " << status.ToString().c_str() );
        
        McpeBlock block(it->key(), it->value());

        maxBlocks++;
        
        if (block.terrain) { 
            if (block.x > maxX ) maxX=block.x;
            if (block.y > maxY ) maxY=block.y;
            if (block.x < minX ) minX=block.x;
            if (block.y < minY ) minY=block.y;
        }

    }
    
    
    width = maxX-minX + 2;
    offX =  -minX;
    
    height = maxY-minY + 2;
    offY = -minY;
    
    std::cout << "Min:  (" << minX << ", " << minY << " ) ";
    std::cout << " Max:  (" << maxX << ", " << maxY << " ) ";
    MCPELOG(" Size: " << width << " x " << height );
    
    map = new Color [height*width*blocksize2];
    MCPELOG("Allocated " << height*width*4*blocksize2/1024/1024 << "MBytes" );
    

}

leveldb::DB *McpeHandler::getDB() {
    return db;
}

void McpeHandler::addToMap(int otherx, int othery, int z, McpeHandler& other) {
    
    MCPELOG("Adding to map on " << otherx << "," << othery );

    leveldb::Status status;
    leveldb::ReadOptions ropts;
    leveldb::Iterator *it =  other.getDB()->NewIterator(ropts);
    
    it->SeekToFirst();
    
    
    if (db != 0) {
        delete db;
        db=0;
    }
    options.compressors[0] = new leveldb::ZlibCompressor();
    options.create_if_missing = false;
    status = leveldb::DB::Open(options, filename, &db);
    
    MCPELOG("Status = " << status.ToString().c_str() );
    assert(status.ok());

    leveldb::WriteOptions write_options;
    write_options.sync = true;

    int blockCount=0;
    
    for (it->SeekToFirst(); it->Valid(); it->Next()) {
        
        status = it->status();
        //MCPELOG("Status = " << status.ToString().c_str() );
        
        leveldb::Slice key = it->key();
        const char* data = key.data();
        
        int x = *((int*)data) + otherx;
        int y = *((int*)(data+4)) + othery;
        char code = data[8];

        if (progress) progress(100*(blockCount++)/maxBlocks, progressContext);
        
        if ( key.size() != 9 ) {
            continue;
        }
        
        char newdata[9];
        memcpy(newdata, &x, 4);
        memcpy(newdata+4, &y, 4);
        memcpy(newdata+8, &code, 1);

        leveldb::Slice newkey(newdata, 9);

        leveldb::Slice value = it->value();
        const char* block = value.data();
        char* newblock = new char[value.size()];
        memcpy(newblock, block, value.size());

        if (code == layerCode) {
            moveBlock(z, block, newblock, value.size());
        }

        leveldb::Slice newvalue(newblock, value.size());

        
        if (code != 'l') {
            //MCPELOG("adding.. " << status.ToString().c_str() << " " << x << ", " << y << " " << data[8] << " " << key.size() <<  ": " << value.size() ); 
            db->Put(write_options, newkey, newvalue);
        }

        
        delete [] newblock;

    }
    
}

void McpeHandler::loadMap(MapType maptype) {
    
    MCPELOG("Loading Map " );

    
    leveldb::Status status;
    leveldb::ReadOptions ropts;
    leveldb::Iterator *it =  db->NewIterator(ropts);
    
    it->SeekToFirst();
    
    memset(map, 0, height*width*4*blocksize2);
    MCPELOG("Map Cleared" );
    
    int blockCount = 0;
    
    for (it->SeekToFirst(); it->Valid(); it->Next()) {
        
        status = it->status();
        
        leveldb::Slice slice = it->key();

        McpeBlock block(it->key(), it->value());

        if (progress) progress((blockCount++)*100/maxBlocks, progressContext);

        if (block.terrain) {
            
            int pos = ((block.x + offX)  + (block.y+offY) * width * blocksize)* blocksize;
            
            //MCPELOG(status.ToString().c_str() << " " << x << ", " << y << " " << data[8] << " " << slice.size() <<  ": " << value.size() << std::endl; // << it->value().ToString() );
            
            if (maptype == NORMAL)
                getBlock(block.blockData, &map[pos], block.zmax);
            else if (maptype == TOPO)
                getTopo(block.blockData, &map[pos]);
            

        }
        
        //MCPELOG(status.ToString().c_str() << " " << x << ", " << y << " " << data[8] << " " << slice.size() <<  ": " << value.size() << std::endl; // << it->value().ToString() );
        
        
    }
    MCPELOG("Done Updating Map" );
}

const char* McpeHandler::getBitmap () {
    return (const char* ) map;
}

int McpeHandler::getBitmapSize () {
    return height*width*blocksize2*sizeof(Color);
}

int McpeHandler::getBitmapWidth () {
    return width*blocksize;
}

int McpeHandler::getBitmapHeight () {
    return height*blocksize;
}



void McpeHandler::savePNM(char* filename) {
    
    MCPELOG("Writing File" );
    
    std::ofstream ofs (filename, std::ofstream::out);
    ofs << "P6" << std::endl;
    ofs << width*blocksize << " " << height*blocksize << std::endl;
    ofs << 255 << std::endl;
    
    for (int y = 0; y < height*blocksize; y++) {
        for (int x = 0; x < width*blocksize; x++)
        {
            int pos = x + y * width * blocksize;
            ofs.write((char*)&map[pos].argb.r,1);
            ofs.write((char*)&map[pos].argb.g,1);
            ofs.write((char*)&map[pos].argb.b,1);
            
        }
        
    }
    ofs.close();
    
}


void McpeHandler::testMap(int _width, int _height) {
    
    MCPELOG("Generating test mat" );
    
    
    width = _width;
    offX =  0;
    
    height = _height;
    offY = 0;
    

    MCPELOG("Size:" << width << ", " << height );
    MCPELOG("Max:" << offX << ", " << offY );
    
    
    map = new Color [height*width*blocksize2];
    
    Color* pmap = map;
    
    for (int y = 0; y < 2*blocksize; y++) {
        for (int x = 0; x < width*blocksize; x++)
        {
            pmap->c=0xff880000;
            pmap++;
        }
    }
    for (int y = 0; y < (height-4)*blocksize; y++) {
        for (int x = 0; x < width*blocksize; x++)
        {
            if ((x > blocksize) and (x < (width-1)*blocksize))
                pmap->c=0xff008800;
            else
                pmap->c=0xff880000;

            pmap++;
        }
    }
    for (int y = 0; y < 2*blocksize; y++) {
        for (int x = 0; x < width*blocksize; x++)
        {
            pmap->c=0xff880000;
            pmap++;
        }
    }
    
    
    MCPELOG("allocated " << height*width*4*blocksize2/1024/1024 << "MBytes" );
}

void McpeHandler::clear (int x1, int y1, int x2, int y2, char action) {
    
    leveldb::Status status;
    leveldb::ReadOptions ropts;
    leveldb::Iterator *it =  db->NewIterator(ropts);
    
    it->SeekToFirst();
    leveldb::WriteOptions write_options;
    write_options.sync = true;

    int total=0, affected = 0;
    for (it->SeekToFirst(); it->Valid(); it->Next()) {
        
        status = it->status();
        
        leveldb::Slice key = it->key();
        const char* data = key.data();
        
        int x = *((int*)data);
        int y = *((int*)(data+4));
        
        if ( key.size() != 9 ) {
            continue;
        }
        
        leveldb::Slice value = it->value();
        
        if (memcmp(key.data(), "~local_player", 13)==0) {
             MCPELOG(" found local_player, size = " << value.size() ); 
        } else {
            total++;
            if (x>x1 and y > y1 and x < x2 and y < y2) {
                if (action == 'e') { // erase area
                    db->Delete(write_options, key);
                    affected ++;
                }
             } else {
                if (action == 'c') { 
                    //crop area
                    db->Delete(write_options, key);
                    affected ++;
                }
            }

        } 
    }
    MCPELOG("Erasing " << affected << " out of " << total << " blocks" );
 
}

void McpeHandler::crop (int x1, int y1, int x2, int y2) {
    clear(x1,y1,x2,y2,'c');
}

void McpeHandler::erase (int x1, int y1, int x2, int y2) {
    clear(x1,y1,x2,y2,'e');
}

void McpeHandler::compact () {
    MCPELOG("Compacting Database..." );
    if (db != 0)
        db->CompactRange(NULL, NULL);
}


void McpeHandler::getBlockInfo(int x, int y) {
    
    Key key_data;
    
    key_data.x = x / blocksize;
    key_data.y = y / blocksize;
    key_data.code = layerCode;
    
    
    leveldb::Status status;
    leveldb::ReadOptions ropts;

    leveldb::Slice key((char*)&key_data, 9);
    std::string value;
    
    status = db->Get(ropts, key, &value);
    
    int xoff = x % blocksize;
    int yoff = y % blocksize;
    
    const char* block = 0;
    
    
    
    const unsigned char* col = (const unsigned char*)block;

    col += xoff + yoff * blocksize;
    int air = 0;
    unsigned int minecraft = 0;
    
    for (int c = 127 ; c >= 0; c--) {
        minecraft = col[c];
        if (minecraft != air) break;
    }
    
    
}

void McpeHandler::setProgressHanler(void (*_progress)(int, void*), void* _context) {
    progress = _progress;
    progressContext = _context;
}

