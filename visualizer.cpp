#include <iostream>
// represents blocks of memory, will probably be useful when vusalizing memory later
struct mem_Block{
    size_t size;
    mem_Block *next;
    bool isfree = false;
};
class mem_allocator{
    private:
    // buffer represents the memory we will allocate which is a 1mb buffer if im not mistaken
    char buffer[1024*1024];
    // making a linked list to keep track of what blocks of memory are free just to manage the buffer well
    mem_Block block_0 = {0,nullptr} ;
    public:
    void* my_malloc(size_t size){
        mem_Block block = {0,nullptr} ;
        size_t free_mem;
        mem_Block *indexer = &block_0 ;
            while (indexer)
            {
                
                if (indexer->size == 0)
                {
                    indexer->size = size;
                    indexer->next = &block;
                    break;
                }
                free_mem += indexer->size;
                indexer = indexer->next;
            }
        void *ptr = &buffer + free_mem ;
        return ptr;
    }
};

int main(){
    return 0;
}