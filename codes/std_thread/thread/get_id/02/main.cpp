#include <thread>
#include <iostream>

void ThreadMain()
{
	std::cout << "begin sub thread main " <<  std::this_thread::get_id() << std::endl;
}

int main(int argc, char *argv[])
{
	std::cout <<  "main thread ID " << std::this_thread::get_id() << std::endl;
	//Create and start a thread
	std::thread th(ThreadMain);
	//Block and wait for the child thread to exit
	th.join();
    return 0;
}
