#include <unistd.h>
#include <iostream>
using namespace std;

int main (int argc,char* argv[]) {
        const char* arg[] = {"pwd",(char*)NULL};
        execvp("pwd",(char* const*)arg);


        return 0;
}