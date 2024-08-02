#include "src/cache.hh"

int main() {
    TensorCache cache(4);
    
    cache.store({"B", 0, 0});
    cache.load({"A", 0, 0});
    cache.load({"A", 0, 1});
    cache.load({"A", 1, 0});
    cache.load({"A", 0, 0});
    cache.load({"A", 1, 0});
    cache.load({"A", 1, 1});

    cache.print_stat();
}