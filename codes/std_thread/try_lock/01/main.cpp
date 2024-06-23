#include <thread>
#include <iostream>
#include <string>
#include <vector>
#include <mutex>

int main(int argc, char *argv[])
{
    std::mutex mtx;
    if ( mtx.try_lock() )
    {
        std::cout << "000 succeed\n";
    }
    else
    {
        std::cout << "000 failed\n";
    }

    if ( mtx.try_lock() )
    {
        std::cout << "111 succeed\n";
    }
    else
    {
        std::cout << "111 failed\n";
    }
    mtx.unlock();


    return 0;
}
