#include <thread>
#include <iostream>
#include <string>

class XThread
{
public:
	virtual void Start()
	{
		this->th_ = std::thread( &XThread::Main, this );
	}
	virtual void Main() = 0;
private:
	std::thread th_;
};

class TestXThread : public XThread
{
public:
	void Main()
	{
		std::cout << "TestXThread Main " << " name = " << this->name << std::endl;
	}
public:
	std::string name = "TestXThread";
};

int main(int argc, char *argv[])
{
	TestXThread testThread;
	testThread.name = "Test name 001";
	testThread.Start();
	std::cin.get();

    return 0;
}
