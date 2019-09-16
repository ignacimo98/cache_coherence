//
// Created by Ignacio Mora on 2019-09-11.
//

#include <sstream>
#include <fstream>
#include "cache.h"


int Cache::getTag(int block) {
    return cacheBlocks[block].tag;

}

Status Cache::getStatus(int block) {
    return cacheBlocks[block].block_status;
}

int Cache::getData(int block) {
    return cacheBlocks[block].data;
}

void Cache::setTag(int block, int tag) {
    cacheBlocks[block].tag = tag;

    std::ofstream outfile;
    std::stringstream fmt_filename;
    fmt_filename << "info_for_ui/cache" << num_core<< "_content.txt";
    outfile.open(fmt_filename.str(), std::ios::out | std::ios::trunc );
    std::stringstream fmt_data;
    std::stringstream fmt_status;
    std::stringstream fmt_tag;

    fmt_data << "[";
    for (int i = 0; i < 7; ++i) {
        fmt_data << cacheBlocks[i].data << ", ";
    }
    fmt_data << cacheBlocks[7].data << "]";
    fmt_status << "[";
    for (int i = 0; i < 7; ++i) {
        fmt_status << cacheBlocks[i].block_status << ", ";
    }
    fmt_status << cacheBlocks[7].block_status << "]";
    fmt_tag << "[";
    for (int i = 0; i < 7; ++i) {
        fmt_tag << cacheBlocks[i].tag << ", ";
    }
    fmt_tag << cacheBlocks[7].tag << "]";

    outfile << "[" << fmt_data.str() << ", " << fmt_status.str() << ", " << fmt_tag.str() <<"]"<< std::endl;
    outfile.close();
}

void Cache::setStatus(int block, Status status) {
    cacheBlocks[block].block_status = status;

    std::ofstream outfile;
    std::stringstream fmt_filename;
    fmt_filename << "info_for_ui/cache" << num_core<< "_content.txt";
    outfile.open(fmt_filename.str(), std::ios::out | std::ios::trunc );
    std::stringstream fmt_data;
    std::stringstream fmt_status;
    std::stringstream fmt_tag;

    fmt_data << "[";
    for (int i = 0; i < 7; ++i) {
        fmt_data << cacheBlocks[i].data << ", ";
    }
    fmt_data << cacheBlocks[7].data << "]";
    fmt_status << "[";
    for (int i = 0; i < 7; ++i) {
        fmt_status << cacheBlocks[i].block_status << ", ";
    }
    fmt_status << cacheBlocks[7].block_status << "]";
    fmt_tag << "[";
    for (int i = 0; i < 7; ++i) {
        fmt_tag << cacheBlocks[i].tag << ", ";
    }
    fmt_tag << cacheBlocks[7].tag << "]";

    outfile << "[" << fmt_data.str() << ", " << fmt_status.str() << ", " << fmt_tag.str() <<"]"<< std::endl;
    outfile.close();
}

void Cache::setData(int block, int data) {
    cacheBlocks[block].data = data;
    std::ofstream outfile;
    std::stringstream fmt_filename;
    fmt_filename << "info_for_ui/cache" << num_core<< "_content.txt";
    outfile.open(fmt_filename.str(), std::ios::out | std::ios::trunc );
    std::stringstream fmt_data;
    std::stringstream fmt_status;
    std::stringstream fmt_tag;

    fmt_data << "[";
    for (int i = 0; i < 7; ++i) {
        fmt_data << cacheBlocks[i].data << ", ";
    }
    fmt_data << cacheBlocks[7].data << "]";
    fmt_status << "[";
    for (int i = 0; i < 7; ++i) {
        fmt_status << cacheBlocks[i].block_status << ", ";
    }
    fmt_status << cacheBlocks[7].block_status << "]";
    fmt_tag << "[";
    for (int i = 0; i < 7; ++i) {
        fmt_tag << cacheBlocks[i].tag << ", ";
    }
    fmt_tag << cacheBlocks[7].tag << "]";

    outfile << "[" << fmt_data.str() << ", " << fmt_status.str() << ", " << fmt_tag.str() <<"]"<< std::endl;
    outfile.close();
}

void Cache::setBlock(int block, Status status, int tag, int data) {
    std::ofstream outfile;
    std::stringstream fmt_filename;
    fmt_filename << "info_for_ui/cache" << num_core<< "_content.txt";
    outfile.open(fmt_filename.str(), std::ios::out | std::ios::trunc );
    std::stringstream fmt_data;
    std::stringstream fmt_status;
    std::stringstream fmt_tag;
    cacheBlocks[block].tag = tag;
    cacheBlocks[block].block_status = status;
    cacheBlocks[block].data = data;
    fmt_data << "[";
    for (int i = 0; i < 7; ++i) {
        fmt_data << cacheBlocks[i].data << ", ";
    }
    fmt_data << cacheBlocks[7].data << "]";
    fmt_status << "[";
    for (int i = 0; i < 7; ++i) {
        fmt_status << cacheBlocks[i].block_status << ", ";
    }
    fmt_status << cacheBlocks[7].block_status << "]";
    fmt_tag << "[";
    for (int i = 0; i < 7; ++i) {
        fmt_tag << cacheBlocks[i].tag << ", ";
    }
    fmt_tag << cacheBlocks[7].tag << "]";

    outfile << "[" << fmt_data.str() << ", " << fmt_status.str() << ", " << fmt_tag.str() <<"]"<< std::endl;
    outfile.close();



}

Cache::Cache(int num_core) {
    this->num_core = num_core;
}
