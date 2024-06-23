#include <thread>
#include <iostream>
#include <string>
#include <vector>

class ThreadPool
{
public:
    ~ThreadPool()
    {
        for ( auto & t : this->m_pool )
        {
            t.join();
        }
    }
    void push_back( std::thread th )
    {
        this->m_pool.push_back( std::move( th ) );
    }
private:
    std::vector<std::thread> m_pool;
};

ThreadPool threadPool;

void download(const std::string &file)
{
    for ( int i = 0; i < 10; ++ i )
    {
        std::cout << "Downloading " << file
            << " (" << i * 10 << "%)..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    std::cout << "Download complete: " << file << std::endl;
}

void interact()
{
    std::string name;
    std::cout << "Input name: " << std::endl;
    std::cin >> name;
    std::cout << "Hi, " << name << std::endl;
}

void myfunc()
{
    std::thread th( []() {
        download( "hello.zip" );
        }
    );
    threadPool.push_back(std::move(th));
}

int main(int argc, char *argv[])
{
    myfunc();
    interact();

    return 0;
}
