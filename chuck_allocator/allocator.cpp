#include "allocator.h"

#include <iostream>
#include <vector>

using namespace task;
class A {
 public:
  int x;
  int y;
  A(int x, int y) {
    this->x = x;
    this->y = y;
  }
  ~A() { ; }
};

bool check_int_array() {
  Allocator<int> allint;

  int *arr;
  int *arr2;
  int *arr3;

  arr = allint.allocate(500);  // chunk is 2048b i.e. 512 * sizeof(int)
  arr2 = allint.allocate(500);
  arr3 = allint.allocate(10);

  if (arr3 - arr > 0x0800 || arr3 - arr < 0)
    return false;                                   // arr3 goes to 1st chunk
  for (int i = 0; i < 10; i++) arr3[i] = 1000 * i;  // filling arrays
  for (int i = 0; i < 500; i++) {
    arr[i] = i;
    arr2[i] = i + 1000;
  }

  for (int i = 0; i < 10; i++) {
    if (arr3[i] != 1000 * i) return false;  // checking for valid data
  }
  for (int i = 0; i < 500; i++) {
    if (arr[i] != i) return false;
    if (arr[i] != i + 1000) return false;
  }
  return true;
}

bool check_vector() {
  std::vector<A, Allocator<A>> vec;

  for (int i = 0; i < 256; i++)
    vec.push_back(
        A(i, 1000 + i));  // vector reallocates itself requiring 2nd chunk

  for (int i = 0; i < 256; i++) {
    if (vec[i].x != i) return false;         // checking for valid data
    if (vec[i].y != 1000 + i) return false;  // checking for valid data
  }
  return true;
}

bool check_copy() {
  Allocator<A> alloc;
  A *a[20];

  a[0] = alloc.allocate(1);  // allocating 1st chunk

  Allocator<A> alloc2 = alloc;  // copy alloc

  for (int i = 1; i < 20; i++) {
    if (i % 2)
      a[i] = alloc.allocate(1);  // allocating with alloc
    else
      a[i] = alloc2.allocate(1);         // allocating with alloc2
    alloc.construct(a[i], i, 1000 + i);  // filling array
  }

  for (int i = 0; i < 20; i++) {
    if (a[i]->x != i) return false;         // checking for valid data
    if (a[i]->y != 1000 + i) return false;  // checking for valid data
  }

  if (a[1] - a[0] != 8) return false;

  alloc2.~Allocator();  // destruct alloc2

  for (int i = 0; i < 20; i++) {
    if (a[i]->x != i)
      return false;  // checking for valid data after destructing one of the
                     // allocators
    if (a[i]->y != 1000 + i)
      return false;  // checking for valid data after destructing one of the
                     // allocators
  }

  return true;
}

int main() {
  if (check_int_array)
    std::cout << "Int array check valid!\n";
  else
    std::cout << "Int array check failed!\n";

  if (check_vector)
    std::cout << "Vector check valid!\n";
  else
    std::cout << "Vector check failed!\n";

  if (check_copy)
    std::cout << "Copy check valid!\n";
  else
    std::cout << "Copy check failed!\n";

  return 0;
}