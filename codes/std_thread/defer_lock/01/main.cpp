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
        for ( int i = 0; i < 100; ++i )
        {
            std::unique_lock grd( mtx );
            arr.push_back(i);
        }
        });
    std::thread th2( [&]() {
        for ( int i = 0; i < 100; ++i )
        {
            std::unique_lock grd( mtx, std::defer_lock );
            grd.lock();
            arr.push_back(i+10000);
            grd.unlock();
            //std::cout << "outside of lock, i = " << i<< "\n";
        }
        });
    th1.join();
    th2.join();
    int kkk = 1;

    return 0;
}
