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
        std::unique_lock grd( mtx, std::try_to_lock );
        if ( grd.owns_lock() )
        {
            std::printf("th1 success\n");
        }
        else
        {
            std::printf("th1 failed\n");
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        });
    std::thread th2( [&]() {
        std::unique_lock grd( mtx, std::try_to_lock );
        if ( grd.owns_lock() )
        {
            std::printf("th2 success\n");
        }
        else
        {
            std::printf("th2 failed\n");
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        });
    th1.join();
    th2.join();
    int kkk = 1;

    return 0;
}
