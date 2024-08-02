#pragma once
#include "src/sim_obj.hh"
#include <sstream>
#include <iostream>
#include <unordered_map>

struct TensorTag {
    /// @brief tensor name, like "A", "B", or "C"
    std::string name;
    /// @brief the column index of the date in the tensor
    int row;
    /// @brief the row index of the data in the tensor 
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
    /// @brief The modified data will be write back to the off-chip memory when it is replaced.
    bool modified;
};

typedef struct TensorTag TensorTag;
typedef struct CacheLine CacheLine;
typedef std::unordered_map<std::string, CacheLine> CacheMap; 


class TensorCache: public SimObj {
    public:
        /// @brief create a cache which could store 'capacity' bytes data by the format of {tensor_name, data_row, data_col}
        /// @param capacity
        TensorCache(int capacity);
        ~TensorCache();

        /// @brief load from cache by the TensorTag: {tensor_name:string, row_index:int, col_index:int}
        /// @param tag 
        /// @return 0
        int load(TensorTag tag);
        /// @brief store to cache by the TensorTag: {tensor_name:string, row_index:int, col_index:int}
        /// @param tag 
        /// @return 
        int store(TensorTag tag);

        void print_stat();

    protected:
        int capacity;
        CacheMap data_map;
        CacheMap::iterator* iter_list;
        int iter_cur;

        /// @brief data miss when loading the cache
        int count_miss;
        /// @brief data hit
        int count_hit;
        /// @brief data write back to the memory when it is replaced
        int count_write;

        CacheMap::iterator match(TensorTag tag);
        void replace(CacheMap::iterator iter);

};
