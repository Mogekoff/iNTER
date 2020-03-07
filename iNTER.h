#define _CRT_SECURE_NO_WARNINGS									//For unsafe funcs
#include <iostream>
#include <ctime>

#include <functional>

#include <thread>
#include <chrono>
#include <csignal>
#include <vector>
#include <fstream>

#include <queue>
#include <string>
#include <map>
#include <sstream>
#include <iterator> 

using namespace std;

class iNTER
{
private:
	queue	<pair<function<void()>,vector<string>>>		Queue;		//Queue Container of functions
	map		<string, pair<string, function<void()>>>	Functions;	//List of functions: CMDNAME | DESCRIPTION | POINTER
	static const short EXITCODE = 0;
	static const short INITCODE = 1;
	static const short RUNTIME = 2;
	const string VERSION = "0.4.0 unstable";
	
	string CurrentDirectory;
	
	vector<string> CurrentParameters;

	int Status;
	static void SigintHandler(int Signal);
	static void SigabrtHandler(int Signal);

	static string Time();

	void Executor();											//Executes every command in Queue Container
	static void Log(string Str);

public:

	iNTER(const int argc, char* argv[]);													//Contains basic commands
	int Interpreter(istream& STREAM = cin, string Input = "");											//Interpreter from stdin and adding to Queue Container

	int GetArgInt(unsigned NumberOfArgument = 0);
	string GetArgStr(unsigned NumberOfArgument = 0);
	static void Print(string Str);								//Formatted print to stdout
	void ExecuteCommand(string Cmd, vector<string> Parameters = vector<string>());
	void ExecuteScript(string Dir);
	
	void AddFunction(string CmdName,
		string CmdDescription,
		function<void()> CmdFunction);

};

//add cd
//add pwd

