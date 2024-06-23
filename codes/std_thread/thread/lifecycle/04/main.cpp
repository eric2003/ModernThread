#include <thread>
#include <chrono>
#include <iostream>
bool is_exit = false;
void ThreadMain()
{
	using namespace std::chrono_literals;
	std::cout << "begin sub thread main " <<  std::this_thread::get_id() << std::endl;
	for ( int i = 0; i < 10; ++ i )
	{
		if ( is_exit ) break;
		std::cout << " in sub thread main loop i = " << i << std::endl;
		std::this_thread::sleep_for(1000ms);
	}
	std::cout << "end sub thread main " <<  std::this_thread::get_id() << std::endl;
}

int main(int argc, char *argv[])
{
	{
		std::thread th( ThreadMain );
		using namespace std::chrono_literals;
		std::this_thread::sleep_for( 3000ms );
		is_exit = true;
		std::cout << "The main thread is blocked, waiting for the child thread to exit\n";
		th.join();
		std::cout << "The child thread has exited\n";
	}
	//std::cin.get();
    return 0;
}
