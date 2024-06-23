#include <thread>
#include <iostream>
#include <string>
#include <vector>
#include <mutex>

int main(int argc, char *argv[])
{
    std::timed_mutex mtx;
    if ( mtx.try_lock_for(std::chrono::milliseconds(500)) )
    {
        std::cout << "000 succeed\n";
    }
    else
    {
        std::cout << "000 failed\n";
    }

    if ( mtx.try_lock_for(std::chrono::milliseconds(500)) )
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
