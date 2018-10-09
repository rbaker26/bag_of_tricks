#include <iostream>
#include <memory>
#include <exception>
class A
{	int i;
	int j;
public:
	A(int i, int j)
	{   this->i = i; this->j = j;
		std::cout << "A constructor" << std::endl;
	}
	~A() { std::cout << "A deconstructor" << std::endl; }
	bool errorCheck() { if (i < 0) throw std::exception(); }
};
	int main()								// Output:
	{	// Scope Block
		{									// Output:
			A* aObj = new A(1, 2);			// A constructor
		}
		// aObj has popped off stack but the memory on the heap has not been freed
		// This is a memory leak.

		// Scope Block
		{														// Output:
			std::unique_ptr<A> uPtr = std::make_unique<A>(1, 2);// A constructor
			// std::unique_ptr<A> uPtr2 = uPtr;// compiler error
		}														// A deconstructor
																// Scope Block
		{														// Output:
			std::shared_ptr<A> uPtr = std::make_shared<A>(1, 2);// A constructor
			std::shared_ptr<A> uPtr2 = uPtr2; 					// A constructor
		}														// A deconstructor  
																//  (its only called once because both
																//   Ptrs shared one object)
		try // Try Block
		{														// Output:
			std::shared_ptr<A> uPtr = std::make_shared<A>(-1,1);// A constructor
			uPtr->errorCheck();									// Throws an error and jumps to catch block
																// A deconstructor
		} // A deconstructor is still called after throwing an exception												  
		catch (const std::exception& e) {}

		std::cin.get();
		return 0;
	}

