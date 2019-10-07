# cisc3320proj1-group9

The system-calls that we use for this shell project are: 
fork(); execvp(); wait(NULL); readline(); getcwd(); chdir();



```
Example: 

Directory: /home/angelo/group9Project/shellProj/cisc3320proj1-group9/angelo
[angelo_Shell]~> ls
finalshell.c  README.md  shell

[angelo_Shell]~> list
finalshell.c  README.md  shell

[angelo_Shell]~> pwd
/home/angelo/group9Project/shellProj/cisc3320proj1-group9/angelo

[angelo_Shell]~> printwd
/home/angelo/group9Project/shellProj/cisc3320proj1-group9/angelo

[angelo_Shell]~> cd ..

[angelo_Shell]~> printwd
/home/angelo/group9Project/shellProj/cisc3320proj1-group9

[angelo_Shell]~> chdir angelo/

[angelo_Shell]~> printwd
/home/angelo/group9Project/shellProj/cisc3320proj1-group9/angelo

[angelo_Shell]~> history

 1) ls
 2) list
 3) pwd
 4) printwd
 5) cd ..
 6) printwd
 7) chdir angelo/
 8) printwd
 9) history
[angelo_Shell]~> help

		 Help Menu:
-------------------------------------------------------

	 The commands that this Shell supports:
~> ls or list : for listing the the files and directory of your current Directory
~> pwd or printwd: Prints out the current working directory
~> cd .. -OR-  cd [stateDirectory]: to either go back to one directory; 
		 or change into a given directory
~> chdir .. -OR- chdir [state_directory]: to change directory
~> history: view the previously entered commands
~> Arrow key: Goes back to previously entered commands
~> Can run external programs: e.g firefox
~> exit: Terminates the shell

[angelo_Shell]~> exit

Thank you. Goodbye


```
