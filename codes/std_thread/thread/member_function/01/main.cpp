#include <thread>
#include <iostream>
#include <string>

class MyThread
{
public:
	void Main()
	{
		std::cout << "MyThread Main " << this->name << "\n";
	}
	std::string name= "MyThread-name";
};

int main(int argc, char *argv[])
{
	MyThread myThread;
	myThread.name = "Test name 001";
	std::thread th( &MyThread::Main, &myThread);
	th.join();

    return 0;
}
