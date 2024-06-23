#include <thread>
#include <iostream>
#include <mutex>
#include <vector>
#include <condition_variable>

int main(int argc, char *argv[])
{
    std::condition_variable cv;
    std::mutex mtx;
    std::vector<int> foods;

    std::thread th1( [&]() {
        for ( int i = 0; i < 2; ++i )
        {
            std::unique_lock lck( mtx );
            cv.wait( lck, [&]() { return foods.size() != 0; } );
            auto food = foods.back();
            foods.pop_back();
            lck.unlock();
            std::cout << "th1 got food:" << food << std::endl;
        }
        });

    std::thread th2( [&]() {
        for ( int i = 0; i < 2; ++i )
        {
            std::unique_lock lck( mtx );
            cv.wait( lck, [&]() { return foods.size() != 0; } );
            auto food = foods.back();
            foods.pop_back();
            lck.unlock();
            std::cout << "th2 got food:" << food << std::endl;
        }
        });
    foods.push_back( 42 );
    cv.notify_one();
    foods.push_back( 233 );
    cv.notify_one();

    foods.push_back( 666 );
    foods.push_back( 4399 );
    cv.notify_all();

    th1.join();
    th2.join();

    return 0;
}
