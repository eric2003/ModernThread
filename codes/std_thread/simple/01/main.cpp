#include <thread>
#include <iostream>

void ThreadMain()
{
	std::cout << "begin thread main" << std::endl;
}

int main(int argc, char *argv[])
{
	//Create and start a thread
	std::thread th(ThreadMain);
	//Block and wait for the child thread to exit
	th.join();
    return 0;
}
