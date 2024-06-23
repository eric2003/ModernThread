#include <thread>
#include <iostream>
#include <mutex>
#include <vector>
#include <condition_variable>

int main(int argc, char *argv[])
{
    std::atomic<int> counter;
    counter.store( 0 );

    int old = counter.exchange( 3 );
    std::cout << "old=" << old << std::endl;

    int now = counter.load();
    std::cout << "now=" << now << std::endl;

    return 0;
}
