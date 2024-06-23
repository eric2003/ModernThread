#include <thread>
#include <iostream>
#include <mutex>
#include <vector>
#include <condition_variable>

int main(int argc, char *argv[])
{
    std::atomic<int> counter;
    counter.store( 0 );

    std::vector<int> data( 2000000 );
    std::thread th1( [&]() {
        for ( int i = 0; i < 1000000; ++i )
        {
            int index = counter.fetch_add( 1 );
            data[ index ] = i;
        }
        });

    std::thread th2( [&]() {
        for ( int i = 0; i < 1000000; ++i )
        {
            int index = counter.fetch_add( 1 );
            data[ index ] = i + 1000000;
        }
        });

    th1.join();
    th2.join();

    std::cout << "data[1000000] = " << data[1000000] << std::endl;

    return 0;
}
