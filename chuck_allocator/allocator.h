#pragma once
#include <iostream>

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
      this->next = NULL;
    }
  }

  char *memory_request(const size_t size) {
    if (size > BLOCK_SIZE) return NULL;
    if (size <= this->remainder) {
      // std::cout << "size ok! \n";
      this->current += size;
      this->remainder -= size;
      return (this->current - size);
    } else if (this->next != NULL) {
      // std::cout << "Requesting next! \n";
      return this->next->memory_request(size);
    } else {
      // std::cout << "Creating new! \n";
      this->next = new Chunk();
      return this->next->memory_request(size);
    }
  }
};

template <typename T>
class Allocator {
  size_t *chunk_counter;
  Chunk *chunks;  // pointer to 1st chunk
 public:
  using size_type = std::size_t;
  using pointer = T *;
  using value_type = T;
  using const_pointer = const T *;
  using reference = T &;
  using const_reference = const T &;
  using difference_type = std::ptrdiff_t;
  template <class U>
  struct rebind {
    typedef Allocator<U> other;
  };

  Allocator() {
    chunks = NULL;
    chunk_counter = new size_t(0);
  }

  Allocator(const Allocator &a)
      : chunks(a.chunks), chunk_counter(a.chunk_counter) {
    *this->chunk_counter += 1;  // remeber copy
  }

  ~Allocator() {
    if (*this->chunk_counter == 1) {  // check for active copy
      if (chunks != NULL) {
        chunks->~Chunk();
        delete chunks;
      }
    } else if (*this->chunk_counter > 0)
      *this->chunk_counter -=
          1;  // if no chunk was created, no need to decrease chunk_counter
  }

  template <typename... Args>
  void construct(T *p, Args &&... args) {
    new (p) T(args...);
    return;
  };

  void destroy(T *p) { p->~T(); };

  T *allocate(const size_t size) {
    if (chunks == NULL) {
      chunks = new Chunk;  // allocate on demand
      *chunk_counter = 1;  // remember 1st chunk
    }
    return (T *)chunks->memory_request(size * sizeof(T));
  };

  void deallocate(T *, const size_t n) { ; }

  Allocator &operator=(Allocator const &a) {
    if (this != &a) {
      Allocator tmp(a);  // copy constructor
      this = &tmp;
    }
    return *this;
  };

  size_t max_size() { return BLOCK_SIZE; }
};
}  // namespace task