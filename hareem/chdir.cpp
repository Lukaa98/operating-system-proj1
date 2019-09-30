#include <unistd.h>
#include <iostream>
using namespace std;

int main (int argc,char* argv[]) {
	// it is not possible to change the main directory
	// chdir creates a new process and changes the directory there
	// it returns a 0 if changing the directory was successful and -1 for faliure 

        int result = chdir("/home/hareem); 
        cout<<"0 is for success and -1 is for faliure in changing dir"<<endl;
        cout<<result<<endl;
        return 0;
}