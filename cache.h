//
// Created by Ignacio Mora on 2019-09-11.
//

#ifndef PROYECTO1ARQUIII_CACHE_H
#define PROYECTO1ARQUIII_CACHE_H

enum Status { INVALID, SHARED, MODIFIED };

typedef struct {
    Status block_status;
    int tag;
    int data;
} CacheBlock;

class Cache {

private:
    CacheBlock cacheBlocks[8] = {};
    int num_core;
public:
    Cache(int num_core);
    int getTag(int block);
    Status getStatus(int block);
    int getData(int block);
    void setTag(int block, int tag);
    void setStatus(int block, Status status);
    void setData(int block, int data);
    void setBlock(int block, Status status, int tag, int data);
    bool isCached(int address);




};


#endif //PROYECTO1ARQUIII_CACHE_H
