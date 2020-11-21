#pragma once

namespace task {

template <class T>
class WeakPtr;

template <class T>
class UniquePtr {
  T* ptr;

 public:
  // ptr constructor
  explicit UniquePtr(T* p) noexcept : ptr(p) { ; };

  // unique constructor
  UniquePtr(UniquePtr& other) = delete;
  UniquePtr(UniquePtr&& other) noexcept : ptr(nullptr) {
    std::swap(ptr, other.ptr);
  };

  // destructor
  ~UniquePtr() { delete ptr; };

  // operators
  UniquePtr& operator=(UniquePtr& other) = delete;
  UniquePtr& operator=(UniquePtr&& other) noexcept {
    if (*this == other) return *this;
    delete ptr;
    ptr = nullptr;
    std::swap(ptr, other.ptr);
    return *this;
  };

  T& operator*() { return *ptr; }
  T* operator->() { return ptr; }

  bool operator==(const UniquePtr<T>& other) {
    return (this->ptr == other.ptr);
  }

  // standart methods
  T* release() noexcept {
    T* result = nullptr;
    std::swap(result, ptr);
    return result;
  }

  void swap(UniquePtr& other) noexcept { std::swap(ptr, other.ptr); }

  T* get() const { return ptr; }

  void reset() {
    T* tmp = release();
    delete tmp;
  }
};  // unique ptr

template <class T>
struct ControlBlock {
  T* ptr;
  size_t sp_count;
  size_t wp_count;

  ControlBlock() : ptr(nullptr), sp_count(0), wp_count(0){};
  ControlBlock(T* p, size_t sp_c, size_t wp_c)
      : ptr(p), sp_count(sp_c), wp_count(wp_c){};
};

template <class T>
class SharedPtr {
 public:
  ControlBlock<T>* cb;

  // ptr constructor

  explicit SharedPtr(T* p) : cb(new ControlBlock<T>(p, 1, 0)) {
    // cb = new ControlBlock<T>(p, 1, 0);
  }

  SharedPtr() : cb(new ControlBlock<T>(nullptr, 1, 0)) {
    // cb = new ControlBlock<T>(nullptr, 1, 0);
  }

  // shared constructor

  SharedPtr(SharedPtr& other) : cb(other.cb) { ++cb->sp_count; }

  SharedPtr(const SharedPtr& other) : cb(other.cb) { ++cb->sp_count; }

  SharedPtr(SharedPtr&& other) {
    cb = std::move(other.cb);
    other.cb = new ControlBlock<T>();
  }

  // weak constructor

  SharedPtr(WeakPtr<T>& other) : cb(other.cb) { ++cb->sp_count; }

  SharedPtr(const WeakPtr<T>& other) : cb(other.cb) { ++cb->sp_count; }

  // destructor

  ~SharedPtr() {
    if (cb->sp_count == 1) {
      delete cb->ptr;
      if (cb->wp_count == 0) delete cb;
    }
    --cb->sp_count;
  }

  // operator =

  SharedPtr& operator=(const SharedPtr& other) {
    if (this == &other || cb == other.cb) return *this;
    this->~SharedPtr();
    cb = other.cb;
    ++cb->sp_count;
    return *this;
  }

  SharedPtr& operator=(SharedPtr&& other) noexcept {
    if (this == &other || cb == other.cb) return *this;
    SharedPtr<T>(std::move(other)).swap(*this);
    return *this;
  };

  // other operators

  T& operator*() { return *(cb->ptr); }

  T* operator->() { return cb->ptr; }

  bool operator==(const SharedPtr<T>& other) { return (this->cb == other.cb); }

  // standart methods

  T* get() const { return cb->ptr; }

  T* release() noexcept {
    ControlBlock<T>* buf = nullptr;
    std::swap(cb, buf);
    --buf->sp_count;
    return buf->ptr;
  }

  void swap(SharedPtr<T>& other) noexcept { std::swap(other.cb, this->cb); }

  void reset() { SharedPtr<T>().swap(*this); }

  template <class Y>
  void reset(Y* ptr) {
    SharedPtr<Y>(ptr).swap(*this);
    return;
  };

  size_t use_count() { return cb->sp_count; }
};  // shared ptr

template <class T>
class WeakPtr {
  // ControlBlock<T> *cb;
 public:
  ControlBlock<T>* cb;

  // ptr constructor

  WeakPtr() : cb(new ControlBlock<T>(nullptr, 0, 0)) { ; }
  explicit WeakPtr(T* p) : cb(new ControlBlock<T>(p, 0, 1)) { ; }

  // weak constructor

  WeakPtr(WeakPtr& other) : cb(other.cb) { ++cb->wp_count; }

  WeakPtr(WeakPtr&& other) {
    cb = std::move(other.cb);
    other.cb = new ControlBlock<T>();
    ++other.cb->wp_count;
    ++cb->wp_count;
  }

  WeakPtr(const WeakPtr& other) : cb(other.cb) { ++cb->wp_count; }

  // shared constructor

  WeakPtr(const SharedPtr<T>& other) : cb(other.cb) { ++cb->wp_count; }

  // destructor

  ~WeakPtr() {
    if (cb->wp_count == 0 && cb->sp_count == 0) {
      delete cb;
    }
    --cb->wp_count;
  };

  // shared operator =

  WeakPtr& operator=(const SharedPtr<T>& other) {
    cb = other.cb;
    ++cb->wp_count;
    return *this;
  };

  WeakPtr& operator=(SharedPtr<T>& other) {
    cb = other.cb;
    ++cb->wp_count;
    return *this;
  };

  // weak operator =

  WeakPtr& operator=(const WeakPtr<T>& other) {
    if (this == & other || cb = other.cb) return *this;
    cb = other.cb;
    ++cb->wp_count;
    return *this;
  };

  WeakPtr& operator=(WeakPtr<T>&& other) noexcept {
    if (this == & other || cb = other.cb) return *this;
    WeakPtr<T>(std::move(other)).swap(*this);
    return *this;
  };

  // standart methods

  void swap(WeakPtr& other) noexcept { std::swap(this->cb, other.cb); }

  void reset() { WeakPtr<T>().swap(*this); }

  size_t use_count() {
    if (cb == nullptr) return 0;
    return cb->sp_count;
  }

  bool expired() {
    if (cb == nullptr || this->cb->sp_count == 0) return true;
    return false;
  }

  SharedPtr<T> lock() noexcept {
    return (expired() ? SharedPtr<T>() : SharedPtr<T>(*this));
  }
};  // weak ptr

}  // namespace task

#include "smart_pointers.tpp"
