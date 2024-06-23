#include <thread>
#include <iostream>
#include <string>

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

int main(int argc, char *argv[])
{
    std::thread th( []() {
        download( "hello.zip" );
        }
    );
        
    interact();

    th.detach();

    return 0;
}
