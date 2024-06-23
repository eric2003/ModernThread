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
        std::unique_lock grd( mtx);
        std::printf("th1 owns the lock\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        });
    std::thread th2( [&]() {
        mtx.lock();
        std::unique_lock grd( mtx, std::adopt_lock );
        std::printf("th2 owns the lock\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        });
    th1.join();
    th2.join();

    return 0;
}
