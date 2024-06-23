#include <thread>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    std::thread th( []( int i ) {
        std::cout << "test lambda i = " << i << "\n";
        }, 123
    );
    th.join();

    return 0;
}
