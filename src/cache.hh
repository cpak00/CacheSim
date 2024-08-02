#pragma once
#include "src/sim_obj.hh"
#include <sstream>
#include <iostream>
#include <unordered_map>

struct TensorTag {
    std::string name;
    int row;
    int col;    

    const std::string key() {
        std::stringstream s;
        s << name << " " << row << " " << col;
        return s.str();
    }
};

struct CacheLine {
    // char data;
    bool valid;
    bool modified;
};

typedef struct TensorTag TensorTag;
typedef struct CacheLine CacheLine;
typedef std::unordered_map<std::string, CacheLine> CacheMap; 


class TensorCache: public SimObj {
    public:
        TensorCache(int capacity);
        ~TensorCache();

        int load(TensorTag tag);
        int store(TensorTag tag);

        void print_stat();

    protected:
        int capacity;
        CacheMap data_map;
        CacheMap::iterator* iter_list;
        int iter_cur;

        int count_miss;
        int count_hit;
        int count_write;

        CacheMap::iterator match(TensorTag tag);
        void replace(CacheMap::iterator iter);

};
