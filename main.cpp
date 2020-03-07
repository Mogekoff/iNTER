#include "iNTER.h"

int Foo(int a, int b) {				//Your function

	iNTER::Print(to_string(a + b));	//Correct cout print

	return a + b;
}


int main(int argc, char* argv[])
{
	iNTER I(argc,argv);

	int Result;
	I.AddFunction("foo", "Example function", [&Result, &I]() { Result = Foo(I.GetArgInt(), I.GetArgInt(1));  });

	//Try: "foo 3 5"

	//Autoexec Script before interactive interpreter
	//Comment this to prevent this execute
	I.ExecuteScript("ExampleScript.irp");

	return I.Interpreter();
}