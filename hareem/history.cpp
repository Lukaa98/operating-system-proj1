#include <unistd.h>
#include <iostream>
using namespace std;

int main (int argc,char* argv[]) {
                const char* arg[] = {"history",(char*)NULL};
                execvp("history",(char* const*)arg);
}
