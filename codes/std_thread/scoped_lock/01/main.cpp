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
            std::scoped_lock grd( mtx1, mtx2 );
        }
        });
    std::thread th2( [&]() {
        for ( int i = 0; i < 100000; ++i )
        {
            std::scoped_lock grd( mtx1, mtx2 );
        }
        });
    th1.join();
    th2.join();

    return 0;
}
