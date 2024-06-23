#include <thread>
#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include <condition_variable>


int main(int argc, char *argv[])
{
    std::condition_variable cv;
    std::mutex mtx;

    std::thread th( [&]() {
        std::unique_lock lck( mtx );
        cv.wait( lck );
        std::cout << "th is awake" << std::endl;
        });
    std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );

    std::cout << "notifying..." << std::endl;
    cv.notify_one(); // will awake th
    th.join();

    return 0;
}
