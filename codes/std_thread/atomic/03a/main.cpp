#include <thread>
#include <iostream>
#include <vector>

struct AtomicInt
{
    int cnt;
    int store( int val )
    {
        this->cnt = val;
    }

    int load() const
    {
        return this->cnt;
    }

    int fetch_add( int val )
    {
        int old = this->cnt;
        this->cnt += val;
        return old;
    }

    int exchange( int val )
    {
        int old = this->cnt;
        this->cnt = val;
        return old;
    }

    bool compare_exchange_strong(int &old, int val)
    {
        if ( this->cnt == old )
        {
            this->cnt = val;
            return true;
        }
        else
        {
            old = this->cnt;
            return false;
        }
    }
    ;
};

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
