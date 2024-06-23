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
            std::lock_guard grd( mtx );
            arr.push_back(i);
        }
        });
    std::thread th2( [&]() {
        for ( int i = 0; i < 10000; ++i )
        {
            std::lock_guard grd( mtx );
            arr.push_back(i+10000);
        }
        });
    th1.join();
    th2.join();
    int kkk = 1;

    return 0;
}
