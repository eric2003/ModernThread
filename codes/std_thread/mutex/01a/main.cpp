#include <thread>
#include <iostream>
#include <string>
#include <vector>
#include <mutex>

int main(int argc, char *argv[])
{
    std::vector<int> arr;
    std::mutex mtx;
    std::thread th1( [&]() {
        for ( int i = 0; i < 10000; ++i )
        {
            mtx.lock();
            arr.push_back(i);
            mtx.unlock();
        }
        });
    std::thread th2( [&]() {
        for ( int i = 0; i < 10000; ++i )
        {
            mtx.lock();
            arr.push_back(i+10000);
            mtx.unlock();
        }
        });
    th1.join();
    th2.join();
    int kkk = 1;

    return 0;
}
