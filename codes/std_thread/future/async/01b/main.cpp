#include <thread>
#include <future>
#include <iostream>
#include <string>

int download(const std::string &file)
{
    for ( int i = 0; i < 10; ++ i )
    {
        std::cout << "Downloading " << file
            << " (" << i * 10 << "%)..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    std::cout << "Download complete: " << file << std::endl;
    return 404;
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
    std::future<int> fret = std::async( []() {
        return download( "hello.zip" );
        }
    );
    interact();
    while ( true )
    {
        std::cout << "Waiting for download complete... " << std::endl;
        auto stat = fret.wait_for( std::chrono::milliseconds( 1000 ) );
        if ( stat == std::future_status::ready )
        {
            std::cout << "Future is ready!!!" << std::endl;
            break;
        }
        else
        {
            std::cout << "Future is not ready!!!" << std::endl;
        }
    }
    std::cout << "Wait returned!" << std::endl;
    int ret = fret.get();
    std::cout << "Download result: " << ret << std::endl;

    return 0;
}
