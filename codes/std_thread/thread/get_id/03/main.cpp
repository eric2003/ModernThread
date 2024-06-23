#include <thread>
#include <chrono>
#include <iostream>

void ThreadMain()
{
	using namespace std::chrono_literals;
	std::cout << "begin sub thread main " <<  std::this_thread::get_id() << std::endl;
	for ( int i = 0; i < 10; ++ i )
	{
		std::cout << " in sub thread main loop i = " << i << std::endl;
		std::this_thread::sleep_for(1000ms);
	}
	std::cout << "end sub thread main " <<  std::this_thread::get_id() << std::endl;
}

int main(int argc, char *argv[])
{
	std::cout <<  "main thread ID " << std::this_thread::get_id() << std::endl;
	//Create and start a thread
	std::thread th(ThreadMain);
	std::cout <<  "begin wait sub thread " << std::endl;
	//Block and wait for the child thread to exit
	th.join();
	std::cout <<  "after th.join()  " << std::endl;
    return 0;
}
