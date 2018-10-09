#include <iostream>
#include <vector>

class A 
{
public:
    A(int i) : i(i) {}
    A(const A& a)
    {
        std::cout << "Copyied " << a.i << std::endl;
    }
private:
    int i;
};

int main()
{
    // The vector has to resize after each object is pushed on 
    // the vector.  The copy-constructor is also called when an 
    // object is contructed and copied to the vector.
    std::vector<A> vA;
    vA.push_back(A(1));
    vA.push_back(A(2));
    vA.push_back(A(3));

    std::cout << "\n\n****************************************\n\n";

    // The vector nolonger resizes, causing copies, but
    // copies are still made everytime an object is put on the 
    // vector.
    std::vector<A> vA_optimized;
    vA_optimized.reserve(5);
    vA_optimized.push_back(A(4));
    vA_optimized.push_back(A(5));
    vA_optimized.push_back(A(6));
    
    std::cout << "\n\n****************************************\n\n";

    // The vector never resized, unless more than 5 objects are put
    // on.  Emplace_back avoids calling copy-constructor by calling the 
    // default-contructor in the memory of the vector.
    std::vector<A> vA_super_optimized;
    vA_super_optimized.reserve(5);
    vA_super_optimized.emplace_back(4);
    vA_super_optimized.emplace_back(5);
    vA_super_optimized.emplace_back(6);
    std::cout << "No copies!!!\n";
    return 0;
}
// Output:
// rbaker@DESKTOP-EUK8SOJ:/mnt/c/Users/007ds/Desktop$ ./vector_test
// Copyied 1
// Copyied 2
// Copyied 0
// Copyied 3
// Copyied 0
// Copyied 0


// ****************************************

// Copyied 4
// Copyied 5
// Copyied 6


// ****************************************

// No copies!!!