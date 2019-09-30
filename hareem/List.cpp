#include <unistd.h>
#include <iostream>
using namespace std;

int main (int argc,char* argv[]) {

        const char* arg[] = {"ls",(char*)NULL}; 
        execvp("ls",(char* const*)arg);

}

