#include <thread>
#include <iostream>
#include <string>

void ThreadMain(int p1, float p2, std::string str)
{
	std::cout << "ThreadMain p1 = " << p1 << " p2 = " << p2 << " str = " << str << "\n";
}

int main(int argc, char *argv[])
{
	{
		float f1 = 3.12f;
		std::thread th( ThreadMain, 1234, f1, "test string para");
		th.join();
	}
    return 0;
}
