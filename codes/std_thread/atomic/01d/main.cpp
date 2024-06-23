#include <thread>
#include <iostream>
#include <mutex>
#include <vector>
#include <condition_variable>

int main(int argc, char *argv[])
{
    std::atomic<int> counter;
    counter.store( 0 );
    std::thread th1( [&]() {
        for ( int i = 0; i < 1000000; ++i )
        {
            counter.fetch_add( 1 );
        }
        });

    std::thread th2( [&]() {
        for ( int i = 0; i < 1000000; ++i )
        {
            counter.fetch_add( 1 );
        }
        });

    th1.join();
    th2.join();

    std::cout << "counter = " << counter << std::endl;

    return 0;
}
