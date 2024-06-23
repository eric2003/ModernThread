#include <thread>
#include <iostream>
#include <string>

void ThreadMain(int p1, float p2, std::string str)
{
	using namespace std::chrono_literals;
	std::cout << "begin sub thread main " <<  std::this_thread::get_id() << std::endl;
	for ( int i = 0; i < 10; ++ i )
	{
		std::cout << " in sub thread main loop i = " << i << std::endl;
		std::this_thread::sleep_for(1000ms);
	}
	std::cout << "ThreadMain p1 = " << p1 << " p2 = " << p2 << " str = " << str << "\n";
}

int main(int argc, char *argv[])
{
	std::thread th;
	{
		float f1 = 3.12f;
		th = std::thread( ThreadMain, 1234, f1, "test string para");
	}
	th.join();
    return 0;
}
