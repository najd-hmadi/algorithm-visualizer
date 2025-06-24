#include <iostream>
#include <SDL2/SDL.h>
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
    
    void* my_malloc(size_t size){
        // initialize block to be added to the linked list
        mem_Block *block = new  mem_Block{0,nullptr} ;
        size_t used_mem = 0;
        mem_Block *indexer = &block_0 ;
            while (indexer)
            {
                
                if (indexer->isfree)
                {
                    indexer->size = indexer->size > 0 ? indexer->size : size ;
                    if(indexer->size >= size ) break;
                    indexer->next = block;
                    indexer->isfree = false;
                    break;
                }
                used_mem += indexer->size;
                indexer = indexer->next;
            }
        void *ptr = (void*)((size_t)&buffer + used_mem) ;
        return ptr;
    }
    template<typename T>
    void my_free(T *&ptr){
        // difference between the beginning address of the buffer and the user pointer
        unsigned int difference = (size_t)ptr - (size_t)&buffer;
        unsigned int used_mem = 0;
        mem_Block *indexer = &block_0 ;
        // go through the linked list until the sum of all used memories is equal to the difference calculated previously

        while( difference > used_mem ){
            used_mem += indexer->size;
            indexer = indexer->next;
        }

        indexer->isfree = true;
        ptr = nullptr;
    }
};

int main(int argc, char* argv[]){
    SDL_Window * window = SDL_CreateWindow("algo visualizer",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1500,900,SDL_WINDOW_SHOWN);
    SDL_Surface * surface = SDL_GetWindowSurface(window);
    if( SDL_Init(SDL_INIT_VIDEO) < 0 ) std::cout << "video initialization error: " << SDL_GetError() << "\n";
    if(!window) std::cout << "window initialization failed: " << SDL_GetError() << '\n';
    SDL_UpdateWindowSurface(window);
    SDL_Delay(2000);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}