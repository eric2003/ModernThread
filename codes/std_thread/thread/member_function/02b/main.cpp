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

	virtual void Wait()
	{
		if ( this->th_.joinable() )
		{
			this->th_.join();
		}
	}

	virtual void Stop()
	{
		this->is_exit_ = true;
		this->Wait();
	}

	bool is_exit() { return this->is_exit_; }

	virtual void Main() = 0;
private:
	std::thread th_;
	bool is_exit_ = false;
};

class TestXThread : public XThread
{
public:
	void Main() override
	{
		std::cout << "TestXThread Main begin " << " name = " << this->name << std::endl;

		while ( !this->is_exit() )
		{
			using namespace std::chrono_literals;
			std::this_thread::sleep_for(100ms);
			std::cout << "." << std::flush;
		}
		std::cout << "\nTestXThread Main End\n";
	}
public:
	std::string name = "TestXThread";
};

int main(int argc, char *argv[])
{
	TestXThread testThread;
	testThread.name = "Test name 001";
	testThread.Start();
	{
		using namespace std::chrono_literals;
		std::this_thread::sleep_for( 3s );
	}
	testThread.Stop();

    return 0;
}
