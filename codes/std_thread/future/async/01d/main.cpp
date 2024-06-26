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
    std::promise<int> pret;
    std::thread th( [&]() {
        auto result = download( "hello.zip" );
        pret.set_value( result );
        }
    );
    std::future<int> fret = pret.get_future();
    interact();
    int ret = fret.get();
    std::cout << "Download result: " << ret << std::endl;
    th.join();

    return 0;
}
