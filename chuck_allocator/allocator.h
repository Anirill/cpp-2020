#pragma once
#include <iostream>
//#include <memory>
//#include <vector>

const size_t BLOCK_SIZE = 2048;

namespace task {


struct Chunk {
    char *start;
    size_t remainder;
    char *current;
    Chunk *next;

    Chunk() {
        std::cout << "Chunk\n";
        this->start = new char[BLOCK_SIZE]; 
        this->current = this->start;
        this->remainder = BLOCK_SIZE;
        this->next = NULL;
    }
    
    ~Chunk() {        
        if (this->next != NULL) this->next->~Chunk();
        if (this->start != NULL) delete[] this->start;
        if (this->next != NULL) {
            delete this->next; 
            std::cout << "Deallocating chunk!\n"; 
        } 
    }

    char* memory_request(const size_t size) {

        if (size <= this->remainder) {
            std::cout << "size ok! \n";
            this->current += size;
            this->remainder -= size;
            return (this->current - size);
        }
        else if (this->next != NULL) {
            std::cout << "Requesting next! \n";
            return this->next->memory_request(size);
        }
        else {
            std::cout << "Creating new! \n";
            this->next = new Chunk();
            return this->next->memory_request(size);
        }
    }
};  

template<typename T>
class Allocator {
    Chunk *chunks;
public:
    using size_type = std::size_t;
    using pointer = T*;
    using value_type = T;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using difference_type = std::ptrdiff_t;
    template<class U> 
    struct rebind { typedef Allocator<U> other; };

    Allocator () : chunks(NULL) {;}

    Allocator (const Allocator &a) : chunks(a.chunks) {;}

    ~Allocator () {
        chunks->~Chunk();
        if (chunks != NULL) {
            delete chunks;
            std::cout << "Deallocating chunk!\n";
        }
    }

    template <typename ... Args>
    void construct (T* p, Args&&... args) {
        new (p) T(args...);
        return;
    };

    void destroy (T* p) {
        p->~T();
    };

    T* allocate (const size_t size) {
        if (chunks == NULL) { chunks = new Chunk; }        
        return (T*) chunks->memory_request(size * sizeof(T));
    };

    void deallocate (T*, const size_t n) {;}

    Allocator& operator= (Allocator const &a) {
        if(this != &a) {
            Allocator tmp(a);
            //this = &tmp;
            std::swap(tmp);
        }
        return *this;
        // ----  ;
    };

    size_t max_size () {
        return BLOCK_SIZE;
    }


    
private:
    
    //struct Chunk;
  
    
};
}