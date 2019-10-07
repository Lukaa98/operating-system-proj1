#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include<sys/types.h> 
#include<sys/wait.h> 
#include<readline/readline.h> 
#include<readline/history.h> 

//Declarations
#define MAX_length 500 //The max length of a command
#define BUFFER_SIZE 100
 
int history_counter =0;

void execCommand(char **parsed2);

//To print out the help Menu
void help_call(){
  puts("\n\t\t Help Menu:"
  "\n-------------------------------------------------------"
  "\n\n\t The commands that this Shell supports:"
  "\n~> ls or list : for listing the the files and directory of your current Directory"
  "\n~> pwd or printwd: Prints out the current working directory"
  "\n~> cd .. -OR-  cd [stateDirectory]: to either go back to one directory; "
  "\n\t\t or change into a given directory"
  "\n~> chdir .. -OR- chdir [state_directory]: to change directory"
  "\n~> history: view the previously entered commands"
  "\n~> Arrow key: Goes back to previously entered commands"
  "\n~> exit: Terminates the shell"
  );
}

//Function to print the Current Directory [DONE]
void printDirectory(){

  char cwd[1024]; //The buffer to hold the path name of working directory
  getcwd(cwd, sizeof(cwd));
  printf("\nDirectory: %s", cwd); 
 
}

//Get input from user and put into history buffer [DONE]
int retrieveInput(char * user, char ** hist){
  char* buff;

  buff = readline("\n[angelo_Shell]~> ");
  if(strlen(buff)!=0 ){
    add_history(buff); //Add the command into history and can reuse using Up-arrow
    strcpy(user, buff); //copies the keyboard input into the user-ptr
    
    //This adds the command into the history array
    hist[history_counter] = buff;
    history_counter ++; //Increments the global variable to keep pushing to the array
    

    return 0;
  }else{
    return 1;
  }
}

//To print the history of commands entered
void print_history(char ** historyList){

    int n;
    for(n=0; n < BUFFER_SIZE; n++){
      if(historyList[n] != NULL){
        printf("\n %d) %s", (n+1), historyList[n] );
      }
      else break;
    }
}

//This is tokenize the string, and ignore the whitespaces [DONE]
void parseSpace(char * str, char ** parsed2){
  
  int n; 
  
  for(n = 0; n < BUFFER_SIZE; n++){ //Loop to parse the command into an array
    //parsed2[n] = strtok(&str, " "); //Using the strtok to specify a delimiter
    parsed2[n] = strsep(&str, " ");
    if(parsed2[n] == NULL){ //If the string is done tokenizingor empty, will break the loop
      break;
    }
    if(strlen(parsed2[n]) == 0){ // is the command had nothing
      n --; 
    }

  }
}

// Builtin commands that we implemented into the shell
int myCommands(char ** parsed2, char** historyList){

  int num_myCmds =5; //This will hold the # of builtin commands we are using
  int i;
  int switchOwnArgs =0;
  char* myCmds[num_myCmds];  
  char * username;

  myCmds[0] = "exit";
  myCmds[1] = "cd" ;
  myCmds[2] = "help";
  myCmds[3] = "history";
  myCmds[4] = "chdir";
 /*
  The purpose of this loop is to determine is whats in our tokenize array called parsed[0] is equal to our BUILTIN commands. If it is, we can run our switch cases
 */
  for(i = 0; i < num_myCmds; i++){
    
    if(strcmp(parsed2[0], myCmds[i]) == 0  ){ //If ListOfOwnCmds[i] is EQUAL to our first command store in parsed2-first element. We Break the loop
      switchOwnArgs = i + 1;
      break;
  }
}
  switch (switchOwnArgs){
    case 1:
      printf("\nThank you. Goodbye\n");
      exit(EXIT_SUCCESS); 
    case 2:
    case 5: //Both case (2&5) will use the chdir function
      chdir(parsed2[1]); // Will change to the directory in parsed2 following the directory name. EX: input: [cd testMe] will go into the testMe DIR
      return 1;
    case 3:
      help_call(); //Will print out the help menu
      return 1;
    case 4:
      print_history(historyList); //Will print out the history of entered commands
      return 1;
    default: 
      break;
  }
  return 0;
}


//To process the user string 
int organizeInput(char * user, char ** parsed, char **historyList){
//LEFT OFF HERE, 
  int piped =0;
  parseSpace(user, parsed); //Will call the f() and set parsed with an array of tokenized items, disregarding the blank-spaces

  if(myCommands(parsed, historyList)){ //if YES, the command entered was builtin
    return 0;
  } 
  else 
    return 1+ piped; /*This means that the execFlag will be set to 1. 
  Therefore, it is a simple command outside of the builtin commands that will run through the forked process */

}

//Will run system-commands like ls or pwd, through the forking of process
void execCommand(char ** parsed2){

  //Forking a child process
  pid_t pid = fork();

  if(pid ==-1){
    printf("\nThe forking failed...");
    return;
  } else if(pid ==0){ //This is for the child process
      //This will execute the system-commande, overwriting the old cold with this new procedure
      execvp(parsed2[0], parsed2);
      printf("Unknown command...");
      exit(0);
  }
  else {
    //The parent process waits for the child process to Terminates
    wait(NULL);
    return;
  }

}


int main(void){

  char inputUser[MAX_length]; //To hold the user inputBuffer
  char *tokenizedCmds[MAX_length];
  char *historyList[MAX_length]; //Will hold the history Array of commands
  int notifyMark =0;
  /*notifyMark:
  return value of 0 if the command was builtin
  return value 1, if the command was simple command like running external program.
  return value 1 will create a child process
  */

  printDirectory(); //Prints our the current directory

  while(1) { // Infinite loop that will keep running till execflag returns 0
    

    //take userinput 
    if(retrieveInput(inputUser, historyList) ){
      continue;
    }
    //Process the input; will tokenize it
    notifyMark = organizeInput(inputUser, tokenizedCmds, historyList);

    //If-statements used incase user input "list" or "printwd"
	// to change into ls, pwd , respectively.
    if(strcmp(tokenizedCmds[0], "list") == 0) tokenizedCmds[0] = "ls";
    if(strcmp(tokenizedCmds[0], "printwd") == 0) tokenizedCmds[0] = "pwd";

    //Will run the fork() if the command is ls, pwd 
    if(notifyMark ==1){
      execCommand(tokenizedCmds);
    }

  }

  return 0;
}
