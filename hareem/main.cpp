#include <iostream>
#include <string>
#include <sys/param.h>
#include <unistd.h>
using namespace std;

int main (int argc,char* argv[]) {
	string  commands[5];
	// stores commands into a string array
	for (int i = 1; i < argc; i++) {
		commands[i] =  argv[i];
	}
	// depending on which command is chosing  statement is executed
	if (commands[1] == "list") {
	cout <<"success"<<endl;
	const char* arg[] = {"ls",(char*)NULL};
	execvp("ls",(char* const*)arg);
	}
	if (commands[1] == "printwd") {
	const char* arg[] = {"pwd",(char*)NULL};
        execvp("pwd",(char* const*)arg);
	}

	if (commands[1] == "history") {
	const char* arg[] = {"history",(char*)NULL};
        execvp("history",(char* const*)arg);
	}

	if (commands[1] == "chdir") {
	string newdir = commands[2];
	int result = chdir(newdir.c_str());
	const char* arg[] = {"ls",(char*)NULL};
        execvp("ls",(char* const*)arg);
	}

	if (commands[1] == "run") {
	string filename = commands[2];
	string slash = "./";
	string openfile = slash  + filename;
	const char* arg[] = {openfile.c_str(),(char*)NULL};
        execvp(openfile.c_str(),(char* const*)arg);
	}
	return 0;
}

