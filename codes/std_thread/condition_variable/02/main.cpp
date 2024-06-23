#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>

int main(int argc, char *argv[])
{
    std::condition_variable cv;
    std::mutex mtx;
    bool ready = false;

    std::thread th( [&]() {
        std::unique_lock lck( mtx );
        cv.wait( lck, [&]() { return ready; } );
        lck.unlock();
        std::cout << "th is awake" << std::endl;
        });
    std::cout << "notifying is not ready" << std::endl;
    cv.notify_one(); // useless now, since ready = false
    ready = true;
    std::cout << "notifying ready" << std::endl;
    cv.notify_one(); //awakening th, since ready = true
    th.join();

    return 0;
}
