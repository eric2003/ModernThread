#include <thread>
#include <iostream>
#include <vector>

int main(int argc, char *argv[])
{
    std::boolalpha( std::cout );
    std::atomic<int> counter;
    counter.store( 2 );

    int old = 1;
    bool equal = counter.compare_exchange_strong( old, 3 );
    std::cout << "equal = " << equal << std::endl; //false
    std::cout << "old=" << old << std::endl; //2

    int now = counter.load();
    std::cout << "now=" << now << std::endl; //2

    old = 2;
    equal = counter.compare_exchange_strong( old, 3 );
    std::cout << "equal = " << equal << std::endl; //true
    std::cout << "old=" << old << std::endl; //2

    now = counter.load();
    std::cout << "now=" << now << std::endl; //3

    return 0;
}
