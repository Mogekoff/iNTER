#include "iNTER.h"

iNTER::iNTER() {
	Status = INITCODE;

	AddFunction("exit", "Exit from program", [=]() {
		cout << '\b';
		Status = EXITCODE;
		});

	AddFunction("version", "Print current version of program", [=]() {
		Print("Current version of iNTER is 0.2.4");
		});

	AddFunction("help", "Print this list of all available commands", [=]() {
		string List = "List of available commands:\n";
		for (auto i : Functions)
			List += i.first + "\t\t" + i.second.first + '\n';
		List.pop_back();
		Print(List);
		});

	AddFunction("clear", "Clear terminal", [=]() {
		cout << "\033[2J\033[1;1H>";
		});

	AddFunction("exec", "Execute typed command by system shell", [=]() {
		system(Arguments.c_str());
		Print(">");
		});

	signal(SIGINT, iNTER::SigintHandler);

	Print("Starting...");
}

int iNTER::Interpreter() {
	Status = RUNTIME;
	thread ExThread(&iNTER::Executor, this);

	string Input;
	string Command;

	while (getline(cin, Input)) {

		Log('>' + Input);
		Print(">");

		if (Input.empty()) {
			Print(">");
			continue;
		}

		auto Temp = Input.find(' ');
		Command = Input;

		if (Temp != -1) {
			Command = Input.substr(0, Temp);
			Arguments = Input.substr(Temp, Input.back());
		}

		auto Iterator = Functions.find(Command);

		if (Iterator != Functions.end())
			Queue.push(Iterator->second.second);
		else
			Print("Command \'" + Command + "\' is not found. Type 'help' to see a list of available commands.");

		if (Command == "exit") {
			this_thread::sleep_for(1ms);

			if (!Queue.empty())
				Print("Waiting for the execution of the remaining commands...");

			ExThread.join();

			Print("Exiting..."); cout << '\b';
			Log("Program exited with code " + to_string(EXITCODE));

			return EXITCODE;
		}
	}
	return SIGINT;
}

void iNTER::Executor() {
	while (Status == RUNTIME)
		while (!Queue.empty()) {
			Queue.front()();
			Queue.pop();
		}
}

void iNTER::Print(string Str) {
	if (Str == ">")
		cout << "\b>";
	else {
		string Output = Time() + Str;
		cout << '\b' << Output << endl << '>';
		Log(Output);
	}
}

void iNTER::Log(string Str) {
	ofstream File("Log.txt", ios_base::app);
	File << Str << endl;
	File.close();
}

void iNTER::AddFunction(string CmdName, string CmdDescription, function<void()> CmdFunction) {
	Functions[CmdName] = { CmdDescription, CmdFunction };
}

string iNTER::Time() {
	time_t Temp = time(NULL);
	tm* Time = localtime(&Temp);
	return '[' + to_string(Time->tm_hour) + ':' + to_string(Time->tm_min) + ':' + to_string(Time->tm_sec) + "] ";
}

void iNTER::SigintHandler(int Signal) {
	Log('[' + to_string(Signal) + "] Terminated by user pressing CTLR+C");
}

void iNTER::SigabrtHandler(int Signal) {
	Log('[' + to_string(Signal) + "] Terminated by abort()");
}


