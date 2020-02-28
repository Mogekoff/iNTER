#include "iNTER.h"

int Foo(int a, int b) {				//Your function

	iNTER::Print(to_string(a + b));	//Correct cout print

	return a + b;
}


int main()
{
	iNTER I;

	int Result;
	I.AddFunction("foo", "Example function", [&Result]() { this_thread::sleep_for(10s); Result = Foo(4, 10);  });

	//Try: foo foo exit

	return I.Interpreter();
}