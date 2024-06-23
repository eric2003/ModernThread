#include <thread>
#include <iostream>
#include <string>
#include <vector>
#include <mutex>

class MTVector
{
private:
    std::vector<int> m_arr;
    mutable std::mutex m_mtx;
public:
    class Accessor
    {
    private:
        MTVector & m_that;
        std::unique_lock<std::mutex> m_guard;
    public:
        Accessor( MTVector & that )
            : m_that( that ), m_guard( that.m_mtx )
        {}
        void push_back( int val ) const
        {
            this->m_that.m_arr.push_back( val );
        }
        std::size_t size() const
        {
            return this->m_that.m_arr.size();
        }
    };
public:
    Accessor access()
    {
        return { *this };
    }
};

int main(int argc, char *argv[])
{
    MTVector arr;
    std::thread th1( [&]() {
        auto axr = arr.access();
        for ( int i = 0; i < 100000; ++i )
        {
            axr.push_back( i );
        }
        });
    std::thread th2( [&]() {
        auto axr = arr.access();
        for ( int i = 0; i < 100000; ++i )
        {
            axr.push_back( 100000 + i );
        }
        });
    th1.join();
    th2.join();

    std::cout << " arr.access().size() = " << arr.access().size() << std::endl;

    return 0;
}
