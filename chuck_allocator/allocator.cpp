#include "allocator.h"
#include <vector>
#include <iostream>

using namespace task;
class A {
    
public:
    int x;
    A (int x, int y) { /*std::cout << x << " " << y << "\n";*/ this->x = x;} 
    ~A () { /*std::cout << "~" << "\n";*/}
};

int main()
{
    Allocator<A> alloc;
    Allocator<A> alloc2;
    Allocator<int> allint;
    alloc2 = alloc;
    A* a[20];

    int *arr;
    int *arr2;
    int *arr3;
    arr = allint.allocate(500);
    arr2 = allint.allocate(500);
    arr3 = allint.allocate(10);
    std::cout << "Adress of arr1: " << arr << "\n";   // goes to 1st chunk
    std::cout << "Adress of arr2: " << arr2 << "\n";  // goes to 2nd chunk
    std::cout << "Adress of arr3: " << arr3 << "\n";  // goes to 1st chunk
    arr[9] = 1;
    arr2[9] = 2;
    arr3[9] = 3;
    arr[499] = 10;
    arr2[499] = 20;
    std::cout << " 1 = " << arr[9] << "\n";
    std::cout << " 2 = " << arr2[9] << "\n";
    std::cout << " 3 = " << arr3[9] << "\n";
    std::cout << "10 = " << arr[499] << "\n";
    std::cout << "20 = " << arr2[499] << "\n";
       
    std::vector<A, Allocator<A>> vec;
    for (int i = 0; i < 512; i++) vec.push_back(A(i, 2 * i));
    std::cout << "vec/[511/] = " << vec[511].x << "\n";
    for (int i = 0; i < 20; i++) 
    {
        if(i % 2) a[i] = alloc.allocate(1);
        else a[i] = alloc2.allocate(1);
        alloc.construct(a[i], i, 10);
    }

    std::cout << "a/[19/] = " << a[19]->x << "\n";
    
    //std::cout << vec2[1022].x << "\n";
    std::cout << " arr/[9/] = " << a[9]->x << "\n";
    std::cout << " &arr/[9/] = " << a[9] << "\n";
    
    std::cout << " arr/[9/] = " << a[10]->x << "\n";
    std::cout << " &arr/[9/] = " << a[10] << "\n";
    
    //vec.push_back(A(3, 4));
    
    

    return 0;
}