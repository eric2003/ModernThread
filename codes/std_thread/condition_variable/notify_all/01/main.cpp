#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>

int main(int argc, char *argv[])
{
    std::condition_variable cv;
    std::mutex mtx;
    bool ready = false;

    std::thread th1( [&]() {
        std::unique_lock lck( mtx );
        cv.wait( lck );
        std::cout << "th1 is awake" << std::endl;
        });
    std::thread th2( [&]() {
        std::unique_lock lck( mtx );
        cv.wait( lck );
        std::cout << "th2 is awake" << std::endl;
        });
    std::thread th3( [&]() {
        std::unique_lock lck( mtx );
        cv.wait( lck );
        std::cout << "th3 is awake" << std::endl;
        });
    std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );
    std::cout << "notifying one" << std::endl;
    cv.notify_one(); // awakening th1 only

    std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );
    std::cout << "notifying all" << std::endl;
    cv.notify_all(); //awakening th2 and th3
    th1.join();
    th2.join();
    th3.join();

    return 0;
}
