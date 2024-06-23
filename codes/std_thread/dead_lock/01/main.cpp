#include <thread>
#include <iostream>
#include <string>
#include <vector>
#include <mutex>

int main(int argc, char *argv[])
{
    std::mutex mtx1;
    std::mutex mtx2;
    std::thread th1( [&]() {
        for ( int i = 0; i < 100000; ++i )
        {
            mtx1.lock();
            mtx2.lock();
            mtx2.unlock();
            mtx1.unlock();
        }
        });
    std::thread th2( [&]() {
        for ( int i = 0; i < 100000; ++i )
        {
            mtx2.lock();
            mtx1.lock();
            mtx1.unlock();
            mtx2.unlock();
        }
        });
    th1.join();
    th2.join();

    return 0;
}
