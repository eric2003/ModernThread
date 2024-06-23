#include <thread>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::jthread> pool;

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
    std::jthread th( []() {
        download( "hello.zip" );
        }
    );
    pool.push_back(std::move(th));
}

int main(int argc, char *argv[])
{
    myfunc();
    interact();

    return 0;
}
