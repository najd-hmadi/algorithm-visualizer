#include <iostream>

struct mem_Block{
    size_t size;
    mem_Block *next;
};
class mem_allocator{
    private:
    char buffer[1024*1024];
    mem_Block block_0 = {0,nullptr} ;
    public:
    void* my_alloc(size_t size){
        mem_Block block = {0,nullptr} ;
        size_t free_mem;
        mem_Block *indexer = &block_0 ;
            while (indexer)
            {
                
                if (indexer->size = 0)
                {
                    indexer->size = size;
                    indexer->next = &block;
                    break;
                }
                free_mem += indexer->size;
                indexer = indexer->next;
            } 
        void *ptr = &buffer[free_mem];
        return ptr;
    }
};

int main(){
    mem_allocator m1;
    int *ptr = (int*)m1.my_alloc(sizeof(int));
    *ptr = 5;
    std::cout << "adress: " << ptr << "/// value: " << *ptr;
    return 0;
}