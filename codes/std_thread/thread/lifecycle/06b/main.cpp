#include <thread>
#include <iostream>
#include <string>

class Para
{
public:
	Para() { std::cout << "Create Para\n"; }
	Para( const Para & p ) { std::cout << "Copy Para\n"; this->name = p.name; }
	~Para() { std::cout << "Drop Para\n"; }
	std::string name= "Para-name";
};

void ThreadMainPtr(Para *p)
{
	using namespace std::chrono_literals;
	std::cout << "begin sub thread main " <<  std::this_thread::get_id() << std::endl;
	for ( int i = 0; i < 10; ++ i )
	{
		std::cout << " in sub thread main loop i = " << i << std::endl;
		std::this_thread::sleep_for(1000ms);
	}
	std::cout << "ThreadMainPtr name = " << p->name << "\n";
}

int main(int argc, char *argv[])
{
	std::thread th;
	{
		Para p;
		p.name = "test Para class";
		th = std::thread( ThreadMainPtr, &p);
	}
	th.join();

    return 0;
}
