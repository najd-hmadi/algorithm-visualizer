#include <iostream>
// represents blocks of memory, will probably be useful when vusalizing memory later
struct mem_Block{
    size_t size;
    mem_Block *next;
    bool isfree = true;
};
class mem_allocator{
    private:
    // buffer represents the memory we will allocate which is a 1mb buffer if im not mistaken
    char buffer[1024*1024];
    // making a linked list to keep track of what blocks of memory are free just to manage the buffer well
    mem_Block block_0 = {0,nullptr} ;
    public:
    size_t get_address(){
        // std::cout << (size_t)&buffer;
        return (size_t)&buffer;
    }
    void* my_malloc(size_t size){
        // initialize block to be added to the linked list
        mem_Block block = {0,nullptr} ;
        size_t used_mem;
        mem_Block *indexer = &block_0 ;
            while (indexer)
            {
                
                if (indexer->isfree)
                {
                    indexer->size = indexer->size > 0 ? indexer->size : size ;
                    if(indexer->size >= size ) break;
                    indexer->next = &block;
                    indexer->isfree = false;
                    break;
                }
                used_mem += indexer->size;
                indexer = indexer->next;
            }
        void *ptr = (void*)((size_t)&buffer + used_mem) ;
        return ptr;
    }
    void my_free(void* &ptr){
        // difference between the beginning address of the buffer and the user pointer
        unsigned int difference = (size_t)ptr - (size_t)&buffer;
        unsigned int used_mem = 0;
        mem_Block *indexer = &block_0 ;
        // go through the linked list until the sum of all used memories is equal to the difference calculated previously

        while( difference > used_mem ){
            used_mem = indexer->size;
            indexer = indexer->next;
        }

        indexer->isfree = true;
        ptr = nullptr;
    }
};

int main(){
    // debugging
    mem_allocator m1;
    int *ptr = (int*)m1.my_malloc(sizeof(int));
    *ptr = 6;
    int *ptr2 = (int*)m1.my_malloc(sizeof(int));
    // m1.get_address();
    // std::cout << "\n address pointed at: " << ptr << " //// ptr2: " << ptr2 << "****difference between buffer and pointer addresses: " << (size_t)ptr2 - m1.get_address() ;
    return 0;
}