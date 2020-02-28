#define _CRT_SECURE_NO_WARNINGS									//For unsafe funcs
#include <iostream>
#include <ctime>

#include <functional>

#include <thread>
#include <chrono>
#include <csignal>

#include <fstream>

#include <queue>
#include <string>
#include <map>

using namespace std;

class iNTER
{
private:
	queue	<function<void()>>						Queue;		//Queue Container of functions
	map		<string, pair<string, function<void()>>>	Functions;	//List of functions: CMDNAME | DESCRIPTION | POINTER
	static const short EXITCODE = 0;
	static const short INITCODE = 1;
	static const short RUNTIME = 2;

	int Status;
	static void SigintHandler(int Signal);
	static void SigabrtHandler(int Signal);

	string Arguments;
	static string Time();

	void Executor();											//Executes every command in Queue Container
	static void Log(string Str);

public:

	iNTER();													//Contains basic commands
	int Interpreter();											//Interpreter from stdin and adding to Queue Container

	static void Print(string Str);								//Formatted print to stdout
	void AddFunction(string CmdName,
		string CmdDescription,
		function<void()> CmdFunction);

};

//add cd
//add pwd

