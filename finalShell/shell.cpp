#include <stdio.h>
#include <cstdlib>
#include <sys/wait.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
vector<string> history;

void read_command (char cmd[], char *par[]) {
	char line[1024];
	int count=0, i=0, j=0;
	char *array[100], *pch;

	//Read line - one at a time
	for ( ;; ) {
		int c = fgetc(stdin);
		line[count++] = (char) c;
		if (c == '\n') break;
	}
	if (count == 1) return;
	history.push_back(line);
	pch = strtok (line, " \n");

	//parse into words and put in array
	while (pch != NULL) {
		array[i++] = strdup (pch);
		pch = strtok (NULL, " \n");
	}

	//command has to be the first word
	strcpy(cmd,array[0]);

	for (int j=0; j<i; j++)
		par[j] = array[j];
	par[i] = NULL; //to terminate 
}

void type_prompt() {
	static int first_time = 1;
	if (first_time) { //clear screen 
		const char* CLEAR_SCREEN = " \e[1;1H\e[2J";
		write(STDOUT_FILENO, CLEAR_SCREEN, 12);
		first_time = 0;
	}
	printf(">"); //display terminal
}

int main() {
	char cmd[50], command[50], *parameters[20];
	char *envp[] = { (char *) "PATH=/bin", 0};
	while (1) {				//repeat until exited from terminal by user
		type_prompt();		//display prompt on screen
		read_command (command, parameters); //read input commands
		if (strcmp(command,"printwd")==0) {
			char directory[1024];
			getwd(directory);
			printf("%s\n",directory );
		}
		else if (strcmp(command,"chdir")==0) {
			string newdir = parameters[1];
			int result = chdir(newdir.c_str());
		}
		else if (strcmp(command,"run")==0) {
			if (fork()!=0)		
				wait(NULL);	
			else {
				execv(parameters[1],NULL);
			}
		}
		else if (strcmp(command,"list")==0) {
			system("ls");
		}
		else if (strcmp(command,"history")==0) {
			for (int i = 0; i < history.size(); i++) {
				printf("%s",history.at(i).c_str() );
			}
		}

		else if (strcmp (command, "exit" ) == 0)
			break;
		else 
			printf("%s\n", "command not supported");
	}
	return 0;
}
