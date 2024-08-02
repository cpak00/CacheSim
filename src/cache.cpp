#include "cache.hh"

TensorCache::TensorCache(int capacity): capacity(capacity), iter_cur(0),
    count_miss(0), count_hit(0), count_write(0)
{
    this->iter_list = new CacheMap::iterator [capacity];
}

TensorCache::~TensorCache()
{
    this->data_map.clear();
    delete[] this->iter_list;
}

CacheMap::iterator TensorCache::match(TensorTag tag)
{
    return this->data_map.find(tag.key());
}

void TensorCache::replace(CacheMap::iterator iter)
{
    CacheMap::iterator src = this->iter_list[this->iter_cur];
    if (src != this->data_map.end() && src->second.modified) count_write ++;
    this->iter_list[this->iter_cur++] = iter;
    if (this->iter_cur >= this->capacity) this->iter_cur = 0;
}

int TensorCache::store(TensorTag tag)
{
    CacheMap::iterator iter = this->match(tag);
    if (iter == this->data_map.end()) 
    {   // miss
        CacheMap::iterator new_iter = this->data_map.insert(std::make_pair(tag.key(), CacheLine({true, true}))).first;
        this->replace(new_iter);
    }
    else
    {   // match
        this->count_hit ++;   
    }
    
    return 0;
}

void TensorCache::print_stat()
{
    std::cout << "count_miss: " << this->count_miss << std::endl;
    std::cout << "count_hit: " << this->count_hit << std::endl;
    std::cout << "count_write: " << this->count_write << std::endl;
}

int TensorCache::load(TensorTag tag)
{
    CacheMap::iterator iter = this->match(tag);
    if (iter == this->data_map.end()) 
    {   // miss
        CacheMap::iterator new_iter = this->data_map.insert(std::make_pair(tag.key(), CacheLine({true, false}))).first;
        this->replace(new_iter);
        this->count_miss ++;
    }
    else
    {   // match
        this->count_hit ++;   
    }
    
    return 0;
}
